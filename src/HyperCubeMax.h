/**
 * @file HyperCubeMax.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points within a hyper-cube using the max
 * metric.
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @date 16/09/2012 
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

#ifndef _HYPER_CUBE_MAX_H
#define _HYPER_CUBE_MAX_H

extern LinePickingData HyperCubeMaxDistanceData;

double HyperCubeMaxDistancePDF(double t, double* parameters);

double HyperCubeMaxDistanceCDF(double a, double* b);

double HyperCubeMaxDistanceMean(double* parameters);

double HyperCubeMaxDistanceVar(double* parameters);

void HyperCubeMaxDistanceSupport(double *t, double *parameters);

void HyperCubeMaxDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

void HyperCubeMaxDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters);

void HyperCubeMaxDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters);

double HyperCubeMaxDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters);

#endif /* _HYPER_CUBE_MAX_H */
