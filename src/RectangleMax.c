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
#include <stdlib.h>
#include <stdio.h>

#include "LinePickingData.h"
#include "metrics.h"
#include "Rand.h"
#include "RectangleMax.h"

LinePickingData RectangleMaxDistanceData =
{
    "rectangle max",
    "rectangle max, side lengths parameters[0], parameters[1]",
    2,
    {2,1},
};

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
    double a2;
    double b2;
    double t2 = t*t;
    double tmp;
    
    /* make sure a < b */
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
    else return 0;
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
    } else {
	return 0;
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

/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters $parameters[0] and $parameters[1] are the lengths of the 
 * sides of the rectangle under consideration.
 * @return The number of coordinates used given input problem and parameters.
 */
void RectangleMaxDistanceNcoords(int *Ncoords, char **CoordSystem, 
                                 double* parameters) 
{
    *Ncoords=2;
    *CoordSystem="Euclidean";
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameters[0] and $parameters[1] are the lengths of the 
 * sides of the rectangle under consideration.
 * @return The set of points.
 */
void RectangleMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, 
                                   double* parameters)
{
    int i, j;
    
    for (i=0; i<*Npoints; i++)
    {
        for (j=0; j<*Ncoords; j++)
        {
            points[i][j] = parameters[*Ncoords-j-1]*drand48();
            /* parameters in opposite order, because give height first */
        }
    }
}

/**
 * Calculate distance (using correct metric) between 2 points
 *
 * @param $Ncoords = number of coordinates for each point
 * @param $points1 = coordinates of first point
 * @param $points2 = coordinates of second point
 * @param $parameters $parameters[0] and $parameters[1] are the lengths of the 
 * sides of the rectangle under consideration.
 * @return The distance between the two points
 */
double RectangleMaxDistanceMetric(int Ncoords, double *point1, double* point2, 
                                  double* parameters)
{
    return DistanceMax(Ncoords, point1, point2);
}
