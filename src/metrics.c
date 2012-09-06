/* metrics.c	
 *
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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
 * 
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
 * The goal of these is to provide common support for the simulation
 * routines. Their not really intended for external use.
 *
 * Note that not all distance metrics are here, as some, e.g., those relating to geodesics
 * specific manifolds are not generic.
 * 
 * @authors Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @authors Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @authors Jonothan Tuke <simon.tuke@adelaide.edu.au>
 *
 */

#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>
#include "metrics.h" 

#ifndef _NOTR
#include <R.h> /* only include this if we are compiling for R */
#endif

#ifdef _MEX
#include "mex.h" 
#include "matrix.h"
#endif


/**
 * Helper function returns the "distance" metric between two points
 * @param $N is the dimension of the points
 * @param $point1 a vector (length $N) of the coordinates of the first point
 * @param $point2 a vector (length $N) of the coordinates of the second point
 * @return the Euclidean (or L2) distance between the two points.
 */
double DistanceEuclidean(int N, double *point1, double *point2)
{
    int i;
    double sum=0;

    for (i=0;i<N;i++) {
	sum += pow(point1[i]-point2[i], 2.0);
    }
    return sqrt(sum);
}

/**
 * Helper function returns the "distance" metric between two points
 * @param $N is the dimension of the points
 * @param $point1 a vector (length $N) of the coordinates of the first point
 * @param $point2 a vector (length $N) of the coordinates of the second point
 * @return the Manhattan (or taxicab, or rectilinear, or L1) distance 
 *         between the two points.
 */
double DistanceManhattan(int N, double *point1, double *point2)
{
    int i;
    double sum=0;

    for (i=0;i<N;i++) {
	sum += fabs( point1[i] - point2[i] );
    }
    return sum;
}


/**
 * Helper function returns the "distance" metric between two points
 * @param $N is the dimension of the points
 * @param $point1 a vector (length $N) of the coordinates of the first point
 * @param $point2 a vector (length $N) of the coordinates of the second point
 * @return the the maximum over a set of sub-distances (sometimes called the 
 *         Chebyshev distance) distance between the two points.
 */
double DistanceMax(int N, double *point1, double *point2)
{
    int i;
    double max = 0;
    double tmp;
    
    for (i=0;i<N;i++) 
    {
        tmp = fabs(point1[i]-point2[i]);
        max = max > tmp ? max : tmp;
    }
    return max;
}


/**
 * Helper function returns the "distance" metric between two points
 * @param $N is the dimension of the points
 * @param $point1 a vector (length $N) of the coordinates of the first point
 * @param $point2 a vector (length $N) of the coordinates of the second point
 * @param $p the power to use in caculating the Lp distance metric
 * @return the Lp distance between the two points.
 */
double DistanceLp(int N, double *point1, double *point2, double p)
{
    int i;
    double sum=0;
    
    for (i=0;i<N;i++) 
    {
        sum += pow(point1[i]-point2[i], p);
    }
    return pow(sum, 1.0/p);
}
