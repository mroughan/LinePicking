/* metrics.h	
 *
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
 *     Copyright 2012 Eric Parsonage <eric.parsonage@adelaide.edu.au>
 *
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
 *
 * $Header$
 */

/** 
 * @mainpage metrics
 * 
 * @brief Code to calculate the various standard distance metrics.
 * 
 * Various standard distance calculations:
 *    Euclidean       = the standard Euclidean (or L2) distance
 *    Manhattan       = the standard Manhattan (or or taxicab, or rectilinear, or L1) distance
 *    Max             = the maximum over a set of sub-distances (sometimes called the Chebyshev distance)
 *    Lp              = the Lp distance 
 *    
 *
 * The goal of these is to provide common support for the simulation
 * routines. Their not really intended for external use.
 *
 * Note that not all distance metrics are here, as some, e.g., those relating to geodesics
 * specific manifolds are not generic.
 * 
 * @authors Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @authors Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @authors Jonothan Tuke <simon.tuke@adelaide.edu.au>
 */

#ifndef _METRICS_H
#define _METRICS_H

double DistanceEuclidean(int, double *, double *);
double DistanceManhattan(int, double *, double *);
double DistanceMax(int, double *, double *);
double DistanceLp(int, double *, double *, double);

#endif

