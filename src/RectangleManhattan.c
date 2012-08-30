/* Rectangle.c	
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

#include "Rectangle.h"

char *RectangleDistanceName = "rectangle";
char *RectangleDistanceDescription = "rectangle, side lengths parameters[0],"
" parameters[1]";
int RectangleDistanceNpar = 2;


/**
 * Implements the PDF of the distance between two random points on a
 * rectangle.
 *
 * From "Random Distances Within a Rectangle and Between Two Rectangles",
 * B. Ghosh, Bulletin of the Calcutta Mathematical Society, Col.43 (1), 
 * p.17-24, 1951. "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI -
 * R MOSCHOPOULOS -G. PEDERZOLI RENDICONT1 DEL CIRCOLO 
 * MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190 
 * @param $t The distance to calculate the density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The density at $t.
 */
double RectangleDistancePDF(double t, double* parameters)
{
    double a = parameters[0];
    double b = parameters[1];
    double a2 = a*a;
    double b2 = b*b;
    double L2 = a2+ b2;
    double L = sqrt(L2);
    double t2 = t*t;
    double tmp;
    
    /* make sure a < b */
    if (a > b) 
    {
        tmp = b;
        b = a;
        a = tmp;
        a2 = a*a;
        b2 = b*b;
    }
    
    /* three cases */
    if (t <= a)
    {
        return( 4*( (a*b*M_PI)/2 - (a+b)*t + t2/2 
                   )*t/(a2*b2) );
    } else if (t>a && t<=b) 
    {
        return( 4*( a*b*asin(a/t) 
                   - a2/2 - b*t
                   + b*sqrt(t2-a2) 
                   )*t/(a2*b2) );
    } else {
        return( 4*(  a*b*(asin(a/t) - asin(sqrt(1 - b2/(t2)))) 
                   - (a2 + b2 + t2)/2
                   + a*sqrt(t2-b2)
                   + b*sqrt(t2-a2) 
                   )*t/(a2*b2));
    }
    
}


/**
 * Implements the CDF of the distance between two random points on a rectangle.
 *
 * Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @todo Write up the derivation.
 * @param $w The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The cumulative density at $w.
 */
double RectangleDistanceCDF(double w, double* parameters)
{
    
    double L = parameters[0];
    double H = parameters[1];
    double L2 = L * L;
    double H2 = H * H;
    double M = sqrt(L2 + H2);
    double tmp;
    double w2 = w * w;
   
    /* make sure H < L */
    if (H > L) 
    {
        tmp = L;
        L = H;
        H = tmp;
        L2 = L * L;
        H2 = H * H;
    }
    
    /* three cases */
    if (w <= H)
    {
        return (w2 * (6 * H * L * M_PI - 8*(H + L)* w + 3 * w2)) / 
                (6.* H2 * L2);
    } 
    else if (w > H && w <= L) 
    {
        return  (
                    (H2 * H2) + 
                    8 * L * w2 * (sqrt(w2- H2) - w) + 
                    H2 * (-6 * w2 + 4 * L * sqrt(w2 - H2)) + 
                    /* 12 * H * L * w2 * atan( H / sqrt(w2 - H2)) */
                    12 * H * L * w2 * asin(H / w)
                ) / (6. * H2 * L2);        
        
    }
    else 
    {
        return  (
                    (H2 * H2) + (L2 * L2) + 
                    4 * H * sqrt(w2 - L2) * (L2 + 2 * w2) + 
                    H2 * (-6 * w2 + 4 * L * sqrt(w2 - H2)) + 
                    w2 * (-6 * L2 - 3 * w2 + 8 * L * sqrt(w2 - H2)) + 
                    12 * H * L * w2 * (
                                            /* atan(L / sqrt(w2 - L2)) - */ 
                                            asin(L / w) -
                                            (M_PI / 2) +
                                            /* atan(H / sqrt(w2 - H2)) */
                                            asin(H / w)
                                        )
                 ) / (6.* H2 * L2);
 
    }
   
}


/**
 * Calculates the mean distance between two random points on a rectangle.
 *
 * From "Random Distances Within a Rectangle and Between Two Rectangles",
 * B. Ghosh, Bulletin of the Calcutta Mathematical Society, Col.43 (1), 
 * p.17-24, 1951. "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI -
 * R MOSCHOPOULOS - G. PEDERZOLI RENDICONT1 DEL CIRCOLO 
 * MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190 
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The mean distance between two random points on a rectangle.
 */
double RectangleDistanceMean(double* parameters)
{
    double a = parameters[0];
    double b = parameters[1];
    double a2 = a*a;
    double b2 = b*b;
    double M2 = a2 + b2;
    double M = sqrt(M2);
    double tmp;
    
    return( (b2*acosh(M/b)/a + a2*acosh(M/a)/b)/6.0 +
           (pow(a,3)/b2 + pow(b,3)/a2)/15.0 -
           M*(a2/b2 + b2/a2 - 3)/15.0
           );
}


/**
 * Calculates the variance of distances between two random points on a 
 * rectangle.
 *
 * From "Random Distances Within a Rectangle and Between Two Rectangles",
 * B. Ghosh, Bulletin of the Calcutta Mathematical Society, Col.43 (1), 
 * p.17-24, 1951. "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI -
 * R MOSCHOPOULOS - G. PEDERZOLI RENDICONT1 DEL CIRCOLO 
 * MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190 
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The variance of distances between two random points on a rectangle.
 */
double RectangleDistanceVar(double* parameters)
{
    double a = parameters[0];
    double b = parameters[1];
    double a2 = a*a;
    double b2 = b*b;
    double M2 = a2 + b2;
    double M = sqrt(M2);
    double tmp = RectangleDistanceMean(parameters);
    
    return( M2/6.0 - tmp*tmp );
}


/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random points on a rectangle.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points on a rectangle.
 * @param $parameters $parameters[0] is the length of one side of the rectangle
 * and $parameters[1] is the length of the other. 
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void RectangleDistanceSupport(double *t, double *parameters)
{
    /* rectangle, side lengths parameters[0], parameters[1] */
    t[0] = 0;
    t[1] = sqrt(parameters[0]*parameters[0] + parameters[1]*parameters[1]);
}


/**
* Intended to determine if the parameters supplied are valid input 
* to the other functions implemented in this file. However as 
* the calling function checks that the supplied parameters are positive 
* this is merely a place holder to allow for a complete implementation 
* in geometries that have more complex relationships between parameters.
*
* @param $parameters  parameters[0] and parameters[1] are the lengths 
* of the sides of the rectangle under consideration.
* @param $result Pointer to storage for an integer indicating any errors  
* in the supplied parameters.
* @param $error_str Pointer to storage for a message explaining any errors
* in the supplied parameters. 
* @return Any error conditions are indicated by placing a value other than 0 
* in the location pointed to by $result and a message explaining the error 
* is copied in to the location pointed to $error_str 
*/
void RectangleDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    /* no further checks needed */
    *result=0;
}