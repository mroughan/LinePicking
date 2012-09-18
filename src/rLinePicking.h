
/**
 * @file LinePicking.h
 * @brief Exposes to matlab and R a set of functions that implement PDF, CDF,   
 * mean and variance of the distance between two random points 
 * in various geometries.
 *
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au> 
 * @author Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @date 22/09/2012
 */

/*
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
 */


#ifndef _R_LINEPICKING_H
#define _R_LINEPICKING_H

#ifndef _NOTR
#define elements(x)  (sizeof(x) / sizeof(x[0]))
#include <R.h> /* only include this if we are compiling for R */
#include <Rinternals.h>

/** @defgroup rapi LinePicking [R] API 
 *\addtogroup rapi 
 *  @{
 */

/* return a list of all the problems with a description */
SEXP rLinePickingAllProblems(void);

/* check that a problem and a set of parameters are valid */
SEXP rLinePickingCheckParameters(SEXP sexpProblem, SEXP sexpParameters);

/* compute support of the density */
SEXP rLinePickingSupport(SEXP sexpProblem, SEXP sexpParameters);

/* primary function for calculating PDF for any region 
 * through a uniform interface, for multiple t values 
 */
SEXP rLinePickingPDF(SEXP sexpt, SEXP sexpProblem, SEXP sexpParameters);

/* primary function for calculating CDF for any region 
 * through a uniform interface, for multiple t values 
 */
SEXP rLinePickingCDF(SEXP sexpt, SEXP sexpProblem, SEXP sexpParameters);

SEXP rLinePickingInverseCDF(SEXP sexpt, SEXP sexpProblem, SEXP sexpParameters); 

/* primary function for calculating Mean line length for any region */
SEXP rLinePickingMean(SEXP sexpProblem, SEXP sexpParameters);

/* primary function for calculating Median line length for any region */
SEXP rLinePickingMedian(SEXP sexpProblem, SEXP sexpParameters); 

/* primary function for calculating Variance of line lengths for any region */
SEXP rLinePickingVar(SEXP sexpProblem, SEXP sexpParameters);

/* generate a set of points suitable for use in simulating a problem */
SEXP rLinePickingSimPoints(SEXP sexpNpoints, SEXP sexpProblem, 
                           SEXP sexpParameters, SEXP sexpSeed);

/* generate a set of distances by simulating a problem */
SEXP rLinePickingSimDistances(SEXP sexpN, SEXP sexpProblem, 
                              SEXP sexpParameters, SEXP sexpSeed);            

/** @}*/
#endif /* _NOTR */


#endif /* _R_LINEPICKING_H */



