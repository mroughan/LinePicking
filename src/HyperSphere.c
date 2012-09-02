/* HyperSphere.c	
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
#include <stdio.h>

#include "LinePickingData.h"
#include "HyperSphere.h"
#include "beta.h" 

LinePickingData HyperSphereDistanceData =
{
   "hyper-sphere",
    "hyper-sphere, with dimension parameters[0], and radius parameters[1]",
    2,
    {3, 1}
};



double Cn(double n)
{
    return pow(M_PI, n / 2.0 )/ tgamma((n / 2.0)+ 1);       
}


/**
 * Implements the PDF of the distance between two random points on a 
 * hyper-sphere.
 *
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The density at $t.
 */

double HyperSphereDistancePDF(double t, double* parameters)
{
    /** @todo check if the 1-sphere is correct if not we
     * need to either limit the parameter here to 2 or above or branch 
     * the code 
     */
    
    double n = ceil(parameters[0]); 
    double r = parameters[1];
    double theta = acos(1. - ((t * t) / (2. * r * r)));
    double dtheta = fabs(2.0 / sqrt((4.0 * r * r) - (t * t)));
    double c = (2 * pow(M_PI, 2.5 - 0.5 * n) * pow(tgamma(n / 2.), 2.)) /
                tgamma((1. + n) / 2.);
    return ((2 * M_PI * pow(sin(theta), n - 1 ) / Cn(n - 2)) * dtheta) / c; 
    
    /* could equally use the following code as it is a simplification of all
     * the abpve 
     */
    /*
     return (pow (M_pi, -1. /2.)* d * pow(1 - pow(1. - (pow(d,2) / 2.) / 
        pow(R,2),2), (n - 2) / 2.) * tgamma((n + 1.) / 2.) * tgamma(n / 2.)) /
        (pow(R,2)*pow(tgamma(n / 2.),2))
     */
}


/**
 * Will implement the CDF of the distance between two random points
 * on a hyper-sphere.
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The cumulative density at $t.
 */
double HyperSphereDistanceCDF(double t, double* parameters)
{    
    double n = ceil(parameters[0]); 
    double r = parameters[1];

    return -1;;
}


/**
 * Calculates the mean distance between two random points on a hyper-sphere.
 *
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The mean distance between two random points on a hyper-sphere.
 */
double HyperSphereDistanceMean(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 1;
    
    return -1;
}


/**
 * Calculates the variance of distances between two random points on 
 * a hyper-sphere.
 *
 *
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere. 
 * @return The variance of distances between two random points on a hyper-sphere.
 */
double HyperSphereDistanceVar(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 2;
        
    return -1;
}



/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random on a hyper-sphere.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points
 * on a hyper-sphere.
 * @param $parameters $parameters[0] is the dimension of the hyper-sphere and 
 * $parameters[1] is the radius of the hyper-sphere.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void HyperSphereDistanceSupport(double *t, double *parameters)
{
    /* hyper-sphere, with dimension parameters[0], and radius parameters[1] */
    t[0] = 0;
    t[1] = 2*parameters[1];
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
void HyperSphereDistanceCheckParameters(double *parameters, int *result, 
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
                "LinePickingCheckParameters: hyper-sphere,"
                " must have parameter[0]>=1, but  parameter[0]=%lf", 
                parameters[0]);
        *result=2;
    }
}
