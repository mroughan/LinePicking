/* LinePicking.c	
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
 * MEX Call as:   [g] = LinePicking(t, mode, parameters)
 *                   remember: parameter(1) (in matlab) == parameter[0] (in C)
 *
 * C Call as:     result = LinePicking(t, g, N, mode, parameters, Npar);
 *
 * Unix command line call as:  
 *            LinePicking -f input_file -m mode -p parameter0 -P parameter1
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
#include "LinePicking.h"
#include "beta.h" 
  
#ifdef _R
#include <R.h>
#endif

#ifdef _MEX
#include "mex.h"
#include "matrix.h"
#endif

void LinePickingCheckParameters(int *mode, double* parameters, int *Npar, int *result, char **error_str)
/* check that a mode and a set of parameters are valid
 *
 * mode = type of region
 *    0: square, with side length parameters[0] 
 *    1: disk, with radius parameters[0] 
 *    2: hyper-ball, dimension parameters[0], radius parameters[1] 
 *    3: rectangle, side lengths parameters[0], parameters[1] 
 *    4: line, length parameters[0] 
 *    5: cube, side length parameters[0] parameters = parameters of the region
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, and similarly, 
 * the function must return void, so we return the exit code in the last argument.
 */
{
    int i;
    static int npars[6] = {1, 1, 2, 2, 1, 1}; 
    
    *error_str  = (char *) malloc((size_t) sizeof(char)*256); /* longest error string is 255 characters */

    /* check the mode is supported */
    if (*mode<0 || *mode>5) {
	*result=1;
	sprintf(*error_str, "LinePickingCheckParameters: the mode %d is unsupported.", *mode);
	return;
    }

    /* check that there are the right number of parameters */
    if (*Npar != npars[*mode]) {
	*result=3;
	sprintf(*error_str, "LinePickingCheckParameters: mode %d requires %d parameters (%d were input).", 
		*mode, npars[*mode], *Npar);
	return;
    }

    /* no non-positive parameters are allowed for any distributions */
    for (i=0;i<*Npar;i++) {
    	if (parameters[i] <= 0) {
	    *result=2;
	    sprintf(*error_str, "LinePickingCheckParameters: all parameters must be >0, but parameter[%d]=%lf", 
		    i, parameters[i]);
	    return;
	}
    }

    /* check mode specific details of input parameters */
    switch (*mode) {
    case 0:/* square, with side length parameters[0] */
	break;
    case 1:/* disk, with radius parameters[0] */
	break;
    case 2: /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
	if (parameters[0] < 1) {
	    *result=2;
	    sprintf(*error_str, "LinePickingCheckParameters: in mode 2, we must have parameter[0]>=1, but  parameter[0]=%lf", 
		    parameters[0]);
	    return;
	}
	break;
    case 3:/* rectangle, side lengths parameters[0], parameters[1] */
	break;
    case 4: /* line, length parameters[0] */
	break;
    case 5: /* cube, side length parameters[0] */
	break;
    }

    /* otherwise, everything is OK */
    *result=0;
    return;
}

void LinePickingSupport(double *t, int *mode, double* parameters, int *Npar, int *result, char **error_str) 
/* compute support of distance density g(t) (at points t) between two points in a region.
 *
 * t = [t_min, t_max]    : assumes 2 spaces are allocated!!!!!
 * mode = type of region
 *    0: square, with side length parameters[0] 
 *    1: disk, with radius parameters[0] 
 *    2: hyper-ball, dimension parameters[0], radius parameters[1] 
 *    3: rectangle, side lengths parameters[0], parameters[1] 
 *    4: line, length parameters[0] 
 *    5: cube, side length parameters[0] parameters = parameters of the region
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, and similarly, 
 * the function must return void, so we return the exit code in the last argument.
 */
{

    /* first check input parameters */
    LinePickingCheckParameters(mode, parameters, Npar, result, error_str);
    if (*result != 0) {
	/* something was wrong with parameters */
	return;
    }

    /* the lower end of the support for all current cases is 0 */
    t[0] = 0;

    /* compute the upper end of the support */
    switch (*mode) {
    case 0:/* square, with side length parameters[0] */
	t[1] = parameters[0]*sqrt(2);
	break;
    case 1:/* disk, with radius parameters[0] */
	t[1] = 2*parameters[0];
	break;
    case 2: /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
	t[1] = 2*parameters[0];
	break;
    case 3:/* rectangle, side lengths parameters[0], parameters[1] */
	t[1] = sqrt(parameters[0]*parameters[0] + parameters[1]*parameters[1]);
	break;
    case 4: /* line, length parameters[0] */
	t[1] = parameters[0];
	break;
    case 5: /* cube, side length parameters[0] */
	t[1] = parameters[0]*sqrt(3);
	break;
    }

    *result=0;
    return; /* correctly executed */
}

void LinePickingPDF(double *t, double *g, int *N, int *mode, double* parameters, int *Npar, int *result, char **error_str) 
/* compute distance density g(t) (at points t) between two points in a region.
 *
 * t = array of points at which to calculate density 
 * g = array to store output 
 * mode = type of region
 *    0: square, with side length parameters[0] 
 *    1: disk, with radius parameters[0] 
 *    2: hyper-ball, dimension parameters[0], radius parameters[1] 
 *    3: rectangle, side lengths parameters[0], parameters[1] 
 *    4: line, length parameters[0] 
 *    5: cube, side length parameters[0] parameters = parameters of the region
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, and similarly, 
 * the function must return void, so we return the exit code in the last argument.
 */
{
    int i;
    double support[2];
    double (*PDF)(double, double*)=NULL;

    /* now calculate the support of the distribution,
       which will incidentally check that the parameters are valid
    */
    LinePickingSupport(support, mode, parameters, Npar, result, error_str);
    if (*result != 0) {
	/* something was wrong with parameters */
	return;
    }
    
    /* select the function to call */
    switch (*mode) {
    case 0:/* square, with side length parameters[0] */
	PDF = &SquareDistanceDensity;
	break;
    case 1:/* disk, with radius parameters[0] */
	PDF = &DiskDistanceDensity;
	break;
    case 2: /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
	PDF = &HyperballDistanceDensity;
	break;
    case 3:/* rectangle, side lengths parameters[0], parameters[1] */
	PDF = &RectangleDistanceDensity;
	break;
    case 4: /* line, length parameters[0] */
	PDF = &LineDistanceDensity;
	break;
    case 5: /* cube, side length parameters[0] */
	PDF = &CubeDistanceDensity;
	break;
    } 

    /* calculate the distribution */
    for (i=0; i<*N; i++) 
    {
	if (t[i] < support[0] || t[i] > support[1]) {
	    g[i] = 0;
	} else {
	    g[i] = (*PDF)(t[i], parameters);
	}
    }

    /* correctly executed */
    *result=0;
    return;
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
    double n = ceil(parameters[0]); 
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
    p = (n+1.0)/2.0;
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
    /* 	mexErrMsgTxt("LinePicking:HyperballDistanceDensity: problem with call to Matlab beta function."); */
    /* } */
    /* mxDestroyArray(rhs[0]); */
    /* mxDestroyArray(rhs[1]); */
    /* mxDestroyArray(rhs[2]); */
    /* mxDestroyArray(lhs[0]); */


    Ix = beta_inc(p, q, x);

    /* printf(" t=%.3f , x=%.3f, Ix=%.9f    Ix2=%.9f\n", t, x, Ix, Ix2); */
    return( n*(pow(t,n-1.0)/pow(r,n))*Ix );
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
  int N, M;    /* number of points */
  int Npar, Mpar;    /* number of parmeters */
  int i;					
  int mode;    /* the type of region on which to calculate the distribution */
  double *parameters; /*  input parameter vector  
			       note that meaning of parameters depends on the mode */
  int result;
  char *error_str;

  /* Check for proper number of input and output arguments. */    
  if (nrhs < 1)
       mexErrMsgTxt("LinePicking: Not enough input arguments: [g] = LinePicking(t, mode, parameters).");
  if (nlhs > 1) 
       mexErrMsgTxt("LinePicking: Too many output arguments: [g] = LinePicking(t, mode, parameters).");
  
  /* Get the input arguments */
  t = mxGetPr(prhs[0]);       /*  */
  N = (int) mxGetN(prhs[0]); /*  */
  M = (int) mxGetM(prhs[0]); /*  */
  if (N<1 || M>1) 
       mexErrMsgTxt("LinePicking: t should be an Nx1 matrix.");

  if (nrhs < 2) 
  {
      mode = 1; /* default mode is a square */
  } else {
      mode = (int) mxGetScalar(prhs[1]);
  }

  Npar = (int) mxGetN(prhs[2]);
  Mpar = (int) mxGetM(prhs[2]);
  Npar = Mpar*Npar;
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

  LinePickingPDF(t, g, &N, &mode, parameters, &Npar, &result, &error_str);
  if (result != 0) {
     mexErrMsgTxt(error_str);
  }

}
#endif


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */
static void 
usage_LinePicking()
{
  fprintf(stderr, "Usage: LinePicking -f input_file -m mode -p parameter[0] -q parameter[1] -s parameter[2] \n");
  fprintf(stderr, "           input_file contains a list of points t.\n");
  exit(1);
}

static void 
set_pars_LinePicking(int argc, char *argv[], char **file, int *mode, double *parameters, int *Npar)
{
  char c;
  extern char    *optarg;
  extern int      optind;

  /* defaults */
  *mode = 0;
  *file = (char *) malloc((size_t) sizeof(char)*256); /* longest allowed file name is 255 characters */
  parameters[0] = 1.0; 
  parameters[1] = 1.0;
  parameters[2] = 1.0; 
  
  while ((c=getopt(argc,argv,"f:m:p:q:s:z")) != EOF)
      switch ((char)c) { 
      case 'f': 
	  if (sscanf(optarg,"%s",*file) != 1) usage_LinePicking(); 
	  break; 
      case 'm':  
	  if (sscanf(optarg,"%d",mode) != 1) usage_LinePicking(); 
	  break; 
      case 'p': 
	  if (sscanf(optarg,"%lf",&(parameters[0])) != 1) usage_LinePicking(); 
	  break; 
      case 'q': 
	  if (sscanf(optarg,"%lf",&(parameters[1])) != 1) usage_LinePicking(); 
	  break;  
      case 's': 
	  if (sscanf(optarg,"%lf",&(parameters[2])) != 1) usage_LinePicking(); 
	  break;  
      case 'h':;
      default: 
	  usage_LinePicking(); 
      }

  switch (*mode) {
  case 0:/* square, with side length parameters[0] */
      *Npar = 1;
      break;
  case 1:/* disk, with radius parameters[0] */
      *Npar = 1;
      break;
  case 2: /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
      *Npar = 2;
      break;
  case 3:/* rectangle, side lengths parameters[0], parameters[1] */
      *Npar = 2;
      break;
  case 4: /* line, length parameters[0] */
      *Npar = 1;
      break;
  case 5: /* cube, side length parameters[0] */
      *Npar = 1;
      break;
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
  FILE *fp;    
  double t, g;
  int N=1;
  int result, Npar;
  char *error_str;

  /*print out program name and version*/
  fprintf(stderr,"%% %s: %s \n", *argv, version);

  /* read in programs options  */
  set_pars_LinePicking(argc, argv, 
			 &file, &mode, parameters, &Npar);
  fprintf(stderr,"%%   file=%s, mode=%d, Npar=%d,", file, mode, Npar);
  for (i=0;i<Npar;i++) {
      fprintf(stderr, " p[%d]=%.3f", i, parameters[i]);
  }
  fprintf(stderr, "\n");

  /* check the mode and parameters are valid */
  LinePickingCheckParameters(&mode, parameters, &Npar, &result, &error_str);
  if (result != 0) {
      fprintf(stderr, "LinePicking: %s\n", error_str);
      exit(1);
  }

  /* read in the input file, and output the results */
  fp = fopen(file, "r");  /* open the file for reading */
  if (fp == NULL) {
      fprintf(stderr, "LinePicking: invalid file!\n");
      exit(1);
  }
  while(fscanf(fp, "%lf", &t) == 1) /* test that we read in exactly one double */
  {
      LinePickingPDF(&t, &g, &N, &mode, parameters, &Npar, &result, &error_str);
      if (result == 0) {
	  fprintf(stdout, "%lf, %lf\n", t, g);
      } else {
	  fprintf(stderr, "LinePicking: error, unexpected error.\n");
	  exit(result);
      }
  }
  fclose(fp);
  
  return(0);
}

#endif


