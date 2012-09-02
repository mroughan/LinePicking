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
#include <stdio.h>

#include "LinePickingData.h"
#include "HyperSphereGeodesic.h"
 
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
    return (pow(M_PI, -1. / 2.) * 
           tgamma((1. + n) / 2.) * 
           tgamma(n / 2.) * 
           pow(sin(t / r), n - 1)) / (r * pow(tgamma(n / 2.), 2.));
}


/**
 * Will implement the CDF of the distance between two random points
 * on a hyper-sphere measured along a geodesic.
 *
 * @todo Implement
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The cumulative density at $t.
 */
double HyperSphereGeodesicDistanceCDF(double t, double* parameters)
{    
    double n = ceil(parameters[0]); 
    double r = parameters[1];

    return -1;;
}


/**
 * Calculates the mean distance between two random points on a hyper-sphere 
 * measured along a geodesic.
 *
 * @todo Implement
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The mean distance between two random points on a hyper-sphere.
 */
double HyperSphereGeodesicDistanceMean(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 1;
    
    return -1;
}


/**
 * Calculates the variance of distances between two random points on 
 * a hyper-sphere measured along a geodesic.
 *
 *
 * @todo Implement
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The variance of distances between two random points on a hyper-sphere.
 */
double HyperSphereGeodesicDistanceVar(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 2;
        
    return -1;
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
