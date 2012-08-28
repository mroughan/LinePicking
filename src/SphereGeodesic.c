/* SphereGeodesic.c	
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
#include "SphereGeodesic.h"

char *SphereGeodesicDistanceName = "sphere geodesic";
char *SphereGeodesicDistanceDescription = 
                                "sphere geodesic, with radius parameters[0]";
int SphereGeodesicDistanceNpar = 1;


/* distance density (at d) between two points on the surface 
 * of a sphere of radius given in parameters[0] with the distance 
 * measured around the surface of the sphere (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double SphereGeodesicDistancePDF(double d, double* parameters)
{
    double R = parameters[0];
        
    return sin(d / R) / ( 2. * R);
}


/* distance cumulative distribution (at d) between two points on the  
 * surface of a sphere of radius given in parameters[0] with the distance 
 * measured around the surface of the sphere (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double SphereGeodesicDistanceCDF(double d, double* parameters)
{
    double R = parameters[0];
    
    return pow(sin(d / (2. * R)), 2);
}

/* mean distance between two points on the surface of a sphere 
 * of radius given in parameters[0] with the distance 
 * measured around the surface of the sphere (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double SphereGeodesicDistanceMean(double* parameters)
{
    double R = parameters[0];
    
    return (M_PI * R) / 2.;
}


/* variance of distance between two points on the surface of a sphere 
 * of radius given in parameters[0] with the distance 
 * measured around the surface of the sphere (i.e., a geodesic) 
 * TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * soon to be written up somewhere
 */
double SphereGeodesicDistanceVar(double* parameters)
{
    double R = parameters[0];
    
    return ((-8 + M_PI * M_PI) * R * R) / 4.;
}

/* suppport for PDF and CDF of distance between two points on the  
 * surface of a sphere of radius given in parameters[0] with the distance 
 * measured around the surface of the sphere (i.e., a geodesic) 
 */
void SphereGeodesicDistanceSupport(double *t, double *parameters)
{
    double R = parameters[0];

    t[0] = 0;
    t[1] = R * M_PI;
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
void SphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* no extra checking required */
    *result=0;
}
