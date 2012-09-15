/* HyperCubeMax.c	
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
#include "HyperGeometric.h"
#include "HyperCubeMax.h"


LinePickingData HyperCubeMaxDistanceData =
{
    "hyper-cube max",
    "hyper-cube, dimensions  parameters[0], side length parameters[1]",
    2,
    {3,1}
};


/**
 * Implements the PDF of the distance between two random points within a 
 * hyper-cube using the max metric.
 *
 * 
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The density at $t.
 */
double HyperCubeMaxDistancePDF(double t, double* parameters)
{
    double n = parameters[0];
    double L = parameters[1];
    
    return n * pow(2.0 / L, n) * 
               pow (t - ((t*t) / (2.0 * L)), n -1) * 
               (1.0 - (t / L));
}


/**
 * Implements the CDF of the distance between two random points within a 
 * hyper-cube using the max metric.
 *
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The cumulative density at $t.
 */
double HyperCubeMaxDistanceCDF(double t, double* parameters)
{
    double n = parameters[0];
    double L = parameters[1];
    
    return pow((2.0 / L)* (t - ((t*t) / (2.0 * L))), n);
}


/**
 * Calculates the mean of the distance between two random points within a 
 * hyper-cube using the max metric.
 *
 * 
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The mean distance between two points in a unit cube.
 */
double HyperCubeMaxDistanceMean(double* parameters)
{
    double n = parameters[0];
    double L = parameters[1];
    double k = 1; /* mean is first moment */
    
    /* use hyper geometric as incomplete beta function is missing */
    return  pow(2, 2.0 * n + k) * pow (L, k) * n *
            (
                (pow(0.5, k + n) / (k + n)) * 
                HyperGeometric2F1(k + n, 1 - n, k + n + 1, 0.5) -
                ((2.0 * pow(0.5, k + n + 1)) / (k + n + 1)) *
                HyperGeometric2F1(k + n + 1, 1 - n, k + n + 2, 0.5)
             );
            
}



/**
 * Calculates the variance of the distance between two 
 * random points within a hyper-cube using the max metric.
 *
 * 
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The variance of the distances between two points in a unit cube.
 */
double HyperCubeMaxDistanceVar(double* parameters)
{
    double n = parameters[0];
    double L = parameters[1];
    double k = 2; /* second moment */
    double mean = HyperCubeMaxDistanceMean(parameters);
    
    /* 
     * compute E[x^2] - E[X]^2 ie the variance 
     * using hyper geometric as we dont seem to have 
     * incomplete beta function that isnt regularized
     */
    return  pow(2.0, 2.0 * n + k) * pow (L, k) * n *
            (
                (pow(0.5, k + n) / (k + n)) * 
                HyperGeometric2F1(k + n, 1 - n, k + n + 1, 0.5) -
                ((2 * pow(0.5, k + n + 1)) / (k + n + 1)) *
                HyperGeometric2F1(k + n + 1, 1 - n, k + n + 2, 0.5)
             ) - pow(mean, 2.0);
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points within a hyper-cube using the max metric.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points within a cube. 
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void HyperCubeMaxDistanceSupport(double *t, double *parameters)
{
    /* cube, side length parameters[0] */
    t[0] = 0;
    t[1] = parameters[1];
}


/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to by $error_str
 */
void HyperCubeMaxDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* cube, side length parameters[1] */
    *result=0; 
}


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The number of coordinates used given input problem and parameters.
 */
void HyperCubeMaxDistanceNcoords(int *Ncoords, char **CoordSystem, 
                                 double* parameters) 
{
    *Ncoords=parameters[0];
    *CoordSystem="Euclidean";
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The set of points.
 */
void HyperCubeMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, 
                           double* parameters)
{
    int i, j;
    
    for (i=0; i<*Npoints; i++)
    {
        for (j=0; j<*Ncoords; j++)
        {
            /* mxArray is transpose of c matrix */
            points[i][j] = parameters[1]*drand48(); 
        }
    }
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameter[0] is the dimensions of the hyper-cube
 * $parameters[1] is the size of the hyper-cube (i.e., the length of any side). 
 * @return The distance between the two points.
 */
double HyperCubeMaxDistanceMetric(int Ncoords, double *point1, double* point2, 
                          double* parameters)
{
    return DistanceMax(Ncoords, point1, point2);
}
