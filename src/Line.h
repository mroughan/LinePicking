/* Line.h	
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

#ifndef _LINE_H
#define _LINE_H

extern char *LineDistanceName;
extern char *LineDistanceDescription;
extern int LineDistanceNpar;

double LineDistancePDF(double t, double* parameters);

double LineDistanceCDF(double a, double* b);

double LineDistanceMean(double* parameters);

double LineDistanceVar(double* parameters);

void LineDistanceSupport(double *t, double *parameters);

void LineDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

#endif /* _LINE_H */