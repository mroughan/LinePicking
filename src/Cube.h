/**
 * @file Cube.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points within a cube.
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @date 22/09/2012 
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

#ifndef _CUBE_H
#define _CUBE_H

extern LinePickingData CubeDistanceData;

double CubeDistancePDF(double t, double* parameters);

double CubeDistanceCDF(double a, double* b);

double CubeDistanceMean(double* parameters);

double CubeDistanceVar(double* parameters);

void CubeDistanceSupport(double *t, double *parameters);

void CubeDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);


#endif /* _CUBE_H */