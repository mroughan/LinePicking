/* Line.c	
 *
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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

#include "Line.h"

char *LineDistanceName = "line";
char *LineDistanceDescription = "line, length parameters[0]";
int LineDistanceNpar = 1;

double LineDistancePDF(double t, double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    

    return(2*(1-t/L)/L);
}

double LineDistanceCDF(double t, double* parameters)
/* distance density (at t) between two points on a line length parameter[0] */
/*    http://mathworld.wolfram.com/LineLinePicking.html */
{
    double L = parameters[0];
    t = t / L;
    
    return(t*(2.0-t));

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

/**
 * Intended to determine if the parameters supplied are valid input 
 * to the other functions implemented in this file. However as there is
 * only one parameter and the calling function checks that it is positive 
 * this is merely a place holder to allow for a complete implementation 
 * in geometries that have more complex relationships between parameters.
 *
 * @param $parameters parameters[0] is the length of the line under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 */

void LineDistanceCheckParameters(double *parameters, int *result, 
                                 char *error_str)
{
    /* line, length parameters[0] */
    *result=0;
}
