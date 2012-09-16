/* HyperSphereGeodesic.c	
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
#include "HyperSphereGeodesic.h"
#include "HyperGeometric.h"
 
LinePickingData HyperSphereGeodesicDistanceData =
{
   "hyper-sphere geodesic",
    "hyper-sphere geodesic, with dimension parameters[0],"
    " and radius parameters[1]",
    2,
    {2, 1}
};


/**
 * Implements the PDF of the distance between two random points on a 
 * hyper-sphere measured along a geodesic.
 *
 * @todo reference us
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The density at $t.
 */
double HyperSphereGeodesicDistancePDF(double t, double* parameters)
{
    
    double n = ceil(parameters[0]); 
    double r = parameters[1];
    
   
   /* return (pow(M_PI, -1. / 2.) * 
           tgamma((1. + n) / 2.) * 
           tgamma(n / 2.) * 
           pow(sin(t / r), n - 1)) / (r * pow(tgamma(n / 2.), 2.)); */
    
    return (tgamma((1 + n) / 2.) * pow(sin(t / r), n - 1)) /
            (sqrt(M_PI) * r * tgamma(n/2.));
}


/**
 * Implements the CDF of the distance between two random points
 * on a hyper-sphere measured along a geodesic.
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The cumulative density at $t.
 */
double HyperSphereGeodesicDistanceCDF(double t, double* parameters)
{    
    double n = ceil(parameters[0]); 
    double r = parameters[1];
    
    
   /* return 0.5 - ((pow(M_PI, -0.5) * cos(t / r) * 
                  tgamma(0.5 + 0.5 * n) *
                  tgamma(n / 2.) *
                  HyperGeometric2F1(0.5,1 - n / 2., 1.5, 
                                    pow(cos(t / r), 2)) *
                  pow(sin(t / r), n)) / 
                    (pow(tgamma(0.5 * n), 2) * pow(pow(sin(t / r),2.),n/2.)));*/
    /*
   return 0.5 - ((cos(t / r) * tgamma((1 + n) / 2.) *
                  HyperGeometric2F1(0.5, 1 - n / 2., 1.5, 
                                    pow(cos(t / r), 2))
            * pow(sin(t/r),n))/
            (sqrt(M_PI)*tgamma(n / 2.) * pow(pow(sin(t / r), 2), n / 2.)));*/
    
    return 0.5 - ((cos(t / r) * tgamma((1 + n)/2.) * 
                   HyperGeometric2F1(0.5, 1 - n / 2., 1.5, 
                                     pow(cos(t / r), 2))) /
                  (sqrt(M_PI) * tgamma(n/2.)));
}


/**
 * Calculates the mean distance between two random points on a hyper-sphere 
 * measured along a geodesic.
 *
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The mean distance between two random points on a hyper-sphere.
 */
double HyperSphereGeodesicDistanceMean(double* parameters)
{ 
    double r = parameters[1];
    
    return (M_PI * r) / 2.0;
}


/**
 * Calculates the variance of distances between two random points on 
 * a hyper-sphere measured along a geodesic.
 *
 *
 * @todo Implement
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The variance of distances between two random points 
 * on a hyper-sphere.
 */
double HyperSphereGeodesicDistanceVar(double* parameters)
{
    int dim = round(parameters[0]);
    double r = parameters[1];
    int n;
    
    double an2 = pow(r, 2) * pow(M_PI, 2) / 4.; 
    double an1 = pow(r, 2) * pow(M_PI, 2) / 12.; 
    double an = 0;
    
    if (dim == 0) return an2;
    if (dim == 1) return an1;
    
    for (n = 2; n <= dim; n++)
    {
        an = an2 - 2 * (pow(r,2) / pow((n - 1),2));
        an2 = an1;
        an1 = an;
    }
    
    return an;
}



/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random on a hyper-sphere measured along a geodesic.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points
 * on a hyper-sphere measured along a geodesic.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void HyperSphereGeodesicDistanceSupport(double *t, double *parameters)
{
    /* hyper-sphere, with dimension parameters[0], and radius parameters[1] */
    t[0] = 0;
    t[1] = M_PI * parameters[1];
}


/**
 * Determines if the parameters supplied are valid input 
 * to the other functions implemented in this file.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere under 
 * consideration and $parameters[1] is the radius of the hyper-sphere under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 * The only condition this function needs to check is that the dimesnion
 * of the hyper-sphere consider is at least 1.
 */
void HyperSphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    /** @todo check if the 1-sphere is correct if not we
     * need to either limit the parameter here to 2 or above or branch 
     * the code 
     */
    *result=0;
    /* hyper-shpere, with dimension parameters[0], and radius parameters[1] */
    if (parameters[0] < 1) 
    {
        sprintf(error_str, 
                "LinePickingCheckParameters: hyper-sphere geodesic ,"
                " must have parameter[0]>=1, but  parameter[0]=%lf", 
                parameters[0]);
        *result=2;
    }
}

/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The number of coordinates used given input problem and parameters.
 */
void HyperSphereGeodesicDistanceNcoords(int *Ncoords, char **CoordSystem, 
                                        double* parameters) 
{
    *Ncoords = parameters[0]+1; 
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
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The set of points.
 */
void HyperSphereGeodesicDistanceSimPoints(double **points, int *Npoints, 
                                          int *Ncoords, double* parameters)
{
    int i, j;
    double *normals;
    double sum;
    
    /* 
     * not the most efficient use of normal random number 
     * generation, but it should work for all n-spheres 
     */
    normals = (double *) malloc(sizeof(double)*(*Ncoords));
    for (i=0; i<*Npoints; i++)
    {
	/* generate n normal random variables */
	rand_normal(*Ncoords, normals);

	/* normalize them so that they lie on the (n-1)-sphere */
	sum = 0;
	for (j=0; j<*Ncoords; j++) 
        sum += normals[j]*normals[j];
	for (j=0; j<*Ncoords; j++) 
        points[i][j] = parameters[1]*normals[j]/sqrt(sum);
    }
    free(normals);
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The distance between the two points
 * @todo Implement this.
 */
double HyperSphereGeodesicDistanceMetric(int Ncoords, double *point1, 
                                         double* point2, double* parameters)
{
    double d = DistanceEuclidean(Ncoords, point1, point2);
    return parameters[1] * 2 * asin(d/ (2 * parameters[1])); 
}
