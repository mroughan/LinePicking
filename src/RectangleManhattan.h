/**
 * @file Rectangle.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points on a rectangle.
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @date 22/09/2012
 */

/*
 *
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

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

extern char *RectangleDistanceName;
extern char *RectangleDistanceDescription;
extern int RectangleDistanceNpar;


double RectangleDistancePDF(double t, double* parameters);

double RectangleDistanceCDF(double t, double* parameters);

double RectangleDistanceMean(double* parameters);

double RectangleDistanceVar(double* parameters);

void RectangleDistanceSupport(double *t, double *parameters);

void RectangleDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);



#endif /* _RECTANGLE_H */