/* Disk.c	
 *
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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

#include "Disk.h"

char *DiskDistanceName = "disk";
char *DiskDistanceDescription = "disk, with radius parameters[0]";
int DiskDistanceNpar = 1;

double DiskDistancePDF(double t, double* parameters)
/* distance density (at t) between two points in a disk radius r */
/*    http://mathworld.wolfram.com/BallLinePicking.html */
{
    double r = parameters[0];
    double d = 2*r;
    double r2 = r*r;
    double t2 = t*t;			     
    double part1, part2, c;
    
    if (t <= 0) 
    {
        return(0);
    } 
    else if (t >= d) 
    {
        return(0);
    }
    
    /* two cases */
    c = acos(t/(2*r));
    part1 = 4*t*c / (M_PI*r2);
    part2 = 2*t2*sqrt(1 - (t2/(4*r2)))/(M_PI*r*r2);
    return(part1 - part2);
}

double DiskDistanceCDF(double s, double* parameters)
    /* culmative density function */
    /* TODO Derived by Eric Parsonage <eric.parsonage@adelaide.edu.au> 
     * soon to be written up somewhere
     */
{    
    double R = parameters[0];
    double R2 = R*R;
    double R3 = R2 * R;
    double s2 = s*s;			     
    double s3 = s2 * s;
    
    if (s <= 0) 
    {
        return(0);
    } 
    else if (s >= R + R) 
    {
        return(1);
    }
     
    return  (
                -(sqrt(4 - s2 / R2) * (2 * R2 * s + s3)) / 4. + 
                2 * R * s2 * acos(s / (2. * R)) + 
                2 * R3 * asin(s / (2. * R))
            ) / (M_PI * R3);
}

double DiskDistanceMean(double* parameters)
/* mean distance between two points in a disk radius r */
/*    http://mathworld.wolfram.com/BallLinePicking.html */
{
    return(parameters[0]*128.0/(45.0*M_PI));
}

double DiskDistanceVar(double* parameters)
/* variance distance between two points in a disk radius r */
/*    calculated numerically */
{
    return(parameters[0]*parameters[0]*0.180224062826);
}

void DiskDistanceSupport(double *t, double *parameters)
{
    /* disk, with radius parameters[0] */
    t[0] = 0;
    t[1] = 2*parameters[0];
}

void DiskDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* disk, with radius parameters[0] */
    *result=0;
}
