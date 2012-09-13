/* SphereGeodesic.c	
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
#include "SphereGeodesic.h"

LinePickingData SphereGeodesicDistanceData =
{
    "sphere geodesic",
    "sphere geodesic, with radius parameters[0]",
    1,
    {1}
};

/**
 * Implements the PDF of the distance between two random points on the 
 * surface of a sphere measured around the surface of the sphere
 * (i.e., a geodesic).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>.
 * @todo Write up the derivation.
 * @param $s The distance to calculate the density for.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The density at $s.
 */
double SphereGeodesicDistancePDF(double s, double* parameters)
{
    double R = parameters[0];
        
    return sin(s / R) / ( 2. * R);
}


/**
 * Implements the CDF of the distance between two random points on the 
 * surface of a sphere measured around the surface of the sphere
 * (i.e., a geodesic).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>.
 * @todo Write up the derivation.
 * @param $s The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The cumulative density at $s.
 */
double SphereGeodesicDistanceCDF(double s, double* parameters)
{
    double R = parameters[0];
    
    return pow(sin(s / (2. * R)), 2);
}


/**
 * Calculates the mean of the distance between two random points on the surface 
 * of a sphere measured around the surface of the sphere (i.e., a geodesic).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>.
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The mean of the distance between two random points on the surface 
 * of a sphere measured around the surface of the sphere (i.e., a geodesic).
 */
double SphereGeodesicDistanceMean(double* parameters)
{
    double R = parameters[0];
    
    return (M_PI * R) / 2.;
}


/**
 * Calculates the variance of the distances between two random points on 
 * the surface of a sphere measured around the surface of the sphere
 * (i.e., a geodesic).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au>.
 * @todo Write up the derivation.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The mean of the distance between two random points on the surface 
 * of a sphere measured around the surface of the sphere (i.e., a geodesic).
 */
double SphereGeodesicDistanceVar(double* parameters)
{
    double R = parameters[0];
    
    return ((-8 + M_PI * M_PI) * R * R) / 4.;
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on the surface of a sphere measured around the surface of 
 * the sphere (i.e., a geodesic).
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on the surface 
 * of a sphere measured around the surface of the sphere (i.e., a geodesic).
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void SphereGeodesicDistanceSupport(double *t, double *parameters)
{
    double R = parameters[0];

    t[0] = 0;
    t[1] = R * M_PI;
}


/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters parameters[0] is the radius of the sphere under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 */
void SphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* no extra checking required */
    *result=0;
}

/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters $parameters[0] is the diameter of the sphere under
 * consideration.
 * @return The number of coordinates used given input problem and parameters.
 */
void SphereGeodesicDistanceNcoords(int *Ncoords, char **CoordSystem, 
				   double* parameters) 
{
    *Ncoords = 3; 
    /* We could use spherical coordinates, but why?" */
    *CoordSystem="Euclidean"; 
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameters[0] is the diameter of the sphere under
 * consideration. 
 * @return The set of points.
 */
void SphereGeodesicDistanceSimPoints(double **points, int *Npoints, 
                                     int *Ncoords, double* parameters)
{
    int i, j;
    double *normals;
    double sum;
    
    normals = (double *) malloc(sizeof(double)*(*Ncoords));
    for (i=0; i<*Npoints; i++)
    {
        /* generate n normal random variables */
        rand_normal(*Ncoords, normals);
        
        /* normalize them so that they lie on the (n-1)-sphere */
        sum = 0;
        for (j=0; j<*Ncoords; j++) 
            sum += normals[j]*normals[j];
        for (j=0; j<*Ncoords; j++) points[i][j] = 
            parameters[0]*normals[j]/sqrt(sum);
    }
    free(normals);
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[0] is the diameter of the sphere under.
 * consideration.
 * @return The distance between the two points.
 * @todo Implement this.
 */
double SphereGeodesicDistanceMetric(int Ncoords, double *point1, double* point2, 
                                    double* parameters)
{
    double d = DistanceEuclidean(Ncoords, point1, point2);
    return parameters[0] * 2 * asin(d/ (2 * parameters[0])); 
}
