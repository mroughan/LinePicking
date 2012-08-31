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
#include <stdio.h>

#include "RectangleManhattan.h"

char *RectangleManhattanDistanceName = "rectangle Manhattan";
char *RectangleManhattanDistanceDescription = 
    "rectangle Manhattan, side lengths parameters[0], parameters[1]";
int RectangleManhattanDistanceNpar = 2;


/**
 * Implements the PDF of the distance between two random points on a
 * rectangle measured using the Manhattan metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. You'll save work if 
 * $parameters[0]<=$parameters[1].
 * @return The density at $t.
 */
double RectangleManhattanDistancePDF(double t, double* parameters)
{
    double a = parameters[0];
    double b = parameters[1];
    double t2 = t*t;
    double tmp;
    
    /* make sure a < b */
    if (a > b) 
    {
        tmp = b;
        b = a;
        a = tmp;
    }
    
    /* three cases */ 
    if (t <= a)
    {
        return (2. * t * (6 * a * b - 3 * a * t - 3 * b * t + t2)) / 
                (3. * a * a * b * b);
        
    } 
    else if (t <= b) 
    {
        return 2.0 * (a + 3.0 * b - 3.0 * t) / (3.0 * b * b);
    } 
    else 
    {
        return (2. * pow(a + b - t, 3)) / (3. * a * a * b * b);
        
    }
}


/**
 * Implements the CDF of the distance between two random points on a rectangle
 * measured using the Manhattan metric.
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
    
    double a = parameters[0];
    double b = parameters[1];
    double a2;
    double b2;
    double t2 = t*t;
    double tmp;
    
    /* make sure hieght < length */
    if (a > b) 
    {
        tmp = b;
        b = a;
        a = tmp;
    }
    a2 = a*a;
    b2 = b*b;

    /* three cases */
    if (t <= a)
    {
        return (t2 * (12 * a * b - 4 * (a + b) * t + t2)) / (6. * a2 * b2);
    } 
    else if (t <= b) 
    {
        return  -(a2 + 4 * a * (b - t) + 6 * t * (-2 * b + t)) / (6. * b2);       
        
    }
    else 
    {
        return -(pow(a,4) + 
                 4 * pow(a,3) * (b - t) + 
                 4 * a * pow(b - t,3) + 
                 pow(b - t,4) + 
                 6 * a2 * t * (t -2 * b)) / (6. * a2 * b2);
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
    
    double a = parameters[0];
    double b = parameters[1];
    
    return (a + b)/3.;
    
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
    double b = parameters[0];
    double a = parameters[1];

    return (a * a + b * b) / 18;
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
