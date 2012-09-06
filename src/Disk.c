/* Disk.c	
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
#include "Disk.h"

char *DiskDistanceName = "disk";
char *DiskDistanceDescription = "disk, with radius parameters[0]";
int DiskDistanceNpar = 1;

LinePickingData DiskDistanceData =
{
    "disk",
    "disk, with radius parameters[0]",
    1,
    {1}
};


/**
 * Implements the PDF of the distance between two random points on a disk.
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters[0] The radius of the disk. 
 *
 * @return The density at $t.
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double DiskDistancePDF(double t, double* parameters)
{
    double r = parameters[0];
    /* double d = 2*r; */
    double r2 = r*r;
    double t2 = t*t;			     
    double part1, part2, c;
    
    
    /* two cases */
    c = acos(t/(2*r));
    part1 = 4*t*c / (M_PI*r2);
    part2 = 2*t2*sqrt(1 - (t2/(4*r2)))/(M_PI*r*r2);
    return(part1 - part2);
}


/**
 * Implements the CDF of the distance between two random points on a disk.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>  
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the radius of the disk. 
 * @todo Write up how to derive the CDF.
 * @return The cumulative density at $t.
 */
double DiskDistanceCDF(double t, double* parameters)
{    
    double R = parameters[0];
    double R2 = R*R;
    double R3 = R2 * R;
    double t2 = t*t;			     
    double t3 = t2 * t;
    
    return  (
                -(sqrt(4 - t / R2) * (2 * R2 * t + t3)) / 4. + 
                2 * R * t2 * acos(t / (2. * R)) + 
                2 * R3 * asin(t / (2. * R))
            ) / (M_PI * R3);
}


/**
 * Calculates the mean of the distance between two random points on a disk.
 * 
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $parameters $parameters[0] is the radius of the disk.  
 * 
 * @return The mean distance between two points on a disk. 
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double DiskDistanceMean(double* parameters)
{
    return(parameters[0]*128.0/(45.0*M_PI));
}


/**
 * Calculates the variance of the distances between two random points on a disk.
 * 
 * Currently calculated numerically.
 * @param $parameters $parameters[0] is the radius of the disk.   
 *
 * @return The variance of distances between two points on a disk. 
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 * @todo Derive an algebraic expression. 
 */
double DiskDistanceVar(double* parameters)
{
    return(parameters[0]*parameters[0]*0.180224062826);
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a disk.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a disk. 
 * @param $parameters $parameters[0] is the radius of the disk.   
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void DiskDistanceSupport(double *t, double *parameters)
{
    /* disk, with radius parameters[0] */
    t[0] = 0;
    t[1] = 2*parameters[0];
}


/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters $parameters[0] is the radius of the disk. 
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 */
void DiskDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* disk, with radius parameters[0] */
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
void DiskDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters) 
{
    *Ncoords=2;
    *CoordSystem="Euclidean"; /* We could use cicular coordinates, but why?" */
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameters[0] is the diameter of the disk under
 * consideration. 
 */
void DiskDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters)
{
    int i, j;
    double *normals;
    double sum, u;
    
    /* not the most efficient use of normal random number generation, but it should work for all nballs */
    normals = (double *) malloc(sizeof(double)*(*Ncoords));
    for (i=0; i<*Npoints; i++)
    {
	/* generate n normal random variables */
	rand_normal(*Ncoords, normals);

	/* normalize them so that they lie on the (n-1)-sphere */
	sum = 0;
	for (j=0; j<*Ncoords; j++) sum += normals[j]*normals[j];
	for (j=0; j<*Ncoords; j++) points[i][j] = normals[j]/sqrt(sum);
	
	/* now distribute them through the disk */
	u = pow(drand48(), 1.0 / *Ncoords);
	for (j=0; j<*Ncoords; j++)
	{
	    points[i][j] = parameters[0] * u * points[i][j];
	}
    }
    free(normals);
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[0] is the diameter of the disk under
 * consideration. 
 * @return The distance between the two points.
 */
double DiskDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters)
{
    return DistanceEuclidean(Ncoords, point1, point2);
}
