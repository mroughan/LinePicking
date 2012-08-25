/* PrismGeodesic.c	
 *
 *     Copyright 2012 Eric Parsonage <eric.parsonagen@adelaide.edu.au>
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *   
 *     This program is distributed in the hope that it will be useful,
 *     but wITHOUT ANY wARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>
#include <stdio.h>
#include "PrismGeodesic.h"

char *PrismGeodesicDistanceName = "PrismGeodesic";
char *PrismGeodesicDistanceDescription = "PrismGeodesic description";
int PrismGeodesicDistanceNpar = 1;


/* distance density (at w) between two points on the surface of an
 * upright prism of length and perimeter given in parameters[0] and 
 * parameters[1] respectively. The distance is measured around the   
 * the surface of the prism (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double PrismGeodesicDistancePDF(double w, double* parameters)
{
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    double P2 = P * P;
    double M = sqrt(L2 + (P2 / 4.));
    double w2 = w * w;
    
    if (w <= 0) 
        return 0;
    else if (w >= M) 
        return 0;
    
    /* three cases */
    if (w <= P / 2)
    {
        return (2 * (L * M_PI - 2 * w)* w) / (L2 * P);
    } 
    else if ((w > P / 2) && w <= L) 
    {
        return  (-2 * w) / L2 + (4 * w * asin(P / (2 * w))) / (L * P);        
    }
    else 
    {
        return  (-2 * w) / L2 + ( 4 * w * sqrt(w2 - L2)) / (L2 * P) - 
        (4 * (w * acos(L / w) - w * asin(P / (2 * w))))/(L * P);
        
    }
}


/* distance distribution (at w) between two points on the surface of an
 * upright prism of length and perimeter given in parameters[0] and 
 * parameters[1] respectively. The distance is measured around the   
 * the surface of the prism (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double PrismGeodesicDistanceCDF(double w, double* parameters)
{
    
    double L = parameters[0];
    double P = parameters[1];
    double L2 = L * L;
    double P2 = P * P;
    double M = sqrt(L2 + (P2 / 4.));
    double w2 = w * w;
    
    if (w <= 0) 
        return 0;
    else if (w >= M) 
        return 1;
    
    /* three cases */
    if (w <= P / 2)
    {
        return (-4 * w * w2 + 3 * L * M_PI * w * sqrt(w2)) / (3. * L2 * P);
    } 
    else if ((w > P / 2) && w <= L) 
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

/* mean distance between two points on the surface of an
 * upright prism of length and perimeter given in parameters[0] and 
 * parameters[1] respectively. The distance is measured around the   
 * the surface of the prism (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double PrismGeodesicDistanceMean(double* parameters)
{
    
    return -1;
}

/* variance of distance between two points on the surface of an
 * upright prism of length and perimeter given in parameters[0] and 
 * parameters[1] respectively. The distance is measured around the   
 * the surface of the prism (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double PrismGeodesicDistanceVar(double* parameters)
{
    
    return -1;
}

void PrismGeodesicDistanceSupport(double *t, double *parameters)
{

    t[0] = 0;
    t[1] = sqrt(pow(parameters[0] / 2, 2) + pow(parameters[1], 2));
}

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
