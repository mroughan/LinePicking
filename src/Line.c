/* Line.c	
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

#include "line.h"

char *LineDistanceName = "line";
char *LineDistanceDescription = "line, length parameters[0]";
int LineDistanceNpar = 1;

double LineDistancePDF(double t, double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    
    if (t<0) {
        return(0);
    } else if (t >= L) {
        return(0);
    } else {
        return(2*(1-t/L)/L);
    }
}

double LineDistanceCDF(double t, double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    t = t / L;
    
    if (t<0) {
        return(0);
    } else if (t >= L) {
        return(1);
    } else {
        return(t*(2.0-t));
    }
}

double LineDistanceMean(double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    return(parameters[0]*1.0/3.0);
}

double LineDistanceVar(double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    return(parameters[0]*parameters[0]*1.0/18.0);
}


void LineDistanceSupport(double *t, double *parameters)
{
    /* line, length parameters[0] */
    t[0] = 0;
    t[1] = parameters[0];
}


void LineDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* line, length parameters[0] */
    *result=0;
}