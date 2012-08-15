/* distance_dist.h
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
 * Compute the
 *   Distance distribution between two random points in a region.
 *
 * Most of the actual distributions are included here as inline
 * function (as most are pretty short).
 *
 * $Header$
 */
#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>
#include "beta.h"

#ifndef _DISTANCE_DIST_H
#define _DISTANCE_DIST_H
 

inline double RectangleDistanceDensity(double t, double* parameters)
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


inline double SquareDistanceDensity(double t, double* parameters)
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

inline double LineDistanceDensity(double t, double* parameters)
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

inline double CubeDistanceDensity(double t, double* parameters)
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

inline double DiskDistanceDensity(double t, double* parameters)
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

inline double HyperballDistanceDensity(double t, double* parameters)
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

int distance_dist(double *, double *, int, int, double*, int);

static void usage_distance_dist();

static void set_pars_distance_dist(int argc, char *argv[], char **file, int *mode, double *parameters);

int main(int argc, char *argv[]);


#endif
