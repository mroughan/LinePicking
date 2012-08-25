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

#include "SphereGeodesic.h"

char *SphereGeodesicDistanceName = "SphereGeodesic";
char *SphereGeodesicDistanceDescription = "SphereGeodesic description";
int SphereGeodesicDistanceNpar = 1;

double SphereGeodesicDistancePDF(double t, double* parameters)
{
    return -1;
}

double SphereGeodesicDistanceCDF(double a, double* b)
{
    return -1;
}

double SphereGeodesicDistanceMean(double* parameters)
{
    return -1;
}

double SphereGeodesicDistanceVar(double* parameters)
{
    return -1;
}

void SphereGeodesicDistanceSupport(double *t, double *parameters)
{

    t[0] = 0;
    t[1] = 1;
}

void SphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    *result=0;
}
