/* SphereGeodesic.c	
 *
 *     Copyright 2012 Eric Parsonage <eric.parsonagen@adelaide.edu.au>
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

void SphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* no extra checking required */
    *result=0;
}
