/* Rectangle.c	
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 * Copyright 2012 Eric Parsonage <eric.parsonagen@adelaide.edu.au>
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


double RectangleDistancePDF(double t, double* parameters)
/* distance density (at t) between two points in a rectangle size a times b */
/*   "Random Distances Within a Rectangle and Between Two Rectangles", B. Ghosh,
 Bulletin of the Calcutta Mathematical Society, Col.43 (1), p.17-24, 1951.
 "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI - R MOSCHOPOULOS -G. PEDERZOLI
 RENDICONT1 DEL CIRCOLO MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190
 */
{
    double a = parameters[0];
    double b = parameters[1];
    double a2 = a*a;
    double b2 = b*b;
    double L2 = a2+ b2;
    double L = sqrt(L2);
    double t2 = t*t;
    double tmp;
    
    if (t<=0) {
        return(0);
    } else if (t >= L) {
        return(0);
    }
    
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


double RectangleDistanceCDF(double a, double* b)
{
    return(-1);
}


double RectangleDistanceMean(double* parameters)
/* mean distance between two points in a rectangle size a times b */
/*   "Random Distances Within a Rectangle and Between Two Rectangles", B. Ghosh,
 Bulletin of the Calcutta Mathematical Society, Col.43 (1), p.17-24, 1951.
 formula (15) on page, 24
 or
 "RANDOM POINTS ASSOCIATED WITH RECTANGLES", A.M. MATHAI - R MOSCHOPOULOS -G. PEDERZOLI
 RENDICONT1 DEL CIRCOLO MATEMATICO DI PALERMO, Serie 11, Tomo XLVIII (1999), pp. 163-190
 p.171, given as 15 E(x)
 */
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


double RectangleDistanceVar(double* parameters)
/* mean distance between two points in a rectangle size a times b */
/* "Random Distances Within a Rectangle and Between Two Rectangles", B. Ghosh,
 Bulletin of the Calcutta Mathematical Society, Col.43 (1), p.17-24, 1951.
 formula (15) on page, 24
 */
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

void RectangleDistanceSupport(double *t, double *parameters)
{
    /* rectangle, side lengths parameters[0], parameters[1] */
    t[0] = 0;
    t[1] = sqrt(parameters[0]*parameters[0] + parameters[1]*parameters[1]);
}


void RectangleDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    /* rectangle, side lengths parameters[0], parameters[1] */
    /* TODO pretty sure one side has to be shorter than the 
     other in order for this to work properly we can force that here */
    *result=0;
}