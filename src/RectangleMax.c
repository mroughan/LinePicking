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
    
    /* two cases */
    if (t <= H)
    {
        return (2 * t * (4 * H * L - 3 * H * t - 3 * L * t + 2 * t2)) /
                (H2 * L2);
        
    } 
    else if (t <= L) 
    {
        return (2 * (L - t)) / L2;
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
    
    /* two cases */
    if (t <= H)
    {
        return ((2 * H - t) * (2 * L - t) * t2) / (H2 * L2);
    } 
    else if (t <= L) 
    {
        return((2 * L - t) * t) / L2;
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
    
    double L = parameters[0];
    double H = parameters[1];
   
    return -(pow(H, 3) - 5 * pow(H, 2) * L - 10*pow(L, 3)) / (30. * pow(L, 2));
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
    double L = parameters[0];
    double H = parameters[1];
    double tmp;
    
    if (H > L) 
    {
        tmp = L;
        L = H;
        H = tmp;
    }
    
    return -(pow(H, 6) - 10 * pow(H, 5) * L + 
             55 * pow(H, 4) * pow(L, 2) - 140 * pow(H, 3) * pow(L, 3) + 
             100 * pow(H, 2) * pow(L, 4) - 50 * pow(L, 6)) /
                (900. * pow(L, 4));

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