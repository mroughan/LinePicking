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
#include <R.h>


 double beta(double a, double b)
{
    /* C gamma function is deprecated, use tgamma instead */
    return( exp( lgamma(a) + lgamma(b) - lgamma(a+b)) );

}


/* beta continued fraction calculation 
      don't use this directly -- its used below
*/
 double beta_cont_frac(double a, double b, double x)
{
    double d, cf=0;
    int i, m;
    int n = 10;
    for (i=n; i>=1; i--) {
	m = i/2;
	if (i % 2 == 0) {
	    /* even case */
	    d = m*(b-m)*x / ((a+2*m-1)*(a+2*m));
	} else {
	    /* odd case */
	    d = - (a+m)*(a+b+m)*x / ( (a+2*m)*(a+2*m+1) );
	}
	cf = d / (1 + cf);
    }
    cf = 1 / (1 + cf);
    return(cf);
}

/* regularized incomplete beta function */
 double beta_inc(double a, double b, double x)
{
    double cf;

    /* check input arguments */
    if (x < 0.0 || x > 1.0) 
    {
	fprintf(stderr, "beta_inc: x (=%.3f) must be in the interval [0,1]\n", x);
	exit(1);
    }
    if (a < 0)
    {
	fprintf(stderr, "beta_inc: a (=%.3f) must be > 0\n", a);
	exit(1);
    }
    if (b < 0)
    {
	fprintf(stderr, "beta_inc: b (=%.3f) must be > 0\n", b);
	exit(1);
    }
    /* printf("    a=%.2f, b=%.2f, x=%6f, (a+1.0)/(a+b+2.0)=%6f\n", a, b, x,(a+1.0)/(a+b+2.0));     */
	
    /* deal with some extreme cases */
    if (x==0.0) return(0.0);
    else if (x==1.0) return(1.0);
 
    if (a==0.0) return(1.0);
    else if (b==0.0) return(0.0);

    if (a==1.0 && b==1.0) return (x);
    else if (a==1.0) return( (1 - pow(1-x,b))/(b*beta(a,b)) );
    else if (b==1.0) return( pow(x,a)/(a*beta(a,b)) );

    /* use identities to get a>1 and b>1  */
    if (a < 1 && b < 1) {
	return( (a*beta_inc(a+1,b,x) + b*beta_inc(a,b+1,x))/(a+b)  );
    } else if (a < 1) {
	return( beta_inc(a+1,b,x) + pow(x,a)*pow(1-x,b)/(a*beta(a,b)) );
    } else if (b < 1) {
	return( beta_inc(a,b+1,x) - pow(x,a)*pow(1-x,b)/(b*beta(a,b)) );
    }

    /* get started */
    if (x <= (a+1.0)/(a+b+2.0)) {
	/* use continued fractions */
	cf = beta_cont_frac(a,b,x);
	return( pow(x,a)*pow(1-x,b)*cf/(a*beta(a,b)) );
    } else {
	/* look at complement */
	/* cf = beta_cont_frac(b, a, 1-x); */
	/* return( 1.0 -  pow(x,a)*pow(1-x,b)*cf/(b*beta(b,a)) );*/
	return( 1.0 - beta_inc(b, a, 1.0-x) ); 
    }
    
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
	    Rprintf("t[i] is %g\n",t[i]);
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
	Rprintf("Mode is unknown\n");
    }
    return(0); /* correctly executed */
}

