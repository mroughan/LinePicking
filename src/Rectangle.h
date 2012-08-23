/* Rectangle.h	
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

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

extern char *RectangleDistanceName;
extern char *RectangleDistanceDescription;
extern int RectangleDistanceNpar;


double RectangleDistancePDF(double t, double* parameters);

double RectangleDistanceCDF(double a, double* b);

double RectangleDistanceMean(double* parameters);

double RectangleDistanceVar(double* parameters);

void RectangleDistanceSupport(double *t, double *parameters);

void RectangleDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);



#endif /* _RECTANGLE_H */