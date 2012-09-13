/* CubeMax.c	
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
#include "CubeMax.h"

LinePickingData CubeMaxDistanceData =
{
    "cube max metric",
    "cube, side length parameters[0]",
    1,
    {1}
};


/**
 * Implements the PDF of the distance between two random points within a cube
 * using the max metric.
 *
 * 
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the size of the cube 
 * (i.e., the length of any side). 
 * @return The density at $t.
 */
double CubeMaxDistancePDF(double t, double* parameters)
{
    double L = parameters[0];
   
    return (6 * (L - t) * pow(t, 2) * pow(-2 * L + t, 2)) / pow(L, 6);
}


/**
 * Implements the CDF of the distance between two random points within a cube
 * using the max metric.
 *
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @return The cumulative density at $t.
 */
double CubeMaxDistanceCDF(double t, double* parameters)
{
    double L = parameters[0];
    
    return (pow(2 * L - t, 3) * pow(t, 3)) / pow(L,6);
}


/**
 * Calculates the mean of the distance between two random points within a cube
 * using the max metric.
 *
 * 
 * @param $parameters $parameters[0] is the size of the cube 
 * (i.e., the length of any side).
 * @return The mean distance between two points in a unit cube.
 */
double CubeMaxDistanceMean(double* parameters)
{
    double L = parameters[0];
    
    return (19 * L) / 35.;
}



/**
 * Calculates the variance of the distance between two 
 * random points within a cube using the max metric.
 *
 * 
 * @param $parameters $parameters[0] is the size of the cube
 * (i.e., the length of any side).
 * @return The variance of the distances between two points in a unit cube.
 */
double CubeMaxDistanceVar(double* parameters)
{
    double L = parameters[0];
    
    return (201 * pow(L, 2)) / 4900.;
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points within a cube using the max metric.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points within a cube. 
 * @param $parameters $parameters[0] is the size of the cube.
 * (i.e., the length of any side).
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void CubeMaxDistanceSupport(double *t, double *parameters)
{
    /* cube, side length parameters[0] */
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
void CubeMaxDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* cube, side length parameters[0] */
    *result=0; 
}


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters parameters[0] is the length of the sides of 
 * the cube under consideration.
 * @return The number of coordinates used given input problem and parameters.
 */
void CubeMaxDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters) 
{
    *Ncoords=3;
    *CoordSystem="Euclidean";
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters parameters[0] is the length of the sides of 
 * the cube under consideration.
 * @return The set of points.
 */
void CubeMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, 
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
 * @param $parameters parameters[0] is the length of the sides of 
 * the cube under consideration.
 * @return The distance between the two points.
 */
double CubeMaxDistanceMetric(int Ncoords, double *point1, double* point2, 
                          double* parameters)
{
    return DistanceMax(Ncoords, point1, point2);
}
