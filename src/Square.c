/* Square.c	
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
#include "Square.h"

char *SquareDistanceName = "square";
char *SquareDistanceDescription = "square, with side length parameters[0]";
int SquareDistanceNpar = 1;

double SquareDistancePDF(double t, double* parameters)
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
        return( 2*t*( 4*sqrt(t2-1) - 
                     (t2+2-M_PI) -4*atan(sqrt(t2-1)) )/parameters[0] );
    }
    
}

double SquareDistanceCDF(double t, double* parameters)
/* distance cumulative distribution (at t) between two points in a unit square*/
/*    http://mathworld.wolfram.com/SquareLinePicking.html */
{
    double L = M_SQRT2;
    double t2, tmp;
    t = t/parameters[0]; /* rescale points to unit square */
    t2 = t*t;
    
    if (t<=0) {
        return(0);
    } else if (t >= L) {
        return(1);
    }
    
    /* two cases */
    if (t <= 1) {
        return( pow(t,4.0)/2 - 8.0*pow(t,3.0)/3 + M_PI*t2 );
    } else {
        tmp = sqrt( t2 - 1 );
        return( -pow(t,4.0)/
               2 -4*t2*atan(tmp) +4.0*(2.0*t2+1)*tmp/3.0 +(M_PI-2)
               *t2 + 1.0/3.0);
    }
}

double SquareDistanceMean(double* parameters)
/* mean distance between two points in a unit square */
/*    http://mathworld.wolfram.com/SquareLinePicking.html */
{
    return(parameters[0] * (2 + M_SQRT2 + 5*asinh(1))/15.0);
}

double SquareDistanceVar(double* parameters)
/* variance of distances between two points in a unit square */
/*    http://mathworld.wolfram.com/SquareLinePicking.html */
{
    double tmp = asinh(1);
    return(parameters[0]*parameters[0] * 
           (69 - 4*M_SQRT2 - 10.0*(2 + M_SQRT2)*tmp - 25*tmp*tmp)/225.0);
}


void SquareDistanceSupport(double *t, double *parameters)
{
    /* square, with side length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0]*sqrt(2);
}

void SquareDistanceCheckParameters(double *parameters, int *result, 
                                   char *error_str)
{
    /* square, with side length parameters[0] */
    *result=0;
}