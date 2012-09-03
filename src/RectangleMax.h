/**
 * @file RectangleMax.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points on a rectangle measured using the
 * max metric.
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

#ifndef _RECTANGLE_MAX_H
#define _RECTANGLE_MAX_H

extern LinePickingData RectangleMaxDistanceData;

double RectangleMaxDistancePDF(double t, double* parameters);

double RectangleMaxDistanceCDF(double t, double* parameters);

double RectangleMaxDistanceMean(double* parameters);

double RectangleMaxDistanceVar(double* parameters);

void RectangleMaxDistanceSupport(double *t, double *parameters);

void RectangleMaxDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

void RectangleMaxDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters);

void RectangleMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters);

double RectangleMaxDistanceMetric(int Ncoords, double *point1, double* point2);


#endif /* _RECTANGLE_MAX_H */
