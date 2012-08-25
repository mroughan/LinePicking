/* Sphere.c	
 *
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

#include "Sphere.h"

char *SphereDistanceName = "Sphere";
char *SphereDistanceDescription = "Sphere description";
int SphereDistanceNpar = 1;

double SphereDistancePDF(double t, double* parameters)
{
    return -1;
}

double SphereDistanceCDF(double a, double* b)
{
    return -1;
}

double SphereDistanceMean(double* parameters)
{
    return -1;
}

double SphereDistanceVar(double* parameters)
{
    return -1;
}

void SphereDistanceSupport(double *t, double *parameters)
{

    t[0] = 0;
    t[1] = 1;
}

void SphereDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    *result=0;
}
