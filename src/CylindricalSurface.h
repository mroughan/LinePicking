/**
 * @file CylindricalSurface.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points on a cylindrical surface.
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

#ifndef _CYLINDRICAL_SURFACE_H
#define _CYLINDRICAL_SURFACE_H

extern LinePickingData CylindricalSurfaceDistanceData;

double CylindricalSurfaceDistancePDF(double t, double* parameters);

double CylindricalSurfaceDistanceCDF(double t, double* parameters);

double CylindricalSurfaceDistanceMean(double* parameters);

double CylindricalSurfaceDistanceVar(double* parameters);

void CylindricalSurfaceDistanceSupport(double *t, double *parameters);

void CylindricalSurfaceDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

void CylindricalSurfaceDistanceNcoords(int *Ncoords, char **CoordSystem, 
                                       double* parameters);

void CylindricalSurfaceDistanceSimPoints(double **points, int *Npoints, 
                                         int *Ncoords, double* parameters);

double CylindricalSurfaceDistanceMetric(int Ncoords, double *point1, 
                                        double* point2, double* parameters);



#endif /* _CYLINDRICAL_SURFACE_H */
