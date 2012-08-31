/**
 * @file PrismGeodesic.h
 * @brief Functions to provide PDF, CDF, mean and variance of the  
 * distance between two random points on the surface (not including the ends)
 * of an upright prism of any cross section. The distance is measured around 
 * the surface i.e., it is a geodesic.
 *
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


#ifndef _PRISM_GEODESIC_H
#define _PRISM_GEODESIC_H


extern LinePickingData PrismGeodesicDistanceData;

double PrismGeodesicDistancePDF(double t, double* parameters);

double PrismGeodesicDistanceCDF(double t, double* parameters);;

double PrismGeodesicDistanceMean(double* parameters);

double PrismGeodesicDistanceVar(double* parameters);

void PrismGeodesicDistanceSupport(double *t, double *parameters);

void PrismGeodesicDistanceCheckParameters(double *parameters, int *result, 
                                char *error_str);

#endif /* _Prism_GEODESIC_H */

