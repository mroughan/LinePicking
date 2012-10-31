/* Line.c	
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
#include <stdlib.h>
#include <stdio.h>

#include "LinePickingData.h"
#include "metrics.h"
#include "Rand.h"
#include "Line.h"

LinePickingData LineDistanceData =
{
    "line",
    "line, length parameters[0]",
    1,
    {1}
};

/**
 * Implements the PDF of the distance between two random points on a line.
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of the line. 
 * @return The density at $t.
 * @see http://mathworld.wolfram.com/LineLinePicking.html 
 */
double LineDistancePDF(double t, double* parameters)
{
    double L = parameters[0];
    
    
    return(2*(1-t/L)/L);
}

/**
 * Implements the CDF of the distance between two random points on a line.
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of the line. 
 * @return The cumulative density at $t.
 * @see http://mathworld.wolfram.com/LineLinePicking.html 
 */
double LineDistanceCDF(double t, double* parameters)
{
    double L = parameters[0];
    t = t / L;
    
    return(t*(2.0-t));
    
}


/**
 * Calculates the mean of the distance between two random points on a line.
 * 
 * @param $parameters $parameters[0] is the length of the line.  
 * 
 * @return The mean distance between two points on a line 
 * @see  http://mathworld.wolfram.com/LineLinePicking.html 
 */
double LineDistanceMean(double* parameters)
{
    double L = parameters[0];
    return(L * 1.0 / 3.0);
}


/**
 * Calculates the variance of the distances between two random points on a line.
 * 
 * Currently calculated numerically.
 * @param $parameters $parameters[0] is the length of the line.   
 *
 * @return The variance of distances between two points on a line 
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double LineDistanceVar(double* parameters)
{
    double L = parameters[0];
    return(L * L * 1.0 / 18.0);
}

/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a line
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a line. 
 * @param $parameters $parameters[0] is the length of the line.   
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void LineDistanceSupport(double *t, double *parameters)
{
    /* line, length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0];
}

/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters parameters[0] is the length of the line under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 */

void LineDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* line, length parameters[0] */
    *result=0;
}

/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters parameters[0] is the length of the line under
 * consideration.
 * @return The number of coordinates used given input problem and parameters.
 */
void LineDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters) 
{
    *Ncoords=1;
    *CoordSystem="Euclidean";
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point
 * @param $parameters parameters[0] is the length of the line under
 * consideration.
 * @return The set of points.
 */
void LineDistanceSimPoints(double **points, int *Npoints, int *Ncoords, 
                           double* parameters)
{
    int i, j;
    
    for (i=0; i<*Npoints; i++)
    {
        for (j=0; j<*Ncoords; j++)
        {
             /* mxArray is transpose of c matrix */
            points[i][j] = parameters[0]*drand48();
        }
    }
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters parameters[0] is the length of the line under
 * consideration.
 * @return The distance between the two points.
 */
double LineDistanceMetric(int Ncoords, double *point1, double* point2, 
                          double* parameters)
{
    return DistanceEuclidean(Ncoords, point1, point2);
}
