/* PrismGeodesic.c	
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
#include "PrismGeodesic.h"

char *PrismGeodesicDistanceName = "PrismGeodesic";
char *PrismGeodesicDistanceDescription = "PrismGeodesic description";
int PrismGeodesicDistanceNpar = 1;

double PrismGeodesicDistancePDF(double t, double* parameters)
{
    return -1;
}

double PrismGeodesicDistanceCDF(double t, double* parameters)
{
    return -1;
}

double PrismGeodesicDistanceMean(double* parameters)
{
    return -1;
}

double PrismGeodesicDistanceVar(double* parameters)
{
    return -1;
}

void PrismGeodesicDistanceSupport(double *t, double *parameters)
{

    t[0] = 0;
    t[1] = sqrt(pow(parameters[0],2) + pow(parameters[1],2));
}

void PrismGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    if (parameters[0] > parameters[1])
    {
        
    }
        
    *result=0;
}
