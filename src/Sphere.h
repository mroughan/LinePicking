/**
 * @file Sphere.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points on the surface of a sphere.
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


#ifndef _SPHERE_H
#define _SPHERE_H

extern LinePickingData SphereDistanceData;

double SphereDistancePDF(double t, double* parameters);

double SphereDistanceCDF(double a, double* b);

double SphereDistanceMean(double* parameters);

double SphereDistanceVar(double* parameters);

void SphereDistanceSupport(double *t, double *parameters);

void SphereDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

void SphereDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters);

void SphereDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters);

double SphereDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters);

#endif /* _SPHERE_H */

