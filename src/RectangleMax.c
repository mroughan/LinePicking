/* RectangleMax.c	
 *
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

#include "RectangleMax.h"

char *RectangleMaxDistanceName = "rectangle max";
char *RectangleMaxDistanceDescription = 
    "rectangle max, side lengths parameters[0], parameters[1]";
int RectangleMaxDistanceNpar = 2;


/**
 * Implements the PDF of the distance between two random points on a
 * rectangle measured using the max metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The density at $t.
 */
double RectangleMaxDistancePDF(double t, double* parameters)
{
    double a = parameters[0];
    double b = parameters[1];
<<<<<<< HEAD
    double a2, b2;
    double t2 = t*t;
    double tmp;
    
    /* make sure hieght < length */
=======
    double a2;
    double b2;
    double t2 = t*t;
    double tmp;
    
    /* make sure a < b */
>>>>>>> e33f3bc67bde8ca2f37dda9888e8fc32af16fd2b
    if (a > b) 
    {
        tmp = b;
        b = a;
        a = tmp;
    }
    a2 = a*a;
    b2 = b*b;
    
    b2 = b * b;
    a2 = a * a;
    
    /* two cases */
    if (t <= a)
    {
        return (2 * t * (4 * a * b - 3 * a * t - 3 * b * t + 2 * t2)) /
                (a2 * b2);
        
    } 
    else if (t <= b) 
    {
        return (2 * (b - t)) / b2;
    } 
}


/**
 * Implements the CDF of the distance between two random points on a rectangle
 * measured using the max metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @todo Write up the derivation.
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The cumulative density at $t.
 */
double RectangleMaxDistanceCDF(double t, double* parameters)
{
    
    double a = parameters[0];
    double b = parameters[1];
<<<<<<< HEAD
    double a2, b2;
=======
    double a2;
    double b2;
>>>>>>> e33f3bc67bde8ca2f37dda9888e8fc32af16fd2b
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
    
    b2 = b * b;
    a2 = a * a;
    
    /* two cases */
    if (t <= a)
    {
        return ((2 * a - t) * (2 * b - t) * t2) / (a2 * b2);
    } 
    else if (t <= b) 
    {
        return((2 * b - t) * t) / b2;
    } 
   
}


/**
 * Calculates the mean distance between two random points on a rectangle
 * measured using the max metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The mean distance between two random points on a rectangle.
 */
double RectangleMaxDistanceMean(double* parameters)
{
    
    double b = parameters[0];
    double a = parameters[1];
   
    return -(pow(a, 3) - 5 * pow(a, 2) * b - 10*pow(b, 3)) / (30. * pow(b, 2));
}


/**
 * Calculates the variance of distances between two random points on a 
 * rectangle measured using the max metric.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The variance of distances between two random points on a rectangle.
 */
double RectangleMaxDistanceVar(double* parameters)
{
    double b = parameters[0];
    double a = parameters[1];
    double tmp;
    
    if (a > b) 
    {
        tmp = b;
        b = a;
        a = tmp;
<<<<<<< HEAD
=======
        
>>>>>>> e33f3bc67bde8ca2f37dda9888e8fc32af16fd2b
    }
    
    return -(pow(a, 6) - 10 * pow(a, 5) * b + 
             55 * pow(a, 4) * pow(b, 2) - 140 * pow(a, 3) * pow(b, 3) + 
             100 * pow(a, 2) * pow(b, 4) - 50 * pow(b, 6)) /
                (900. * pow(b, 4));

}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a rectangle measured using the max metric.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a rectangle.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void RectangleMaxDistanceSupport(double *t, double *parameters)
{
    /* rectangle, side lengths parameters[0], parameters[1] */
    t[0] = 0;
    t[1] = parameters[0] > parameters[1] ? parameters[0] : parameters[1];
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
void RectangleMaxDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    /* no further checks needed */
    *result=0;
}
