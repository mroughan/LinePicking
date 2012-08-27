/* Hyperball.c	
 *
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 *     Copyright 2012 Eric Parsonage <eric.parsonage@adelaide.edu.au>
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
 */

#include <math.h>
#include <stdio.h>
#include "Hyperball.h"
#include "beta.h" 

char *HyperballDistanceName = "hyper-ball";
char *HyperballDistanceDescription = "hyper-ball, with dimension parameters[0]"
", and radius parameters[1]";
int HyperballDistanceNpar = 2;


double HyperballDistancePDF(double t, double* parameters)
/* distance density (at t) between two points in a hyperball, 
 dimension n, radius r */
/*  
 @Misc{tu00:_circle_line,
 author = 	 {Tu, S.-J. and Fischbach, E.},
 title = 	 {A New Geometric Probability Technique for an {N}-Dimensional Sphere and Its Applications},
 year = 	 2000,
 howpublished = {arXiv:math-ph/0004021v3, \url{http://arxiv.org/abs/math-ph/0004021}}}
 
 http://mathworld.wolfram.com/BallLinePicking.html */
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
    /* 	mexErrMsgTxt("LinePicking:HyperballDistancePDF: problem with call to Matlab beta function."); */
    /* } */
    /* mxDestroyArray(rhs[0]); */
    /* mxDestroyArray(rhs[1]); */
    /* mxDestroyArray(rhs[2]); */
    /* mxDestroyArray(lhs[0]); */
    
    
    Ix = beta_inc(p, q, x);
    
    /* printf(" t=%.3f , x=%.3f, Ix=%.9f    Ix2=%.9f\n", t, x, Ix, Ix2); */
    return( n*(pow(t,n-1.0)/pow(r,n))*Ix );
}


double HyperballDistanceCDF(double a, double* b)
{
    
    
    return(-1);
}

double HyperballDistanceMean(double* parameters)
/* mean distance between two points in a hyperball, 
 dimension n, radius r */
/*  
 @Misc{tu00:_circle_line,
 author = 	 {Tu, S.-J. and Fischbach, E.},
 title = 	 {A New Geometric Probability Technique for an {N}-Dimensional Sphere and Its Applications},
 year = 	 2000,
 howpublished = {arXiv:math-ph/0004021v3, \url{http://arxiv.org/abs/math-ph/0004021}}}
 */
{
    double n = ceil(parameters[0]); 
    double m = 1;
    double tmp = pow((n/(n+m)),2.0) * pow(parameters[1],m)
	*tgamma(n+m+1.0)*tgamma(n/2.0)/( tgamma((n+m)/2.0)*tgamma(n+1 + m/2.0) );
    return( tmp );
    
    /* switch (n) { */
    /* case 1: */
    /* 	return(parameters[1] * 2.0/3.0); */
    /* 	break; */
    /* case 2: */
    /* 	return(parameters[1] * 128.0/(45*M_PI)); */
    /* 	break; */
    /* case 3: */
    /* 	return(parameters[1] * 36.0/35.0); */
    /* 	break; */
    /* case 4: */
    /* 	return(parameters[1] * 16384.0/(4725*M_PI)); */
    /* 	break; */
    /* case 5: /\* calculated numerically *\/ */
    /* 	return(parameters[1] * 1.154401161607); */
    /* 	break; */
    /* case 6: /\* calculated numerically *\/ */
    /* 	return(parameters[1] * 1.190852402194); */
    /* 	break; */
    /* default: */
    /* 	return(-1); */
    /* 	break; */
    /* } */
}

double HyperballDistanceVar(double* parameters)
/* variance of distance between two points in a hyperball, 
 dimension n, radius r */
/*  
 @Misc{tu00:_circle_line,
 author = 	 {Tu, S.-J. and Fischbach, E.},
 title = 	 {A New Geometric Probability Technique for an {N}-Dimensional Sphere and Its Applications},
 year = 	 2000,
 howpublished = {arXiv:math-ph/0004021v3, \url{http://arxiv.org/abs/math-ph/0004021}}}
 */
{
    double n = ceil(parameters[0]); 
    double m = 2;
    double tmp = pow((n/(n+m)),2.0) * pow(parameters[1],m)
	*tgamma(n+m+1.0)*tgamma(n/2.0)/( tgamma((n+m)/2.0)*tgamma(n+1 + m/2.0) );
    return( tmp - pow(HyperballDistanceMean(parameters),2.0));
    
    
    /* switch (n) { */
    /* case 1: */
    /* 	return(parameters[1] * parameters[1] * 0.222222222222); */
    /* 	break; */
    /* case 2: */
    /* 	return(parameters[1] * parameters[1] * 0.180224062826); */
    /* 	break; */
    /* case 3: */
    /* 	return(parameters[1] * parameters[1] * 0.142040815734); */
    /* 	break; */
    /* case 4: */
    /* 	return(parameters[1] * parameters[1] * 0.115083085418); */
    /* 	break; */
    /* case 5: */
    /* 	return(parameters[1] * parameters[1] * 0.095929395933); */
    /* 	break; */
    /* case 6: */
    /* 	return(parameters[1] * parameters[1] * 0.081870574293); */
    /* 	break; */
    /* default: */
    /* 	return(-1); */
    /* 	break; */
    /* } */
}

void HyperballDistanceSupport(double *t, double *parameters)
{
    /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    t[0] = 0;
    t[1] = 2*parameters[1];
}

void HyperballDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    *result=0;
    /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    if (parameters[0] < 1) 
    {
        sprintf(error_str, 
                "LinePickingCheckParameters: hyperball,"
                " must have parameter[0]>=1, but  parameter[0]=%lf", 
                parameters[0]);
        *result=2;
    }
}
