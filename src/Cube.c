/* Cube.c	
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 * Copyright 2012 Eric Parsonage <eric.parsonagen@adelaide.edu.au>
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

#include "Cube.h"

char * CubeDistanceName = "cube";
char * CubeDistanceDescription = "cube, side length parameters[0]";
int CubeDistanceNpar = 1;


double CubeDistancePDF(double t, double* parameters)
/* distance density (at t) between two points in a unit cube */
/*    http://mathworld.wolfram.com/CubeLinePicking.html */
/*    from Mathai, A. M.; Moschopoulos, P.; and Pederzoli, G. 
 "Distance between Random Points in a Cube." J. Statistica 59, 61-81, 1999.
 but with 'corrected typos'
 */ 
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
                   -16*t*asin( 1.0/sqrt(2.0 - 2.0/t2) )/* acsc(x) = asin(1/x) */
                   +16.0*t*atan( t*tmp )
                   -24.0*(1.0+t2)*atan( tmp )
                   )/parameters[0] );
    }
    
}

double CubeDistanceCDF(double a, double* b)
{
    return(-1);
}


double CubeDistanceMean(double* parameters)
/* mean distance between two points in a unit cube */
/*    http://mathworld.wolfram.com/CubeLinePicking.html */
/*    from Mathai, A. M.; Moschopoulos, P.; and Pederzoli, G. 
 "Distance between Random Points in a Cube." J. Statistica 59, 61-81, 1999.
 but with 'corrected typos'
 */
{
    double L = M_SQRT2;
    double L3 = sqrt(3);
    double tmp;
    
    /* Robbin's constant */
    return(parameters[0] * ( 4 + 17.0*M_SQRT2 - 6*sqrt(3) + 21*log(1+M_SQRT2) 
                            + 42.0*log(2+sqrt(3)) - 7*M_PI )/105.0);
}


double CubeDistanceVar(double* parameters)
/* mean distance between two points in a unit cube */
/*    calculated numerically */
{
    return(parameters[0]*parameters[0]*0.062143604936);
}


void CubeDistanceSupport(double *t, double *parameters)
{
    /* cube, side length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0]*sqrt(3);
}


void CubeDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* cube, side length parameters[0] */
    *result=0; 
}
