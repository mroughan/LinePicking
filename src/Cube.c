/* Cube.c	
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

#include "Cube.h"

char * CubeDistanceName = "cube";
char * CubeDistanceDescription = "cube, side length parameters[0]";
int CubeDistanceNpar = 1;

/**
 * Implements the PDF of the distance between two random points within a cube.
 *
 * From Mathai, A. M.; Moschopoulos, P.; and Pederzoli, G. 
 * "Distance between Random Points in a Cube." J. Statistica 59, 61-81, 1999.
 * but with 'corrected typos'
 * 
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the size of the cube 
 * (i.e., the length of any side). 
 * @return The density at $t.
 * @see  http://mathworld.wolfram.com/CubeLinePicking.html
 */
double CubeDistancePDF(double t, double* parameters)
{
    double L = M_SQRT2;
    double L3 = sqrt(3);
    double t2;
    double tmp;
    t = t/parameters[0]; /* rescale points to unit cube */
    t2 = t*t;
    
    /* three cases */
    if (t <= 1)
    {
        return( -t2*( (t-8)*t2 + M_PI*(6*t - 4) )/parameters[0] );
    } 
    else if ( t <= L ) 
    {
        tmp = sqrt(t2-1.0);
        /* return( ( 4.0 - M_PI - 0.5)  ); */
        return( 2.0*t*( 
                       t2*(t2-8.0*tmp+3.0)
                       -4.0*tmp
                       +12.0*t2*acos(1.0/t)    
                       +M_PI*(3.0-4.0*t)
                       -0.5
                       )/parameters[0]  );
    } else 
    {
        tmp = sqrt(t2-2.0);
        return( t*(
                   (1.0+t2)*( 6.0*M_PI + 8.0*tmp - 5.0 - t2)
                   -16*t*asin( 1.0/sqrt(2.0 - 2.0/t2) )
                   +16.0*t*atan( t*tmp )
                   -24.0*(1.0+t2)*atan( tmp )
                   )/parameters[0] );
    }
    
}


/**
 * Implements the CDF of the distance between two random points within a cube.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>  
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @todo Write up how to derive the CDF.
 * @return The cumulative density at $t.
 */
double CubeDistanceCDF(double t, double* parameters)

{
 
    double t2;
    double t3;
    double t4;
    double t6;

    t = t / parameters[0]; /* rescale points to unit cube */    
    
    t2 = t*t;
    t3 = t2*t;
    t4 = t2 * t2;
    t6 = t4 * t2;
    /* three cases */
    
    if (t <= 1)
    {
        return (t3 * (5 * M_PI *(8 - 9 * t) + (48 - 5 * t) * t2)) / 30.;
    } 
    else if (t <= M_SQRT2) 
    {
        return  (
                    3 + 10 * t6 +24 * sqrt(-1 + t2) - 
                    5 * M_PI * (3 + 2*t2*(-9 + 8*t)) + 
                    t4 * (45 - 96 * sqrt(-1 + t2)) - 
                    3 * t2 * (5 + 36 * sqrt(-1 + t2)) + 
                    180 * t4 * acos(1 / t)
                ) / 30.;
    } 
    else 
    {
       
        return  (
                    3 * (9 + 5 * M_PI) + 15 * (-5 + 6 * M_PI) * t2 + 
                    45 * (-1 + M_PI) * t4 - 5 * t6 + 
                    12 * sqrt(-2 + t2) + 108 * t2 * sqrt(-2 + t2) + 
                    48 * t4 * sqrt(-2 + t2) + 
                    30 * atan((-2 + t) / sqrt(-2 + t2)) - 
                    30 * atan((2 + t) / sqrt(-2 + t2)) - 
                    20 * t2 * (8 * t * asin(1 / sqrt(2 - 2 / t2)) + 
                    9 * (2 + t2) * atan(sqrt(-2 + t2)) - 
                    8 * t * atan(t * sqrt(-2 + t2)))
                ) / 30.;  
    }
}


/**
 * Calculates the mean of the distance between two random points within a cube.
 *
 * From Mathai, A. M.; Moschopoulos, P.; and Pederzoli, G. 
 * "Distance between Random Points in a Cube." J. Statistica 59, 61-81, 1999.
 * but with 'corrected typos'
 * 
 * @param $parameters $parameters[0] is the size of the cube 
 * (i.e., the length of any side).
 * @return The mean distance between two points in a unit cube
 * @see  http://mathworld.wolfram.com/CubeLinePicking.html
 */
double CubeDistanceMean(double* parameters)
{
    double L = M_SQRT2;
    double L3 = sqrt(3);
    double tmp;
    
    /* Robbin's constant */
    return(parameters[0] * ( 4 + 17.0*M_SQRT2 - 6*sqrt(3) + 21*log(1+M_SQRT2) 
                            + 42.0*log(2+sqrt(3)) - 7*M_PI )/105.0);
}



/**
 * Calculates the variance of the distance between two 
 * random points within a cube.
 *
 * This was calculated numerically.
 * 
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @todo Try to derive a value algebaricaly 
 * @return The variance of the distances between two points in a unit cube
 */
double CubeDistanceVar(double* parameters)
/* mean distance between two points in a unit cube */
/*    calculated numerically */
{
    return(parameters[0]*parameters[0]*0.062143604936);
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points within a cube.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points within a cube. 
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void CubeDistanceSupport(double *t, double *parameters)
{
    /* cube, side length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0]*sqrt(3);
}


/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to by $error_str
 */
void CubeDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* cube, side length parameters[0] */
    *result=0; 
}
