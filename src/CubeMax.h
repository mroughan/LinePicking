/**
 * @file CubeMax.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points within a cube using the max
 * metric.
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @date 15/09/2012 
 */

/*
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

#ifndef _CUBE_MAX_H
#define _CUBE_MAX_H

extern LinePickingData CubeMaxDistanceData;

double CubeMaxDistancePDF(double t, double* parameters);

double CubeMaxDistanceCDF(double a, double* b);

double CubeMaxDistanceMean(double* parameters);

double CubeMaxDistanceVar(double* parameters);

void CubeMaxDistanceSupport(double *t, double *parameters);

void CubeMaxDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

void CubeMaxDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters);

void CubeMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters);

double CubeMaxDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters);

#endif /* _CUBE_MAX_H */
