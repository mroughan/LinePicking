/* Cylinder.c	
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
#include "EllipticK.h"
#include "EllipticF.h"
#include "EllipticE1.h"
#include "EllipticE2.h"

#include "LinePickingData.h"
#include "metrics.h"
#include "Rand.h"
#include "Cylinder.h"
#include "HyperGeometric.h"

LinePickingData CylinderDistanceData =
{
    "cylinder",
    "cylinder, length parameters[0], radius parameters[1]",
    2,
    {2,0.5}
};




/**
 * Implements the PDF of the distance between two random points in a
 * cylinder.
 *
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius. 
 * @return The density at $t.
 */
double CylinderDistancePDF(double t, double* parameters)
{
    double L = parameters[0];
    double D = parameters[1] * 2.;
    double L2 = L * L;
    double D2 = D * D;
    double t2 = t * t;
    double result;
    
    
    /* three cases */
    if (t <=  D)
    {
        
        return (4 * t * (3 * D2 * t * sqrt(D2 - t2) + 
                         6 * t * t2 * sqrt(D2 - t2) + 
                         12 * D2 * t * (L * M_PI - t * acos(t / D)) - 
                         3 * D2 * D2 * asin(t / D) + 
                         16 * D * L * (-((D2 + t2) * EllipticE1(t2 / D2)) + 
                                       (D2 - t2) * EllipticK(t2 / D2)))) /
                            (3.* D2 * D2 * L2 * M_PI);
    } 
    else if (t <= L) 
    {
        return (-2 * t * (3 * D2 * M_PI * (D2 - 8 * L * t) + 
                          32 * L * t * ((D2 + t2) * EllipticE1(D2 / t2) + 
                                        (D2 - t2) * EllipticK(D2 / t2))))/
                (3. * D2 * D2 * L2 * M_PI);
    } 
    else 
    {
        result = (2 * t * (-2 * sqrt(-((L2 - t2 ) * (D2 + L2 - t2))) *
                           (3 * D2 + 2 * L2 + 6 * t2) - 
                           6 * D2 * (D2 - 4 * (L2 + t2)) * 
                           acos(sqrt(t2 - L2) / D) + 
                           32 * L * t * 
                           (-((D2 + t2) * EllipticE1(D2 / t2)) + 
                            (D2 + t2) *
                            EllipticE2(asin(sqrt(t2 - L2) / D), D2 / t2) + 
                            t*(D*EllipticF(acos(L/t), t2 / D2) - 
                               t*EllipticF(asin(sqrt(t2 - L2) / D), D2 / t2)) + 
                            (t2 - D2) * EllipticK(D2 / t2)))) /
                    (3. * D2 * D2 * L2 * M_PI);
        
        return (result < 0.0) ? 0 : result;
        
    }
    
}


/**
 * Implements the CDF of the distance between two random points in a 
 * cylinder.
 * 
 * @param $w The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.  
 * @return The cumulative density at $w.
 * @todo Implement.
 */
double CylinderDistanceCDF(double w, double* parameters)
{
    return -1;
}


/**
 * Calculates the mean distance between two random points in a 
 * cylinder.
 *
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The mean distance between two random points in a cylinder.
 * @todo Implement.
 */
double CylinderDistanceMean(double* parameters)
{
    return -1;
}


/**
 * Calculates the variance of distances between two random points in a 
 * cylinder.
 *
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The variance of distances between two random points in a 
 * cylinder.
 * @todo Implement.
 */
double CylinderDistanceVar(double* parameters)
{
    return -1;
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points in a cylinder.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points in a cylinder. 
 * 
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void CylinderDistanceSupport(double *t, double *parameters)
{
    /* cylindrical surface, side lengths parameters[0], parameters[1] */
    t[0] = 0;
    t[1] = sqrt(parameters[0]*parameters[0] + 4 * parameters[1]*parameters[1]);
}


/**
* Intended to determine if the parameters supplied are valid input 
* to the other functions implemented in this file. However as 
* the calling function checks that the supplied parameters are positive 
* this is merely a place holder to allow for a complete implementation 
* in geometries that have more complex relationships between parameters.
*
* @param $parameters $parameters[0] is the length of the cylinder
* and $parameters[1] is the radius.
* @param $result Pointer to storage for an integer indicating any errors  
* in the supplied parameters.
* @param $error_str Pointer to storage for a message explaining any errors
* in the supplied parameters. 
* @return Any error conditions are indicated by placing a value other than 0 
* in the location pointed to by $result and a message explaining the error 
* is copied in to the location pointed to $error_str 
*/
void CylinderDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    *result=0;
    if (2 * parameters[1] <= parameters[0]) return;
    
    *result=4;
    sprintf(error_str,
            "\nLinePickingCheckParameters: For the cylinder "
            "we must have (2 * parameter[1]  <= parameter[0]).\n"
            "i.e., The length of the cylinder must be >= "
            " the diameter of the cylinder\n"); 
}


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The number of coordinates used given input problem and parameters.
 */
void CylinderDistanceNcoords(int *Ncoords, char **CoordSystem, 
                              double* parameters) 
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
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The set of points.
 */
void CylinderDistanceSimPoints(double **points, int *Npoints, 
                                         int *Ncoords, double* parameters)
{
    int i, j;
    
    double normals[2];
    double u, sum;
    
    
    for (i=0; i<*Npoints; i++)
    {
        
        /* generate n normal random variables */
        rand_normal(2, normals);
        
        /* normalize them so that they lie on the (n-1)-sphere */
        sum = 0;
        for (j=0; j<2; j++) sum += normals[j]*normals[j];
        for (j=0; j<2; j++) points[i][j] = normals[j]/sqrt(sum);
        
        /* now distribute them through the disk */
        u = pow(drand48(), 1.0 / 2);
        for (j=0; j<2; j++)
        {
            points[i][j] = parameters[1] * u * points[i][j];
        }
        points[i][2] = drand48() * parameters[0];
    }
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[0] is the length of the cylinder
 * and $parameters[1] is the radius.
 * @return The distance between the two points.
 */
double CylinderDistanceMetric(int Ncoords, double *point1, 
                                        double* point2, double* parameters)
{
    return DistanceEuclidean(Ncoords, point1, point2);
}
