/* Square.c	
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
#include "Square.h"

LinePickingData SquareDistanceData =
{
    "square",
    "square, with side length parameters[0]",
    1,
    {1}
};


/**
 * Implements the PDF of the distance between two random points on a square.
 *
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the size of the square. 
 * @return The density at $t.
 * @see http://mathworld.wolfram.com/SquareLinePicking.html 
 */
double SquareDistancePDF(double t, double* parameters)
{
    /* double L = M_SQRT2; */
    double t2;
    t = t/parameters[0]; /* rescale points to unit square */
    t2 = t*t;
    
    /* two cases */
    if (t <= 1)
        return 2 * t * (t2 - 4 * t + M_PI) / parameters[0];
    else 
        return  2 * t * (4 * sqrt(t2-1) - 
                         (t2 + 2 - M_PI) - 
                         4 * atan(sqrt(t2 - 1))) / parameters[0];
}


/**
 * Implements the CDF of the distance between two random points on a square.
 *
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the size of the square. 
 * @return The cumulative density at $t.
 * @see http://mathworld.wolfram.com/SquareLinePicking.html 
 */
double SquareDistanceCDF(double t, double* parameters)
{
    /* double L = M_SQRT2; */
    double t2, tmp;
    t = t/parameters[0]; /* rescale points to unit square */
    t2 = t*t;
    
    /* two cases */
    if (t <= 1) 
        return pow(t, 4.) / 2 - 8. * pow(t, 3.) / 3 + M_PI * t2;
    else 
    {
        tmp = sqrt(t2 - 1);
        return  -pow(t, 4.) / 2 - 4 * t2 * atan(tmp) + 
                    4.0 * (2.0 * t2 + 1) * tmp /
                    3.0 + (M_PI - 2) * t2 + 1.0 / 3.0;
    }
}


/**
 * Calculates the mean of the distance between two random points on a square.
 *
 * @param $parameters $parameters[0] is the size of the square.  
 * 
 * @return The mean distance between two random points on a square. 
 * @see http://mathworld.wolfram.com/SquareLinePicking.html 
 */
double SquareDistanceMean(double* parameters)
{
    return parameters[0] * (2 + M_SQRT2 + 5 * asinh(1)) / 15.0;
}


/**
 * Calculates the variance of the distances between two random points 
 * on a square.
 *
 * @param $parameters $parameters[0] is the size of the square.  
 * 
 * @return The variance of the distances between two points random points
 * on a square. 
 * @see http://mathworld.wolfram.com/SquareLinePicking.html 
 */
double SquareDistanceVar(double* parameters)
{
    double tmp = asinh(1);
    return parameters[0] * parameters[0] * 
            (69 - 4 * M_SQRT2 - 10.0 * 
            (2 + M_SQRT2) * tmp - 25 * tmp * tmp) / 225.0;
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a square.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a square. 
 * @param $parameters $parameters[0] is the size of the square.   
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void SquareDistanceSupport(double *t, double *parameters)
{
    /* square, with side length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0]*sqrt(2);
}

/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters parameters[0] is the length of the sides of 
 * the square under consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 */
void SquareDistanceCheckParameters(double *parameters, int *result, 
                                   char *error_str)
{
    /* square, with side length parameters[0] */
    *result=0;
}


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters parameters[0] is the length of the sides of 
 * the square under consideration.
 */
void SquareDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters) 
{
    *Ncoords=2;
    *CoordSystem="Euclidean";
}

/**
 * Simulate a set of points from the problem of interest
 *
 * @param $points = Npoints x Ncoords array of coordinates, in the correct system
 * @param $Npoints = number of points to generate
 * @param $Ncoords = number of coordinates for each point
 * @param $parameters parameters[0] is the length of the sides of 
 * the square under consideration.
 */
void SquareDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters)
{
    int i, j;
    
    for (i=0; i<*Npoints; i++)
    {
	for (j=0; j<*Ncoords; j++)
	{
	    points[i][j] = parameters[0]*drand48(); /* mxArray is transpose of c matrix */
	}
    }
}

/**
 * Calculate distance (using correct metric) between 2 points
 *
 * @param $Ncoords = number of coordinates for each point
 * @param $points1 = coordinates of first point
 * @param $points2 = coordinates of second point
 * @return The distance between the two points
 */
double SquareDistanceMetric(int Ncoords, double *point1, double* point2)
{
    return DistanceEuclidean(Ncoords, point1, point2);
}
