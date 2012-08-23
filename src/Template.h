/* XXX.h	
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


#ifndef _YYY_H
#define _YYY_H


char * XXXDistanceName;
char * XXXDistanceDescription;
int XXXDistanceNpar;


double XXXDistancePDF(double t, double* parameters);

double XXXDistanceCDF(double a, double* b);

double XXXDistanceMean(double* parameters);

double XXXDistanceVar(double* parameters);

void XXXDistanceSupport(double *t, double *parameters);

void XXXDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

#endif /* _YYY_H */

