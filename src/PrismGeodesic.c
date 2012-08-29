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
#include <stdio.h>
#include "PrismGeodesic.h"

char *PrismGeodesicDistanceName = "prism geodesic";
char *PrismGeodesicDistanceDescription = 
            "prism geodesic, with length parameters[0], and perimeter parameters[1]."
            "Perimeter is used as the prism can have any cross section.";

int PrismGeodesicDistanceNpar = 2;


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
    double P2 = P * P;
    double M = sqrt(L2 + (P2 / 4.));
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
        return  (-2 * w) / L2 + ( 4 * w * sqrt(w2 - L2)) / (L2 * P) - 
        (4 * (w * acos(L / w) - w * asin(P / (2 * w))))/(L * P);
        
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
    double M = sqrt(L2 + (P2 / 4.));
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
    double L5 = L4 * L;
    double L6 = L5 * L;
    double L7 = L6 * L;
    double L8 = L7 * L;
    double L9 = L8 * L;
    double L10 = L9 * L;
    double L11 = L10 * L; 
    double P2 = P * P;
    double P3 = P2 * P;
    double P4 = P3 * P;
    double P5 = P4 * P;
    double P6 = P5 * P;
    double P7 = P6 * P;
    double P8 = P7 * P;
    double P9 = P8 * P;
    double P10 = P9 * P;
    double P11 = P10 * P; 
    
    /* I am not taking the piss this was the best Mathmatica could do for me */
    
    return  (-576 * L5 * P6 - 48 * L3 * P8 + 24 * L * P10 + 
             2880 * L7 * P3 * sqrt(4 * L2 + P2) + 
             2448 * L5 * P5 * sqrt(4 * L2 + P2) + 
             96 * L3 * P7 * sqrt(4 * L2 + P2) - 
             24 * L * P9 * sqrt(4 * L2 + P2) + 
             960 * L6 * P5 * M_PI + 576 * L4 * P7 * M_PI + 
             108 * L2 * P9 * M_PI + 6 * P11 * M_PI - 
             6336 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI - 
             4128 * L6 * P4 * sqrt(4 * L2 + P2) * M_PI - 
             924 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI - 
             96 * L2 * P8 * sqrt(4 * L2 + P2) * M_PI - 
             6 * P10 * sqrt(4 * L2 + P2) * M_PI + 
             1536 * L7 * P4 * pow(M_PI,2) + 
             1152 * L5 * P6 * pow(M_PI,2) + 
             288 * L3 * P8 * pow(M_PI,2) + 24 * L * P10 * pow(M_PI,2) - 
             3072 * L9 * P * sqrt(4 * L2 + P2) * pow(M_PI,2) - 
             3840 * L7 * P3 * sqrt(4 * L2 + P2) * pow(M_PI,2) - 
             1728 * L5 * P5 * sqrt(4 * L2 + P2) * pow(M_PI,2) - 
             336 * L3 * P7 * sqrt(4 * L2 + P2) * pow(M_PI,2) - 
             24 * L * P9 * sqrt(4 * L2 + P2) * pow(M_PI,2) - 
             12288 * L10 * sqrt(4 * L2 + P2) * pow(M_PI,3) - 
             12288 * L8 * P2 * sqrt(4 * L2 + P2) * 
             pow(M_PI,3) - 4608 * L6 * P4 * 
             sqrt(4 * L2 + P2) * pow(M_PI,3) - 
             768 * L4 * P6 * sqrt(4 * L2 + P2) * pow(M_PI,3) - 
             48 * L2 * P8 * sqrt(4 * L2 + P2) * pow(M_PI,3) + 
             384 * L2 * pow(4 * L2 + P2,4.5) * 
             pow(asin((2 * L) / sqrt(4 * L2 + P2)),3) + 
             384 * L2 * pow(4 * L2 + P2,4.5) * 
             pow(asin(P / sqrt(4 * L2 + P2)),3) + 
             384 * L7 * P4 * log(2) + 32 * L5 * P6 * log(2) - 
             16 * L3 * P8 * log(2) + 
             2304 * L8 * P2 * sqrt(4 * L2 - P2) * log(2) + 
             192 * L6 * P4 * sqrt(4 * L2 - P2) * log(2) - 
             96 * L4 * P6 * sqrt(4 * L2 - P2) * log(2) + 
             6144 * L8 * P2 * sqrt(4 * L2 + P2) * log(2) - 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * log(2) + 
             16 * L3 * P7 * sqrt(4 * L2 + P2) * log(2) - 
             1536 * L7 * P2 * sqrt(16 * L4 - P4) * log(2) + 
             96 * L4 * P5 * sqrt(16 * L4 - P4) * log(2) + 
             4608 * L10 * P * M_PI * log(2) + 512 * L8 * P3 * M_PI * log(2) - 
             608 * L6 * P5 * M_PI * log(2) - 
             112 * L4 * P7 * M_PI * log(2) - 
             6144 * L9 * P * sqrt(4 * L2 - P2) * M_PI * log(2) - 
             3072 * L7 * P3 * sqrt(4 * L2 - P2) * M_PI * log(2) - 
             384 * L5 * P5 * sqrt(4 * L2 - P2) * M_PI * log(2) + 
             192 * L6 * P4 * sqrt(4 * L2 + P2) * M_PI * log(2) + 
             48 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI * log(2) - 
             12288 * L11 * pow(M_PI,2) * log(2) - 
             9216 * L9 * P2 * pow(M_PI,2) * log(2) - 
             2304 * L7 * P4 * pow(M_PI,2) * log(2) - 
             192 * L5 * P6 * pow(M_PI,2) * log(2) + 
             9216 * L10 * P * asin(P / (2 * L)) * log(2) + 
             768 * L8 * P3 * asin(P / (2 * L)) * log(2) - 
             384 * L6 * P5 * asin(P / (2 * L)) * log(2) - 
             12288 * L9 * P * sqrt(4 * L2 + P2) * asin(P / (2 * L)) * 
             log(2) + 384 * L6 * P4 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(2) - 24576 * L11 * M_PI * asin(P / (2 * L)) * log(2) - 
             12288 * L9 * P2 * M_PI * asin(P / (2 * L)) * log(2) - 
             1536 * L7 * P4 * M_PI * asin(P / (2 * L)) * log(2) - 
             64 * L7 * P3 * sqrt(4 * L2 + P2) * 
             pow(log(2),2) - 384 * L8 * P * sqrt(16 * L4 - P4) * 
             pow(log(2),2) - 768 * L10 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(2),2) - 192 * L8 * P2 * 
             sqrt(4 * L2 + P2) * M_PI * pow(log(2),2) - 
             1536 * L10 * sqrt(4 * L2 + P2) * asin(P / (2 * L)) * 
             pow(log(2),2) + 576 * L9 * P2 * log(256) - 
             28 * L5 * P6 * log(256) + 2 * L3 * P8 * log(256) - 
             288 * L8 * P2 * sqrt(4 * L2 - P2) * log(256) - 
             24 * L6 * P4 * sqrt(4 * L2 - P2) * log(256) + 
             12 * L4 * P6 * sqrt(4 * L2 - P2) * log(256) - 
             768 * L8 * P2 * sqrt(4 * L2 + P2) * log(256) + 
             48 * L5 * P5 * sqrt(4 * L2 + P2) * log(256) - 
             2 * L3 * P7 * sqrt(4 * L2 + P2) * log(256) + 
             192 * L7 * P2 * sqrt(16 * L4 - P4) * log(256) - 
             12 * L4 * P5 * sqrt(16 * L4 - P4) * log(256) - 
             1536 * L10 * P * M_PI * log(256) - 640 * L8 * P3 * M_PI * log(256)- 
             32 * L6 * P5 * M_PI * log(256) + 
             8 * L4 * P7 * M_PI * log(256) + 
             768 * L9 * P * sqrt(4 * L2 - P2) * M_PI * log(256) + 
             384 * L7 * P3 * sqrt(4 * L2 - P2) * M_PI * log(256) + 
             48 * L5 * P5 * sqrt(4 * L2 - P2) * M_PI * log(256) - 
             1152 * L10 * P * asin(P / (2 * L)) * log(256) - 
             96 * L8 * P3 * asin(P / (2 * L)) * log(256) + 
             48 * L6 * P5 * asin(P / (2 * L)) * log(256) + 
             1536 * L9 * P * sqrt(4 * L2 + P2) * asin(P / (2 * L)) * 
             log(256) - 48 * L6 * P4 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(256) + 
             3072 * L11 * M_PI * asin(P / (2 * L)) * log(256) + 
             1536 * L9 * P2 * M_PI * asin(P / (2 * L)) * log(256) + 
             192 * L7 * P4 * M_PI * asin(P / (2 * L)) * log(256) - 
             12 * L9 * P * sqrt(4 * L2 + P2) * pow(log(256),2) + 
             L7 * P3 * sqrt(4 * L2 + P2) * 
             pow(log(256),2) + 6 * L8 * P * sqrt(16 * L4 - P4) * 
             pow(log(256),2) + 24 * L10 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * pow(log(256),2) - 
             13824 * L9 * P2 * log(L) - 1152 * L7 * P4 * log(L) + 
             576 * L5 * P6 * log(L) - 
             576 * L5 * P5 * sqrt(4 * L2 + P2) * log(L) + 
             41472 * L10 * P * M_PI * log(L) + 
             19968 * L8 * P3 * M_PI * log(L) + 
             2208 * L6 * P5 * M_PI * log(L) - 
             48 * L4 * P7 * M_PI * log(L) + 
             192 * L6 * P4 * sqrt(4 * L2 + P2) * M_PI * log(L) + 
             48 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI * log(L) - 
             12288 * L11 * pow(M_PI,2) * log(L) - 
             9216 * L9 * P2 * pow(M_PI,2) * log(L) - 
             2304 * L7 * P4 * pow(M_PI,2) * log(L) - 
             192 * L5 * P6 * pow(M_PI,2) * log(L) + 
             6144 * L9 * P * sqrt(4 * L2 + P2) * log(2) * log(L) - 
             128 * L7 * P3 * sqrt(4 * L2 + P2) * log(2) * 
             log(L) - 768 * L8 * P * sqrt(16 * L4 - P4) * log(2) * 
             log(L) - 1536 * L10 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(L) - 384 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI * 
             log(2) * log(L) - 3072 * L10 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(2) * log(L) - 
             192 * L9 * P * sqrt(4 * L2 + P2) * log(256) * log(L) + 
             16 * L7 * P3 * sqrt(4 * L2 + P2) * log(256) * 
             log(L) + 96 * L8 * P * sqrt(16 * L4 - P4) * log(256) * 
             log(L) + 384 * L10 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(256) * log(L) + 
             5376 * L9 * P * sqrt(4 * L2 + P2) * pow(log(L),2) - 
             768 * L10 * sqrt(4 * L2 + P2) * M_PI * pow(log(L),2) - 
             192 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(L),2) + 2304 * L7 * P4 * M_PI * log(P) + 
             768 * L5 * P6 * M_PI * log(P) - 
             48 * L3 * P8 * M_PI * log(P) - 24 * L * P10 * M_PI * log(P) + 
             96 * L3 * P7 * sqrt(4 * L2 + P2) * M_PI * log(P) + 
             24 * L * P9 * sqrt(4 * L2 + P2) * M_PI * log(P) - 
             6144 * L8 * P3 * pow(M_PI,2) * log(P) - 
             4608 * L6 * P5 * pow(M_PI,2) * log(P) - 
             1152 * L4 * P7 * pow(M_PI,2) * log(P) - 
             96 * L2 * P9 * pow(M_PI,2) * log(P) + 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(2) * 
             log(P) - 64 * L4 * P6 * sqrt(4 * L2 + P2) * 
             log(2) * log(P) - 384 * L5 * P4 * 
             sqrt(16 * L4 - P4) * log(2) * log(P) - 
             768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(P) - 192 * L5 * P5 * sqrt(4 * L2 + P2) * M_PI * 
             log(2) * log(P) - 1536 * L7 * P3 * 
             sqrt(4 * L2 + P2) * asin(P / (2 * L)) * log(2) * log(P) - 
             96 * L6 * P4 * sqrt(4 * L2 + P2) * log(256) * log(P) + 
             8 * L4 * P6 * sqrt(4 * L2 + P2) * log(256) * log(P) + 
             48 * L5 * P4 * sqrt(16 * L4 - P4) * log(256) * log(P) + 
             192 * L7 * P3 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(256) * log(P) + 
             3072 * L6 * P4 * sqrt(4 * L2 + P2) * log(L) * 
             log(P) - 768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * 
             log(L) * log(P) - 192 * L5 * P5 * 
             sqrt(4 * L2 + P2) * M_PI * log(L) * log(P) + 
             192 * L3 * P7 * sqrt(4 * L2 + P2) * 
             pow(log(P),2) - 192 * L4 * P6 * 
             sqrt(4 * L2 + P2) * M_PI * pow(log(P),2) - 
             48 * L2 * P8 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(P),2) + 6912 * L9 * P2 * 
             log(4 * L2 + P2) + 
             576 * L7 * P4 * log(4 * L2 + P2) - 
             288 * L5 * P6 * log(4 * L2 + P2) + 
             288 * L5 * P5 * sqrt(4 * L2 + P2) * 
             log(4 * L2 + P2) - 
             18432 * L10 * P * M_PI * log(4 * L2 + P2) - 
             9216 * L8 * P3 * M_PI * log(4 * L2 + P2) - 
             1152 * L6 * P5 * M_PI * log(4 * L2 + P2) - 
             2304 * L9 * P * sqrt(4 * L2 + P2) * log(2) * 
             log(4 * L2 + P2) - 
             2304 * L9 * P * sqrt(4 * L2 + P2) * log(L) * 
             log(4 * L2 + P2) - 
             1152 * L6 * P4 * sqrt(4 * L2 + P2) * log(P) * 
             log(4 * L2 + P2) - 
             9216 * L9 * P2 * log(4 + P2 / L2) - 
             768 * L7 * P4 * log(4 + P2 / L2) + 
             384 * L5 * P6 * log(4 + P2 / L2) - 
             384 * L5 * P5 * sqrt(4 * L2 + P2) * 
             log(4 + P2 / L2) + 
             24576 * L10 * P * M_PI * log(4 + P2 / L2) + 
             12288 * L8 * P3 * M_PI * log(4 + P2 / L2) + 
             1536 * L6 * P5 * M_PI * log(4 + P2 / L2) + 
             3072 * L9 * P * sqrt(4 * L2 + P2) * log(2) * 
             log(4 + P2 / L2) + 
             3072 * L9 * P * sqrt(4 * L2 + P2) * log(L) * 
             log(4 + P2 / L2) + 
             1536 * L6 * P4 * sqrt(4 * L2 + P2) * log(P) * 
             log(4 + P2 / L2) + 
             2304 * L6 * P5 * log(2 * L + sqrt(4 * L2 - P2)) + 
             192 * L4 * P7 * log(2 * L + sqrt(4 * L2 - P2)) - 
             96 * L2 * P9 * log(2 * L + sqrt(4 * L2 - P2)) + 
             96 * L2 * P8 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             6144 * L7 * P4 * M_PI * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             3072 * L5 * P6 * M_PI * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             384 * L3 * P8 * M_PI * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(2) * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(L) * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             384 * L3 * P7 * sqrt(4 * L2 + P2) * log(P) * 
             log(2 * L + sqrt(4 * L2 - P2)) - 
             4608 * L9 * P2 * log(1 + P / sqrt(4 * L2 + P2)) - 
             384 * L7 * P4 * log(1 + P / sqrt(4 * L2 + P2)) + 
             192 * L5 * P6 * log(1 + P / sqrt(4 * L2 + P2)) - 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * 
             log(1 + P / sqrt(4 * L2 + P2)) + 
             12288 * L10 * P * M_PI * log(1 + P / sqrt(4 * L2 + P2)) + 
             6144 * L8 * P3 * M_PI * 
             log(1 + P / sqrt(4 * L2 + P2)) + 
             768 * L6 * P5 * M_PI * 
             log(1 + P / sqrt(4 * L2 + P2)) + 
             1536 * L9 * P * sqrt(4 * L2 + P2) * log(2) * 
             log(1 + P / sqrt(4 * L2 + P2)) + 
             1536 * L9 * P * sqrt(4 * L2 + P2) * log(L) * 
             log(1 + P / sqrt(4 * L2 + P2)) + 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(P) * 
             log(1 + P / sqrt(4 * L2 + P2)) - 
             2304 * L6 * P5 * log(2 * L + sqrt(4 * L2 + P2)) - 
             192 * L4 * P7 * log(2 * L + sqrt(4 * L2 + P2)) + 
             96 * L2 * P9 * log(2 * L + sqrt(4 * L2 + P2)) - 
             96 * L2 * P8 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             3840 * L7 * P4 * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             2304 * L5 * P6 * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             432 * L3 * P8 * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             24 * L * P10 * M_PI * log(2 * L + sqrt(4 * L2 + P2)) - 
             96 * L3 * P7 * sqrt(4 * L2 + P2) * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             24 * L * P9 * sqrt(4 * L2 + P2) * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             6144 * L8 * P3 * pow(M_PI,2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             4608 * L6 * P5 * pow(M_PI,2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             1152 * L4 * P7 * pow(M_PI,2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             96 * L2 * P9 * pow(M_PI,2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             64 * L4 * P6 * sqrt(4 * L2 + P2) * log(2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             384 * L5 * P4 * sqrt(16 * L4 - P4) * log(2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             1536 * L7 * P3 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(2) * log(2 * L + sqrt(4 * L2 + P2)) + 
             96 * L6 * P4 * sqrt(4 * L2 + P2) * log(256) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             8 * L4 * P6 * sqrt(4 * L2 + P2) * log(256) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             48 * L5 * P4 * sqrt(16 * L4 - P4) * log(256) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             192 * L7 * P3 * sqrt(4 * L2 + P2) * 
             asin(P / (2 * L)) * log(256) * log(2 * L + sqrt(4 * L2 + P2)) - 
             2304 * L6 * P4 * sqrt(4 * L2 + P2) * log(L) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * log(L) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * M_PI * log(L) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             384 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI * log(P) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             96 * L2 * P8 * sqrt(4 * L2 + P2) * M_PI * log(P) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             1152 * L6 * P4 * sqrt(4 * L2 + P2) * 
             log(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             1536 * L6 * P4 * sqrt(4 * L2 + P2) * 
             log(4 + P2 / L2) * 
             log(2 * L + sqrt(4 * L2 + P2)) + 
             384 * L3 * P7 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 - P2)) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * 
             log(1 + P / sqrt(4 * L2 + P2)) * 
             log(2 * L + sqrt(4 * L2 + P2)) - 
             192 * L3 * P7 * sqrt(4 * L2 + P2) * 
             pow(log(2 * L + sqrt(4 * L2 + P2)),2) - 
             192 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(2 * L + sqrt(4 * L2 + P2)),2) - 
             48 * L2 * P8 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(2 * L + sqrt(4 * L2 + P2)),2) - 
             4608 * L10 * P * M_PI * log(P + sqrt(4 * L2 + P2)) - 
             1536 * L8 * P3 * M_PI * log(P + sqrt(4 * L2 + P2)) + 
             96 * L6 * P5 * M_PI * log(P + sqrt(4 * L2 + P2)) + 
             48 * L4 * P7 * M_PI * log(P + sqrt(4 * L2 + P2)) - 
             192 * L6 * P4 * sqrt(4 * L2 + P2) * M_PI * 
             log(P + sqrt(4 * L2 + P2)) - 
             48 * L4 * P6 * sqrt(4 * L2 + P2) * M_PI * 
             log(P + sqrt(4 * L2 + P2)) + 
             12288 * L11 * pow(M_PI,2) * log(P + sqrt(4 * L2 + P2)) + 
             9216 * L9 * P2 * pow(M_PI,2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             2304 * L7 * P4 * pow(M_PI,2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             192 * L5 * P6 * pow(M_PI,2) * 
             log(P + sqrt(4 * L2 + P2)) - 
             1536 * L9 * P * sqrt(4 * L2 + P2) * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             128 * L7 * P3 * sqrt(4 * L2 + P2) * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             768 * L8 * P * sqrt(16 * L4 - P4) * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             1536 * L10 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             384 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             3072 * L10 * sqrt(4 * L2 + P2) * asin(P / (2 * L)) * log(2) * 
             log(P + sqrt(4 * L2 + P2)) + 
             192 * L9 * P * sqrt(4 * L2 + P2) * log(256) * 
             log(P + sqrt(4 * L2 + P2)) - 
             16 * L7 * P3 * sqrt(4 * L2 + P2) * log(256) * 
             log(P + sqrt(4 * L2 + P2)) - 
             96 * L8 * P * sqrt(16 * L4 - P4) * log(256) * 
             log(P + sqrt(4 * L2 + P2)) - 
             384 * L10 * sqrt(4 * L2 + P2) * asin(P / (2 * L)) * log(256) * 
             log(P + sqrt(4 * L2 + P2)) - 
             6144 * L9 * P * sqrt(4 * L2 + P2) * log(L) * 
             log(P + sqrt(4 * L2 + P2)) + 
             1536 * L10 * sqrt(4 * L2 + P2) * M_PI * log(L) * 
             log(P + sqrt(4 * L2 + P2)) + 
             384 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI * log(L) * 
             log(P + sqrt(4 * L2 + P2)) - 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(P) * 
             log(P + sqrt(4 * L2 + P2)) + 
             768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * log(P) * 
             log(P + sqrt(4 * L2 + P2)) + 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * M_PI * log(P) * 
             log(P + sqrt(4 * L2 + P2)) + 
             2304 * L9 * P * sqrt(4 * L2 + P2) * 
             log(4 * L2 + P2) * log(P + sqrt(4 * L2 + P2))\
             - 3072 * L9 * P * sqrt(4 * L2 + P2) * 
             log(4 + P2 / L2) * log(P + sqrt(4 * L2 + P2))\
             + 768 * L6 * P4 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 - P2)) * 
             log(P + sqrt(4 * L2 + P2)) - 
             1536 * L9 * P * sqrt(4 * L2 + P2) * 
             log(1 + P / sqrt(4 * L2 + P2)) * 
             log(P + sqrt(4 * L2 + P2)) - 
             768 * L7 * P3 * sqrt(4 * L2 + P2) * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) * 
             log(P + sqrt(4 * L2 + P2)) - 
             192 * L5 * P5 * sqrt(4 * L2 + P2) * M_PI * 
             log(2 * L + sqrt(4 * L2 + P2)) * 
             log(P + sqrt(4 * L2 + P2)) + 
             768 * L9 * P * sqrt(4 * L2 + P2) * 
             pow(log(P + sqrt(4 * L2 + P2)),2) - 
             768 * L10 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(P + sqrt(4 * L2 + P2)),2) - 
             192 * L8 * P2 * sqrt(4 * L2 + P2) * M_PI * 
             pow(log(P + sqrt(4 * L2 + P2)),2) - 
             96 * L * pow(4 * L2 + P2,3) * 
             pow(asin(P / sqrt(4 * L2 + P2)),2) * 
             (-P4 + 2 * L2 * P * sqrt(4 * L2 + P2) + 
              P3 * sqrt(4 * L2 + P2) + 
              24 * L3 * sqrt(4 * L2 + P2) * M_PI + 
              6 * L * P2 * sqrt(4 * L2 + P2) * M_PI + 
              8 * L4 * log(2) + 8 * L4 * log(L) + 4 * L * P3 * log(P) - 
              4 * L * P3 * log(2 * L + sqrt(4 * L2 + P2)) - 
              8 * L4 * log(P + sqrt(4 * L2 + P2))) - 
             96 * L * pow(4 * L2 + P2,3) * 
             pow(asin((2 * L) / sqrt(4 * L2 + P2)),2) * 
             (-P4 + 2 * L2 * P * sqrt(4 * L2 + P2) + 
              P3 * sqrt(4 * L2 + P2) + 
              24 * L3 * sqrt(4 * L2 + P2) * M_PI + 
              6 * L * P2 * sqrt(4 * L2 + P2) * M_PI - 
              12 * L * pow(4 * L2 + P2,1.5) * 
              asin(P / sqrt(4 * L2 + P2)) + 8 * L4 * log(2) + 
              8 * L4 * log(L) + 4 * L * P3 * log(P) - 
              4 * L * P3 * log(2 * L + sqrt(4 * L2 + P2)) - 
              8 * L4 * log(P + sqrt(4 * L2 + P2))) - 
             2304 * L6 * P5 * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
             192 * L4 * P7 * log((L * (2 + sqrt(4 - P2 / L2))) / 
                                 P) + 96 * L2 * P9 * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
             96 * L2 * P8 * sqrt(4 * L2 + P2) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             6144 * L7 * P4 * M_PI * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             3072 * L5 * P6 * M_PI * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             384 * L3 * P8 * M_PI * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             96 * L6 * P4 * sqrt(4 * L2 + P2) * log(256) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * log(L) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             384 * L3 * P7 * sqrt(4 * L2 + P2) * log(P) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
             384 * L3 * P7 * sqrt(4 * L2 + P2) * 
             log(2 * L + sqrt(4 * L2 + P2)) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
             768 * L6 * P4 * sqrt(4 * L2 + P2) * 
             log(P + sqrt(4 * L2 + P2)) * 
             log((L * (2 + sqrt(4 - P2 / L2))) / P) + 
             4 * (4 * L2 + P2) * 
             asin((2 * L) / sqrt(4 * L2 + P2)) * 
             (-120 * L4 * P5 - 42 * L2 * P7 - 3 * P9 + 
              792 * L6 * P2 * sqrt(4 * L2 + P2) + 
              318 * L4 * P4 * sqrt(4 * L2 + P2) + 
              36 * L2 * P6 * sqrt(4 * L2 + P2) + 
              3 * P8 * sqrt(4 * L2 + P2) - 
              384 * L5 * P4 * M_PI - 192 * L3 * P6 * M_PI - 
              24 * L * P8 * M_PI + 768 * L7 * P * sqrt(4 * L2 + P2) * 
              M_PI + 768 * L5 * P3 * sqrt(4 * L2 + P2) * M_PI + 
              240 * L3 * P5 * sqrt(4 * L2 + P2) * M_PI + 
              24 * L * P7 * sqrt(4 * L2 + P2) * M_PI + 
              4608 * L8 * sqrt(4 * L2 + P2) * pow(M_PI,2) + 
              3456 * L6 * P2 * sqrt(4 * L2 + P2) * 
              pow(M_PI,2) + 864 * L4 * P4 * 
              sqrt(4 * L2 + P2) * pow(M_PI,2) + 
              72 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(M_PI,2) + 288 * L2 * pow(4 * L2 + P2,3.5) * 
              pow(asin(P / sqrt(4 * L2 + P2)),2) - 
              576 * L8 * P * log(2) + 80 * L6 * P3 * log(2) + 
              56 * L4 * P5 * log(2) + 
              768 * L7 * P * sqrt(4 * L2 - P2) * log(2) + 
              192 * L5 * P3 * sqrt(4 * L2 - P2) * log(2) - 
              24 * L4 * P4 * sqrt(4 * L2 + P2) * log(2) + 
              3072 * L9 * M_PI * log(2) + 1536 * L7 * P2 * M_PI * log(2) + 
              192 * L5 * P4 * M_PI * log(2) + 
              96 * L8 * sqrt(4 * L2 + P2) * pow(log(2),2) + 
              192 * L8 * P * log(256) + 32 * L6 * P3 * log(256) - 
              4 * L4 * P5 * log(256) - 
              96 * L7 * P * sqrt(4 * L2 - P2) * log(256) - 
              24 * L5 * P3 * sqrt(4 * L2 - P2) * log(256) + 
              96 * L8 * sqrt(4 * L2 + P2) * pow(log(L),2) - 
              288 * L5 * P4 * log(P) - 24 * L3 * P6 * log(P) + 
              12 * L * P8 * log(P) - 
              12 * L * P7 * sqrt(4 * L2 + P2) * log(P) + 
              1536 * L6 * P3 * M_PI * log(P) + 
              768 * L4 * P5 * M_PI * log(P) + 
              96 * L2 * P7 * M_PI * log(P) + 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * log(2) * 
              log(P) + 24 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(log(P),2) + 2304 * L8 * P * log(4 * L2 + P2) + 
              576 * L6 * P3 * log(4 * L2 + P2) - 
              3072 * L8 * P * log(4 + P2 / L2) - 
              768 * L6 * P3 * log(4 + P2 / L2) + 
              768 * L5 * P4 * 
              log(2 * L + sqrt(4 * L2 - P2)) + 
              192 * L3 * P6 * 
              log(2 * L + sqrt(4 * L2 - P2)) - 
              1536 * L8 * P * log(1 + P / sqrt(4 * L2 + P2)) - 
              384 * L6 * P3 * 
              log(1 + P / sqrt(4 * L2 + P2)) - 
              480 * L5 * P4 * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              168 * L3 * P6 * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              12 * L * P8 * log(2 * L + sqrt(4 * L2 + P2)) + 
              12 * L * P7 * sqrt(4 * L2 + P2) * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              1536 * L6 * P3 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              768 * L4 * P5 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              96 * L2 * P7 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * log(2) * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              48 * L2 * P6 * sqrt(4 * L2 + P2) * log(P) * 
              log(2 * L + sqrt(4 * L2 + P2)) + 
              24 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(log(2 * L + sqrt(4 * L2 + P2)),2) + 
              576 * L8 * P * log(P + sqrt(4 * L2 + P2)) + 
              48 * L6 * P3 * log(P + sqrt(4 * L2 + P2)) - 
              24 * L4 * P5 * log(P + sqrt(4 * L2 + P2)) + 
              24 * L4 * P4 * sqrt(4 * L2 + P2) * 
              log(P + sqrt(4 * L2 + P2)) - 
              3072 * L9 * M_PI * log(P + sqrt(4 * L2 + P2)) - 
              1536 * L7 * P2 * M_PI * 
              log(P + sqrt(4 * L2 + P2)) - 
              192 * L5 * P4 * M_PI * 
              log(P + sqrt(4 * L2 + P2)) - 
              192 * L8 * sqrt(4 * L2 + P2) * log(2) * 
              log(P + sqrt(4 * L2 + P2)) - 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * log(P) * 
              log(P + sqrt(4 * L2 + P2)) + 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * 
              log(2 * L + sqrt(4 * L2 + P2)) * 
              log(P + sqrt(4 * L2 + P2)) + 
              96 * L8 * sqrt(4 * L2 + P2) * 
              pow(log(P + sqrt(4 * L2 + P2)),2) - 
              48 * L * pow(4 * L2 + P2,2) * 
              asin(P / sqrt(4 * L2 + P2)) * 
              (-P4 + 2 * L2 * P * sqrt(4 * L2 + P2) + 
               P3 * sqrt(4 * L2 + P2) + 
               24 * L3 * sqrt(4 * L2 + P2) * M_PI + 
               6 * L * P2 * sqrt(4 * L2 + P2) * M_PI + 
               8 * L4 * log(2) + 8 * L4 * log(L) + 
               4 * L * P3 * log(P) - 
               4 * L * P3 * log(2 * L + sqrt(4 * L2 + P2)) - 
               8 * L4 * log(P + sqrt(4 * L2 + P2))) + 
              24 * L4 * log(L) * (-216 * L4 * P - 50 * L2 * P3 + 
                                  P5 - P4 * sqrt(4 * L2 + P2) + 
                                  128 * L5 * M_PI + 64 * L3 * P2 * M_PI + 
                                  8 * L * P4 * M_PI + 8 * L4 * sqrt(4 * L2 + P2) * 
                                  log(2) + 4 * L * P3 * sqrt(4 * L2 + P2) * log(P) - 
                                  4 * L * P3 * sqrt(4 * L2 + P2) * 
                                  log(2 * L + sqrt(4 * L2 + P2)) - 
                                  8 * L4 * sqrt(4 * L2 + P2) * 
                                  log(P + sqrt(4 * L2 + P2))) - 
              768 * L5 * P4 * 
              log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
              192 * L3 * P6 * 
              log((L * (2 + sqrt(4 - P2 / L2))) / P)) + 
             4 * (4 * L2 + P2) * asin(P / sqrt(4 * L2 + P2)) * 
             (-120 * L4 * P5 - 42 * L2 * P7 - 3 * P9 + 
              792 * L6 * P2 * sqrt(4 * L2 + P2) + 
              318 * L4 * P4 * sqrt(4 * L2 + P2) + 
              36 * L2 * P6 * sqrt(4 * L2 + P2) + 
              3 * P8 * sqrt(4 * L2 + P2) - 
              384 * L5 * P4 * M_PI - 192 * L3 * P6 * M_PI - 
              24 * L * P8 * M_PI + 768 * L7 * P * sqrt(4 * L2 + P2) * 
              M_PI + 768 * L5 * P3 * sqrt(4 * L2 + P2) * M_PI + 
              240 * L3 * P5 * sqrt(4 * L2 + P2) * M_PI + 
              24 * L * P7 * sqrt(4 * L2 + P2) * M_PI + 
              4608 * L8 * sqrt(4 * L2 + P2) * pow(M_PI,2) + 
              3456 * L6 * P2 * sqrt(4 * L2 + P2) * 
              pow(M_PI,2) + 864 * L4 * P4 * 
              sqrt(4 * L2 + P2) * pow(M_PI,2) + 
              72 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(M_PI,2) - 576 * L8 * P * log(2) + 
              80 * L6 * P3 * log(2) + 56 * L4 * P5 * log(2) + 
              768 * L7 * P * sqrt(4 * L2 - P2) * log(2) + 
              192 * L5 * P3 * sqrt(4 * L2 - P2) * log(2) - 
              24 * L4 * P4 * sqrt(4 * L2 + P2) * log(2) + 
              3072 * L9 * M_PI * log(2) + 1536 * L7 * P2 * M_PI * log(2) + 
              192 * L5 * P4 * M_PI * log(2) + 
              96 * L8 * sqrt(4 * L2 + P2) * pow(log(2),2) + 
              192 * L8 * P * log(256) + 32 * L6 * P3 * log(256) - 
              4 * L4 * P5 * log(256) - 
              96 * L7 * P * sqrt(4 * L2 - P2) * log(256) - 
              24 * L5 * P3 * sqrt(4 * L2 - P2) * log(256) + 
              96 * L8 * sqrt(4 * L2 + P2) * pow(log(L),2) + 
              24 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(log(P),2) + 2304 * L8 * P * log(4 * L2 + P2) + 
              576 * L6 * P3 * log(4 * L2 + P2) - 
              3072 * L8 * P * log(4 + P2 / L2) - 
              768 * L6 * P3 * log(4 + P2 / L2) + 
              768 * L5 * P4 * 
              log(2 * L + sqrt(4 * L2 - P2)) + 
              192 * L3 * P6 * 
              log(2 * L + sqrt(4 * L2 - P2)) - 
              1536 * L8 * P * log(1 + P / sqrt(4 * L2 + P2)) - 
              384 * L6 * P3 * 
              log(1 + P / sqrt(4 * L2 + P2)) - 
              480 * L5 * P4 * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              168 * L3 * P6 * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              12 * L * P8 * log(2 * L + sqrt(4 * L2 + P2)) + 
              12 * L * P7 * sqrt(4 * L2 + P2) * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              1536 * L6 * P3 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              768 * L4 * P5 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              96 * L2 * P7 * M_PI * 
              log(2 * L + sqrt(4 * L2 + P2)) - 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * log(2) * 
              log(2 * L + sqrt(4 * L2 + P2)) + 
              24 * L2 * P6 * sqrt(4 * L2 + P2) * 
              pow(log(2 * L + sqrt(4 * L2 + P2)),2) + 
              576 * L8 * P * log(P + sqrt(4 * L2 + P2)) + 
              48 * L6 * P3 * log(P + sqrt(4 * L2 + P2)) - 
              24 * L4 * P5 * log(P + sqrt(4 * L2 + P2)) + 
              24 * L4 * P4 * sqrt(4 * L2 + P2) * 
              log(P + sqrt(4 * L2 + P2)) - 
              3072 * L9 * M_PI * log(P + sqrt(4 * L2 + P2)) - 
              1536 * L7 * P2 * M_PI * 
              log(P + sqrt(4 * L2 + P2)) - 
              192 * L5 * P4 * M_PI * 
              log(P + sqrt(4 * L2 + P2)) - 
              192 * L8 * sqrt(4 * L2 + P2) * log(2) * 
              log(P + sqrt(4 * L2 + P2)) + 
              96 * L5 * P3 * sqrt(4 * L2 + P2) * 
              log(2 * L + sqrt(4 * L2 + P2)) * 
              log(P + sqrt(4 * L2 + P2)) + 
              96 * L8 * sqrt(4 * L2 + P2) * 
              pow(log(P + sqrt(4 * L2 + P2)),2) + 
              12 * L * P3 * log(P) * (-24 * L4 * P - 2 * L2 * P3 + 
                                      P5 - P4 * sqrt(4 * L2 + P2) + 
                                      128 * L5 * M_PI + 64 * L3 * P2 * M_PI + 
                                      8 * L * P4 * M_PI + 8 * L4 * 
                                      sqrt(4 * L2 + P2) * 
                                      log(2) - 4 * L * P3 * sqrt(4 * L2 + P2) * 
                                      log(2 * L + sqrt(4 * L2 + P2)) - 
                                      8 * L4 * sqrt(4 * L2 + P2) * 
                                      log(P + sqrt(4 * L2 + P2))) + 
              24 * L4 * log(L) * (-216 * L4 * P - 50 * L2 * P3 + 
                                  P5 - P4 * sqrt(4 * L2 + P2) + 
                                  128 * L5 * M_PI + 64 * L3 * P2 * M_PI + 
                                  8 * L * P4 * M_PI + 8 * L4 * sqrt(4 * L2 + P2) * 
                                  log(2) + 4 * L * P3 * sqrt(4 * L2 + P2) * log(P) - 
                                  4 * L * P3 * sqrt(4 * L2 + P2) * 
                                  log(2 * L + sqrt(4 * L2 + P2)) - 
                                  8 * L4 * sqrt(4 * L2 + P2) * 
                                  log(P + sqrt(4 * L2 + P2))) - 
              768 * L5 * P4 * 
              log((L * (2 + sqrt(4 - P2 / L2))) / P) - 
              192 * L3 * P6 * 
              log((L * (2 + sqrt(4 - P2 / L2))) / P))) / 
    (27648. * L5 * P3 * sqrt(4 * L2 + P2));
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
