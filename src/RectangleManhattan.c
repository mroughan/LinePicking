/* RectangleManhattan.c	
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

#include "RectangleManhattan.h"

char *RectangleManhattanDistanceName = "rectangle Manhattan";
char *RectangleManhattanDistanceDescription = 
    "rectangle Manhattan, side lengths parameters[0], parameters[1]";
int RectangleManhattanDistanceNpar = 2;


/**
 * Implements the PDF of the distance between two random points on a
 * rectangle measured using theManhattan metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The density at $t.
 */
double RectangleManhattanDistancePDF(double t, double* parameters)
{
    double H = parameters[0];
    double L = parameters[1];
    double H2 = H*H;
    double L2 = L*L;
    double t2 = t*t;
    double tmp;
    
    /* make sure hieght < length */
    if (H > L) 
    {
        tmp = L;
        L = H;
        H = tmp;
    }
    
   
    
    /* three cases */
    if (t <= H)
    {
        return (2 * t * (6 * H * L - 3 * H * t - 3 * L * t + t2)) / 
                (3. * H2 * L2);
        
    } 
    else if (t <= L) 
    {
        return (2 * (H + 3 * L - 3 * t)) / (3. * L2);
    } 
    else 
    {
        return (2 * pow(H + L - t, 3)) / (3. * H2 * L2);
        
    }
    
}


/**
 * Implements the CDF of the distance between two random points on a rectangle
 * measured using theManhattan metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @todo Write up the derivation.
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The cumulative density at $t.
 */
double RectangleManhattanDistanceCDF(double t, double* parameters)
{
    
    double H = parameters[0];
    double L = parameters[1];
    double H2 = H*H;
    double L2 = L*L;
    double t2 = t*t;
    double tmp;
    
    /* make sure hieght < length */
    if (H > L) 
    {
        tmp = L;
        L = H;
        H = tmp;
    }
    
    /* three cases */
    if (t <= H)
    {
        return (t2 * (12 * H * L - 4 * (H + L) * t + t2)) / (6. * H2 * L2);
    } 
    else if (t <= L) 
    {
        return  -(H2 + 4 * H * (L - t) + 6 * t * (-2 * L + t)) / (6. * L2);       
        
    }
    else 
    {
        return -(pow(H,4) + 
                 4 * pow(H,3) * (L - t) + 
                 4 * H * pow(L - t,3) + 
                 pow(L - t,4) + 
                 6 * H2 * t * (t -2 * L)) / (6. * H2 * L2);
    }
   
}


/**
 * Calculates the mean distance between two random points on a rectangle
 * measured using the Manhattan metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The mean distance between two random points on a rectangle.
 */
double RectangleManhattanDistanceMean(double* parameters)
{
    
    double L = parameters[0];
    double H = parameters[1];
    
    return (H + L)/3.;
    
}


/**
 * Calculates the variance of distances between two random points on a 
 * rectangle measured using the Manhattan metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The variance of distances between two random points on a rectangle.
 */
double RectangleManhattanDistanceVar(double* parameters)
{
    double L = parameters[0];
    double H = parameters[1];
    double tmp;
    
    if (H > L) 
    {
        tmp = L;
        L = H;
        H = tmp;
    }
    
    return (2 * pow(H, 5) + 
            14 * pow(H, 4) * (L - 1) -
            28 * pow(H, 3) * (L - 2) * L + 
            105 * pow(L, 4) + 
            35 * pow(H, 2) * pow(L, 2) * (4 * L - 1)) / 
                (1890. * pow(L,2));
    
    
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a rectangle measured using the Manhattan metric.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a rectangle.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void RectangleManhattanDistanceSupport(double *t, double *parameters)
{
    /* rectangle, side lengths parameters[0], parameters[1] */
    t[0] = 0;
    t[1] = parameters[0] + parameters[1];
}


/**
* Intended to determine if the parameters supplied are valid input 
* to the other functions implemented in this file. However as 
* the calling function checks that the supplied parameters are positive 
* this is merely a place holder to allow for a complete implementation 
* in geometries that have more complex relationships between parameters.
*
* @param $parameters  parameters[0] and parameters[1] are the lengths 
* of the sides of the rectangle under consideration.
* @param $result Pointer to storage for an integer indicating any errors  
* in the supplied parameters.
* @param $error_str Pointer to storage for a message explaining any errors
* in the supplied parameters. 
* @return Any error conditions are indicated by placing a value other than 0 
* in the location pointed to by $result and a message explaining the error 
* is copied in to the location pointed to $error_str 
*/
void RectangleManhattanDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    /* no further checks needed */
    *result=0;
}