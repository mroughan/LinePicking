/**
 * @file Hyperball.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points within a hyper-ball.
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

#ifndef _HYPERBALL_H
#define _HYPERBALL_H


extern LinePickingData HyperballDistanceData;

double HyperballDistancePDF(double t, double* parameters);

double HyperballDistanceCDF(double t, double* parameters);

double HyperballDistanceMean(double* parameters);

double HyperballDistanceVar(double* parameters);

void HyperballDistanceSupport(double *t, double *parameters);

void HyperballDistanceCheckParameters(double *parameters, int *result, 
				      char *error_str);

void HyperballDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters);

void HyperballDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters);

double HyperballDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters);


#endif /* _HYPERBALL_H */
