/**
 * @file HyperSphereGeodesic.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points within a hyper-ball measured
 * along a geodesic.
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

#ifndef _HYPERSPHERE_GEODESIC_H
#define _HYPERSPHERE_GEODESIC_H

extern LinePickingData HyperSphereGeodesicDistanceData;

double HyperSphereGeodesicDistancePDF(double t, double* parameters);

double HyperSphereGeodesicDistanceCDF(double t, double* parameters);

double HyperSphereGeodesicDistanceMean(double* parameters);

double HyperSphereGeodesicDistanceVar(double* parameters);

void HyperSphereGeodesicDistanceSupport(double *t, double *parameters);

void HyperSphereGeodesicDistanceCheckParameters(double *parameters, int *result, 
				      char *error_str);

#endif /* _HYPERSPHERE_GEODESIC_H */
