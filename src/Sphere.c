/* Sphere.c	
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

#include "LinePickingData.h"
#include "Sphere.h"


LinePickingData SphereDistanceData =
{
    "sphere",
    "sphere, with radius parameters[0]",
    1,
    {1},
};

/**
 * Implements the PDF of the distance between two random points on the 
 * surface of a sphere.
 * 
 * From Solomon, H. Geometric Probability. Philadelphia, PA: SIAM, 1978.
 * @param $s The distance to calculate the density for.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The density at $s.
 * @see http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistancePDF(double s, double* parameters)
{
    double R = parameters[0];
    
    return s / (2. * R * R);    
}


/**
 * Implements the CDF of the distance between two random points on the 
 * surface of a sphere.
 *
 * From Solomon, H. Geometric Probability. Philadelphia, PA: SIAM, 1978.
 * @param $s The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The  cumulative density at $s.
 * @see http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistanceCDF(double s, double* parameters)
{
    double R = parameters[0];

    return (s * s) / (4. * R * R);
}


/**
* Calculates the mean of the distance between two random points on the surface 
* of a sphere.
*
* From Solomon, H. Geometric Probability. Philadelphia, PA: SIAM, 1978.
* @param $parameters $parameters[0] is the radius of the sphere. 
* @return The mean of the distance between two random points on the surface 
* of a sphere
* @see http://mathworld.wolfram.com/SphereLinePicking.html
*/
double SphereDistanceMean(double* parameters)
{
    double R = parameters[0];
    
    return (4. * R) / 3.;
}


/**
 * Calculates the variance of the distances between two random points 
 * on the surface of a sphere.
 *
 * From Solomon, H. Geometric Probability. Philadelphia, PA: SIAM, 1978.
 * @param $parameters $parameters[0] is the radius of the sphere. 
 * @return The variance of the distances between two random points on 
 * the surface  of a sphere
 * @see http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistanceVar(double* parameters)
{
    double R = parameters[0];
    
    return (2. *  R * R) / 9.;
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on the surface of a sphere.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on the surface 
 * of a sphere.
 * @param $parameters $parameters[0] is the radius of the sphere.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void SphereDistanceSupport(double *t, double *parameters)
{

    double R = parameters[0];
    
    t[0] = 0;
    
    /* the longest line is the diameter of the sphere */
    t[1] = 2 * R;
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
void SphereDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{   
    /* nothing further to check */
    *result=0;
}
