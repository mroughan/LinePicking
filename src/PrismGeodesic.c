/* PrismGeodesic.c	
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
#include "PrismGeodesic.h"

LinePickingData PrismGeodesicDistanceData =
{
    "prism geodesic",
    "prism geodesic, with length parameters[0], and perimeter parameters[1]."
    "Perimeter is used as the prism can have any cross section.",
    2,
    {1,1}
};    


/**
 * Implements the PDF of the distance between two random points on the
 * surface of an upright prism (excluding the ends). The distance is  
 * measured around the the surface of the prism (i.e., a geodesic). 
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @todo Write up the derivation.
 * @param $w The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of the prism and  
 * $parameters[1] is the perimeter of the prism. 
 * @return The density at $w.
 */
double PrismGeodesicDistancePDF(double w, double* parameters)
{
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    /* double P2 = P * P; */
    /* double M = sqrt(L2 + (P2 / 4.)); */
    double w2 = w * w; 
        
    /* three cases */
    if (w <= P / 2)
    {
        return (2 * (L * M_PI - 2 * w)* w) / (L2 * P);
    } 
    else if (w <= L) 
    {
        return  (-2 * w) / L2 + (4 * w * asin(P / (2 * w))) / (L * P);        
    }
    else 
    {
        double r = (((-2 * w)  + ( 4 * w * sqrt(w2 - L2)) / P ) / L - 
                 (w * (4 * acos(L / w) - 4 * asin(P / (2 * w))))/ P) / L;
        return r < 0.0 ? 0.0 : r; 
    }
}


/**
 * Implements the CDF of the distance between two random points on the
 * surface of an upright prism (excluding the ends). The distance is  
 * measured around the the surface of the prism (i.e., a geodesic). 
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @todo Write up the derivation.
 * @param $w The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the length of the prism and  
 * $parameters[1] is the perimeter of the prism. 
 * @return The cumulative density at $w.
 */
double PrismGeodesicDistanceCDF(double w, double* parameters)
{
    
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    double P2 = P * P;
    /* double M = sqrt(L2 + (P2 / 4.)); */
    double w2 = w * w;
    
    
    /* three cases */
    if (w <= P / 2)
    {
        return (-4 * w * w2 + 3 * L * M_PI * w * sqrt(w2)) / (3. * L2 * P);
    } 
    else if (w <= L) 
    {
        return  (P2 - 12 * w2) / (12. * L2) + 
                sqrt(4 * w2 - P2) / (2. * L) + 
                (2 * w2 * asin(P / (2 * w))) / (L * P);        
    }
    else 
    {
        return  (P2 - 12 * w2) / (12. * L2) + 
                (2 * sqrt(w2 -L2)) / (3. * P) + 
                (4 * w2 * sqrt(w2 - L2)) / (3. * L2 * P) + 
                sqrt(4 * w2 - P2) / (2. * L) + 
                (
                    2 * L * (acos((2 * L) / sqrt(4 * L2 + P2)) 
                    - asin(P / sqrt(4 * L2 + P2)))
                ) / P +
                (
                    P2 * acos((2 * L) / sqrt(4 * L2 + P2)) - 
                    4 * w2 * acos(L/w) + 
                    4 * w2 * asin(P / (2 * w)) - 
                    P2 * asin(P / sqrt(4 * L2 + P2))
                    ) / (2. * L * P);
    }
}




/**
 * Calculates the mean distance between two random points on the
 * surface of an upright prism (excluding the ends).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @param $parameters $parameters[0] is the length of the prism and  
 * $parameters[1] is the perimeter of the prism. 
 * @return The mean distance between two random points on the
 * surface of an upright prism (excluding the ends).
 * @todo re-derive the mean without using the three part PDF as a basis 
 * I am sure a simpler result can be found using a similar methods to 
 * that used on the rectangle
 */
double PrismGeodesicDistanceMean(double* parameters)
{
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    double L3 = L2 * L;
    double L4 = L3 * L;
    double L5 = L4 * L;
    
    double P2 = P * P;
    double P3 = P2 * P;
    double P4 = P3 * P;
    double P5 = P4 * P;

    /* it isnt simple because the PDF is in three parts */
    return  (24 * L4 * P + 2 * L2 * P3 - P5 + 
             P4 * sqrt(4 * L2 + P2) - 64 * L5 * M_PI - 
             32 * (L2  *  L) * P2 * M_PI - 4 * L * P4 * M_PI + 
             8 * L * pow(4 * L2 + P2, 2) * 
             asin((2 * L) / sqrt(4 * L2 + P2)) + 
             8 * L * pow(4 * L2 + P2, 2) * 
             asin(P / sqrt(4 * L2 + P2)) - 
             L4 * sqrt(4 * L2 + P2) * log(256) - 
             8 * L4 * sqrt(4 * L2 + P2) * log(L) - 
             4 * L * P3 * sqrt(4 * L2 + P2) * log(P) + 
             4 * L * P3 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             8 * L4 * sqrt(4 * L2 + P2) * 
             log(P + sqrt(4 * L2 + P2))) / 
            (48. * L2 * P * sqrt(4 * L2 + P2));
}

/**
 * Calculates the variance of distances between two random points on the
 * surface of an upright prism (excluding the ends).
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @param $parameters $parameters[0] is the length of the prism and  
 * $parameters[1] is the perimeter of the prism. 
 * @return The variance of distances between two random points on the
 * surface of an upright prism (excluding the ends).
 * @todo re-derive the variance without using the three part PDF as a basis 
 * I am sure a simpler result can be found using a similar methods to 
 * that used on the rectangle
 */
double PrismGeodesicDistanceVar(double* parameters)
{
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    double L3 = L2 * L;
    double L4 = L3 * L;
    
    double P2 = P * P;
    double P3 = P2 * P;
    double P4 = P3 * P;

    
    return (8 * L * P * (2 * L2 + P2) - 3 * pow(4 * L2 + P2,2) * M_PI + 
            6 * pow(4 * L2 + P2,2) * 
            (asin((2 * L)/sqrt(4 * L2 + P2)) + 
            asin(P/sqrt(4 * L2 + P2))))/(96. * L * P) - 
            pow(P4 * sqrt(4 * L2 + P2) - 
            4 * L * pow(4 * L2 + P2,2) * M_PI + 
            (4 * L2 + P2) * 
            (6 * L2 * P - P3 + 8 * L * (4 * L2 + P2) * 
             (asin((2 * L)/sqrt(4 * L2 + P2)) + asin(P/sqrt(4 * L2 + P2)))
            ) + 4 * L * P3 * sqrt(4 * L2 + P2) * 
            log((2 * L + sqrt(4 * L2 + P2))/P) - 
            L4 * sqrt(4 * L2 + P2) * 
            log((256 * pow(L,8))/pow(P + sqrt(4 * L2 + P2),8)),2)/
            (2304. * L4 * P2 * (4 * L2 + P2));
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on the surface of an upright prism (excluding the ends).
 *
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on the surface 
 * of an upright prism (excluding the ends).
 * @param $parameters $parameters[0] is the length of the prism and  
 * $parameters[1] is the perimeter of the prism. 
 * 
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void PrismGeodesicDistanceSupport(double *t, double *parameters)
{

    t[0] = 0;
    t[1] = sqrt(pow(parameters[0], 2) + pow(parameters[1]/2, 2));
}


/**
 * Determines if the parameters supplied are valid input 
 * to the other functions implemented in this file.
 * @param $parameters parameters[0] is the length of the prism under 
 * consideration and parameters[1] is the perimeter of the prism under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 * The only condition this function needs to check is that the length of the  
 * prism is at least as long as half the perimeter
 */
void PrismGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    *result=0;
    if (parameters[1] / 2. <= parameters[0]) return;
    
    *result=4;
    sprintf(error_str,
            "\nLinePickingCheckParameters: For the PrismGeodetic region "
            "we must have (parameter[1] / 2 <= parameter[0]).\n"
            "i.e., The Length of the prism must be >= "
            " to half the Perimeter of the prism\n"); 
}


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters parameters[0] is the length of the prism under 
 * consideration and parameters[1] is the perimeter of the prism under
 * consideration.
 * @return The number of coordinates used given input problem and parameters.
 */
void PrismGeodesicDistanceNcoords(int *Ncoords, char **CoordSystem, 
                                  double* parameters) 
{
    *Ncoords = 3; 
    *CoordSystem="Euclidean"; 
}




/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, 
 * in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameters[0] is the length of the prism under 
 * and $parameters[1] is the length of the perimeter of the prism 
 * under consideration.
 * @return The set of points.
 */
void PrismGeodesicDistanceSimPoints(double **points, int *Npoints, 
                                    int *Ncoords, double* parameters)
{
    
    int i;
    double normals[2];
    double length;
    

    for (i=0; i<*Npoints; i++)
    {
        /* generate 2 normal random variables */
        rand_normal(2, normals);
        
        /* normalize them so that they lie on the circle */
        length = sqrt(pow(normals[0], 2) + pow(normals[1], 2));
        points[i][0] = ((parameters[1]/ (2 *M_PI)) * normals[0]) / length;
        points[i][1] = ((parameters[1]/ (2 *M_PI)) * normals[1]) / length;
        points[i][2] = drand48() * parameters[0];
    }    
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[0] is the length of the prism under 
 * and $parameters[1] is the length of the perimeter of the prism 
 * under consideration.
 * @return The distance between the two points.
 * @todo Implement this.
 */
double PrismGeodesicDistanceMetric(int Ncoords, double *point1, 
                                   double* point2, double* parameters)
{
    double d= sqrt(pow(point1[0]-point2[0], 2.0) + 
                   pow(point1[1]-point2[1], 2.0));
    double g = (parameters[1] / (2*M_PI)) * 2 * 
                    asin(d/ (2 * (parameters[1] / (2*M_PI))));
    return  sqrt(pow(point1[2]-point2[2], 2) + pow(g, 2));
    
}


