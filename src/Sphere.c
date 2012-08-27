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

#include "Sphere.h"

char *SphereDistanceName = "sphere";
char *SphereDistanceDescription = "sphere, with radius parameters[0]";
int SphereDistanceNpar = 1;


/* distance density (at s) between two points on the surface 
 * of a sphere of radius given in parameters[0] 
 * http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistancePDF(double s, double* parameters)
{
    double R = parameters[0];
    
    return s / (2. * R * R);    
}


/* distance cumulative distribution (at s) between two points on the surface 
 * of a sphere of radius given in parameters[0] not given at the link above. 
 * However the integration is trivial
 */
double SphereDistanceCDF(double s, double* parameters)
{
    double R = parameters[0];

    return (s * s) / (4. * R * R);
}

/* mean distance between two points on the surface of a sphere of radius 
 * given in parameters[0] http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistanceMean(double* parameters)
{
    double R = parameters[0];
    
    return (4. * R) / 3.;
}

/* variance of distances between two points on the suface of a sphere of radius 
 * given in parameters[0] http://mathworld.wolfram.com/SphereLinePicking.html
 */
double SphereDistanceVar(double* parameters)
{
    double R = parameters[0];
    
    return (2. *  R * R) / 9.;
}

/* suppport for PDF and CDF of distance between two points on the  
 * surface of a sphere of radius given in parameters[0] 
 */
void SphereDistanceSupport(double *t, double *parameters)
{

    double R = parameters[0];
    
    t[0] = 0;
    
    /* the longest line is the diameter of the sphere */
    t[1] = 2 * R;
}

void SphereDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{   
    /* nothing further to check */
    *result=0;
}
