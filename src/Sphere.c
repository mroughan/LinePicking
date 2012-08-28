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

/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters parameters[0] is the diameter of the sphere under
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
