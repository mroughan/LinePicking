/* distance_dist.c	
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *   
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Compute the distance distribution between two point in a region, 
 * often called the "line picking problem".
 *
 * MEX Call as:   [g] = distance_dist(t, mode, parameters)
 *                   remember: parameter(1) (in matlab) == parameter[0] (in C)
 *
 * C Call as:     result = distance_dist(t, g, N, mode, parameters, Npar);
 *
 * Unix command line call as:  
 *            distance_dist -f input_file -m mode -p parameter0 -P parameter1
 *                   but this isn't finished yet
 *    
 * Various regions are supported:
 *    0: square, with side length parameters[0]
 *    1: disk, with radius parameters[0]
 *    2: hyper-ball, dimension parameters[0], radius parameters[1]
 *    3: rectangle, side lengths parameters[0], parameters[1]
 *    4: line, length parameters[0]
 *    5: cube, side length parameters[0]
 *
 * 
 */
#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>
#include "distance_dist.h"
#include "beta.h" 
  
#include <R.h>

#ifdef _MEX
#include "mex.h"
#include "matrix.h"
#endif

int distance_dist(double *t, double *g, int *N, int *mode, double* parameters, int *Npar)
/* computer distance density g(t) (at points t) between two points in a region.
 *
 * t = array of points at which to calculate density
 * g = array to store output
 * mode = 
 *    0: square, with side length parameters[0]
 *    1: disk, with radius parameters[0]
 *    2: hyper-ball, dimension parameters[0], radius parameters[1]
 *    3: rectangle, side lengths parameters[0], parameters[1]
 *    4: line, length parameters[0]
 *    5: cube, side length parameters[0]
 * parameters = parameters of the region (see above)
 * Npar = number of parameters
 *  
 */
{
    int i;
    Rprintf("Hello Jono\n");

    /* calculate the distribution */
    if (*mode == 0) /* square, with side length parameters[0] */
    {
	if (*Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = SquareDistanceDensity(t[i], parameters);
	}
    } else if (*mode == 1) /* disk, with radius parameters[0] */
    {
	if (*Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = DiskDistanceDensity(t[i], parameters);
	}
    } else if (*mode == 2) /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    {
	if (*Npar < 2) {
	    return(3);
	}
	if (parameters[0] < 1) {
	    return(2);
	}
	if (parameters[1] <= 0) {  
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = HyperballDistanceDensity(t[i], parameters);
	}
    } else if (*mode == 3) /* rectangle, side lengths parameters[0], parameters[1] */
    {
	if (*Npar < 2) {
	    return(3);
	}
	if (parameters[0] <= 0 || parameters[1] <= 0) {
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = RectangleDistanceDensity(t[i], parameters);
	}
    } else if (*mode == 4) /* line, length parameters[0] */
    {
	if (*Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = LineDistanceDensity(t[i], parameters);
	}
    } else if (*mode == 5) /* cube, side length parameters[0] */
    {
	if (*Npar < 1) {
	    return(3);
	}
	if (parameters[0] <= 0) {
	    return(2);
	}
	for (i=0; i<*N; i++) 
	{
	    g[i] = CubeDistanceDensity(t[i], parameters);
	}
    } else {
	return(1); /* first type of error */
    }
    return(0); /* correctly executed */
}


double RectangleDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points in a rectangle size a times b */
/*   "Random Distances Within a Rectangle and Between Two Rectangles", B. Ghosh,
               Bulletin of the Calcutta Mathematical Society, Col.43 (1), p.17-24, 1951.
     "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI - R MOSCHOPOULOS -G. PEDERZOLI
               RENDICONT1 DEL CIRCOLO MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190
   */
{
    double a = parameters[0];
    double b = parameters[1];
    double a2 = a*a;
    double b2 = b*b;
    double L2 = a2+ b2;
    double L = sqrt(L2);
    double t2 = t*t;
    double tmp;

    if (t<=0) {
	return(0);
    } else if (t >= L) {
	return(0);
    }

    /* make sure a < b */
    if (a > b) 
    {
	tmp = b;
	b = a;
	a = tmp;
	a2 = a*a;
	b2 = b*b;
    }

    /* three cases */
    if (t <= a)
    {
	return( 4*( (a*b*M_PI)/2 - (a+b)*t + t2/2 
		    )*t/(a2*b2) );
    } else if (t>a && t<=b) 
    {
	return( 4*( a*b*asin(a/t) 
		    - a2/2 - b*t
		    + b*sqrt(t2-a2) 
		    )*t/(a2*b2) );
    } else {
	return( 4*(  a*b*(asin(a/t) - asin(sqrt(1 - b2/(t2)))) 
		     - (a2 + b2 + t2)/2
		     + a*sqrt(t2-b2)
		     + b*sqrt(t2-a2) 
		    )*t/(a2*b2));
    }

}


double SquareDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points in a unit square */
/*    http://mathworld.wolfram.com/SquareLinePicking.html */
{
    double L = M_SQRT2;
    double t2;
    t = t/parameters[0]; /* rescale points to unit square */
    t2 = t*t;

    if (t<=0) {
	return(0);
    } else if (t >= L) {
	return(0);
    }

    /* two cases */
    if (t <= 1)
    {
	return( 2*t*(t2 - 4*t + M_PI)/parameters[0] );
    } else {
	return( 2*t*( 4*sqrt(t2-1) - (t2+2-M_PI) -4*atan(sqrt(t2-1)) )/parameters[0] );
    }

}

double LineDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points on a unit line */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    
    if (t<0) {
	return(0);
    } else if (t >= L) {
	return(0);
    } else {
	return(2*(1-t/L)/L);
    }
}

double CubeDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points in a unit cube */
/*    http://mathworld.wolfram.com/CubeLinePicking.html */
/*    from Mathai, A. M.; Moschopoulos, P.; and Pederzoli, G. 
       "Distance between Random Points in a Cube." J. Statistica 59, 61-81, 1999.
      but with 'corrected typos'
 */

/* middle section isn't working though */
{
    double L = M_SQRT2;
    double L3 = sqrt(3);
    double t2;
    double tmp;
    t = t/parameters[0]; /* rescale points to unit square */
    t2 = t*t;

    if (t<=0) {
	return(0);
    } else if (t >= L3) {
	return(0);
    }

    /* three cases */
    if (t <= 1)
    {
	return( -t2*( (t-8)*t2 + M_PI*(6*t - 4) )/parameters[0] );
    } else if ( t <= L ) {
	tmp = sqrt(t2-1.0);
	/* return( ( 4.0 - M_PI - 0.5)  ); */
	return( 2.0*t*( 
		    t2*(t2-8.0*tmp+3.0)
		    -4.0*tmp
		    +12.0*t2*acos(1.0/t)    /* asec(x) = acos(1/x) */
		    +M_PI*(3.0-4.0*t)
		    -0.5
		    )/parameters[0]  );
    } else {
	tmp = sqrt(t2-2.0);
	return( t*(
		    (1.0+t2)*( 6.0*M_PI + 8.0*tmp - 5.0 - t2)
		    -16*t*asin( 1.0/sqrt(2.0 - 2.0/t2) )  /* acsc(x) = asin(1/x) */
		    +16.0*t*atan( t*tmp )
		    -24.0*(1.0+t2)*atan( tmp )
		    )/parameters[0] );
    }
 
}

double DiskDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points in a disk radius r */
/*    http://mathworld.wolfram.com/BallLinePicking.html */
{
    double r = parameters[0];
    double d = 2*r;
    double r2 = r*r;
    double t2 = t*t;			     
    double part1, part2, c;

    if (t<=0) {
	return(0);
    } else if (t >= d) {
	return(0);
    }

    /* two cases */
    c = acos(t/(2*r));
    part1 = 4*t*c / (M_PI*r2);
    part2 = 2*t2*sqrt(1 - (t2/(4*r2)))/(M_PI*r*r2);
    return(part1 - part2);
}

double HyperballDistanceDensity(double t, double* parameters)
/* distance density (at t) between two points in a hyperball, 
   dimension n, radius r */
/*    http://mathworld.wolfram.com/BallLinePicking.html */
{
    double n = parameters[0]; 
    double r = parameters[1];
    double d = 2*r;
    double r2 = r*r;
    double t2 = t*t;			     
    double p, q, x, Ix, Ix2;
    int result;
    /* mxArray *rhs[3], *lhs[1]; /\* arrays for passing parameters back to Matlab */
    /* 				 to compute incomplete beta function *\/ */

    if (t<=0) {
	return(0);
    } else if (t >= d) {
	return(0);
    }

    x = 1.0 - t2/(4.0*r2);
    p = (n+1)/2.0;
    q = 1.0/2.0;

    /* call matlab to get values for incomplete beta function */
    /* /\* Matlab BETAINC(X,Z,W) computes the incomplete beta function *\/ */
    /* /\* result = mexCallMATLAB(int nlhs, mxArray *plhs[], int nrhs,  mxArray *prhs[], const char *functionName); */
    /*      http://www.mathworks.com.au/help/matlab/creating-c-c-and-fortran-programs-to-be-callable-from-matlab-mex-files.html */
    /* 	 http://www.mathworks.com.au/help/techdoc/apiref/bqoqnz0.html */
    /*      http://www.mathworks.com.au/help/matlab/apiref/mexcallmatlab.html */
    /* 	 http://www.mathworks.com.au/help/techdoc/apiref/mxcreatedoublescalar.html */
    /*  *\/ */
    /* rhs[0] = mxCreateDoubleScalar(x); /\* create data structure for input to function *\/ */
    /* rhs[1] = mxCreateDoubleScalar(p); /\* create data structure for input to function *\/ */
    /* rhs[2] = mxCreateDoubleScalar(q); /\* create data structure for input to function *\/ */
    /* lhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL); /\* create data structure for output of function *\/ */
    /* result = mexCallMATLAB(1, lhs, 3,  rhs, "betainc"); */
    /* if (result == 0) { */
    /* 	Ix2 = mxGetScalar(lhs[0]); */
    /* } else { */
    /* 	mexErrMsgTxt("distance_dist:HyperballDistanceDensity: problem with call to Matlab beta function."); */
    /* } */
    /* mxDestroyArray(rhs[0]); */
    /* mxDestroyArray(rhs[1]); */
    /* mxDestroyArray(rhs[2]); */
    /* mxDestroyArray(lhs[0]); */


    Ix = beta_inc(p, q, x);

    /* printf(" t=%.3f , x=%.3f, Ix=%.9f    Ix2=%.9f\n", t, x, Ix, Ix2); */
    return( n*(pow(t,n-1)/pow(r,n))*Ix );
}







#ifdef _MEX

/*
 * Matlab parts
 *
 */

void mexFunction(
        int nlhs,       mxArray *plhs[],
        int nrhs, const mxArray *prhs[]
        )
{
  
  double *t; /* points at which to calculate the distribution */
  double *g; /* value of the distribution at the points t */
  uint32_t N, M;    /* number of points */
  uint32_t Npar, Mpar;    /* number of parmeters */
  int i;					
  int mode;    /* the type of region on which to calculate the distribution */
  double *parameters; /*  input parameter vector  
			       note that meaning of parameters depends on the mode */
  int result;

  /* Check for proper number of input and output arguments. */    
  if (nrhs < 1)
       mexErrMsgTxt("distance_dist: Not enough input arguments: [g] = distance_dist(t, mode, parameters).");
  if (nlhs > 1) 
       mexErrMsgTxt("distance_dist: Too many output arguments: [g] = distance_dist(t, mode, parameters).");
  
  /* Get the input arguments */
  t = mxGetPr(prhs[0]);       /*  */
  N = (uint32_t) mxGetN(prhs[0]); /*  */
  M = (uint32_t) mxGetM(prhs[0]); /*  */
  if (N<1 || M>1) 
       mexErrMsgTxt("distance_dist: t should be an Nx1 matrix.");

  if (nrhs < 2) 
  {
      mode = 1; /* default mode is a square */
  } else {
      mode = (int) mxGetScalar(prhs[1]);
  }

  Npar = (uint32_t) mxGetN(prhs[2]);
  Mpar = (uint32_t) mxGetM(prhs[2]);
  if (nrhs < 3 || Npar*Mpar<1)
  {
      parameters = (double *) malloc((size_t) sizeof(double)*3);
	  /* allocate three, even though at the moment we only need 2 */
      parameters[0] = 1;
      parameters[1] = 1;
      parameters[2] = 1;
  } else {
      parameters = mxGetPr(prhs[2]); 
  }
  
  /* create output matrices */
  plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
  g = mxGetPr(plhs[0]);

  result = distance_dist(t, g, N, mode, parameters, Mpar*Npar);
  if (result == 0) {
      /* this means it returned correctly */
  } else if (result == 1) {
      mexErrMsgTxt("distance_dist: unsupported mode.");
  } else if (result == 2) {
      mexErrMsgTxt("distance_dist: parameters out of range.");
  } else if (result == 3) {
      mexErrMsgTxt("distance_dist: not enough parameters were entered.");
  }

}
#endif


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */
static void 
usage_distance_dist()
{
  fprintf(stderr, "Usage: distance_dist -f input_file -m mode -p parameter0 -P parameter1 \n");
  fprintf(stderr, "           input_file contains a list of points t.\n");
  exit(1);
}

static void 
set_pars_distance_dist(int argc, char *argv[], char **file, int *mode, double *parameters)
{
  char c;
  extern char    *optarg;
  extern int      optind;
  int F;

  /* defaults */
  *mode = 0;
  *file = (char *) malloc((size_t) sizeof(char)*256); /* longest file name is 256 characters */
  /* *parameters = (double *) malloc((size_t) sizeof(double)*3); */
  /* (*parameters)[0] = 1.1; */
  /* (*parameters)[1] = 1.2; */
  /* (*parameters)[2] = 1.3; */
  parameters[0] = 1.0; 
  parameters[1] = 1.0;
  parameters[2] = 1.0; 
  
  while ((c=getopt(argc,argv,"f:m:p:q:s:z")) != EOF)
      switch ((char)c) { 
      case 'f': 
	  if (sscanf(optarg,"%s",*file) != 1) usage_distance_dist(); 
	  break; 
      case 'm':  
	  if (sscanf(optarg,"%d",mode) != 1) usage_distance_dist(); 
	  break; 
      case 'p': 
	  if (sscanf(optarg,"%lf",&(parameters[0])) != 1) usage_distance_dist(); 
	  break; 
      case 'q': 
	  if (sscanf(optarg,"%lf",&(parameters[1])) != 1) usage_distance_dist(); 
	  break;  
      case 's': 
	  if (sscanf(optarg,"%lf",&(parameters[2])) != 1) usage_distance_dist(); 
	  break;  
      case 'h':;
      default: 
	  usage_distance_dist(); 
      }
}
 
int main(int argc, char *argv[])
{
  int i=0;
  char *readbuf;
  double epsilon;
  int mode;
  double parameters[3];
  char *version = "version 1.0";
  char *file;

  /*print out program name and version*/
  fprintf(stderr,"%% %s: %s \n", *argv, version);

  /* read in programs options  */
  set_pars_distance_dist(argc, argv, 
			 &file, &mode, parameters);
  fprintf(stderr,"%%   file=%s, mode=%d, ", file, mode);
  for (i=0;i<3;i++) {
      fprintf(stderr, " p[%d]=%.3f", i, parameters[i]);
  }
  fprintf(stderr, "\n");

  return(0);
}
#endif


