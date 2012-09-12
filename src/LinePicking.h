
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



#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>

#include "LinePickingData.h"

#ifndef _LINEPICKING_H
#define _LINEPICKING_H


#ifndef PRINT_STDOUT
/* http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html#Variadic-Macros */
#if defined(_MEX) /* MEX */
#include "mex.h"
#define PRINT_STDOUT(...) mexPrintf(__VA_ARGS__)
#elif defined(_NOTR) /* Standalone code or library */
#define PRINT_STDOUT(...) fprintf(stdout, __VA_ARGS__)
#else  /* R */
#include <R.h> 
#include <Rinternals.h>
#define PRINT_STDOUT(...) Rprintf(__VA_ARGS__)
#endif
#endif


/** @defgroup api LinePicking [C] API 
 *\addtogroup api 
 *  @{
 */

/* return the number of implemented problems */
void LinePickingNumberOfProblems(int *);

/* print a list of problems to stdout */
void LinePickingPrintAllProblems(void);

/* return a list of all the problems with a description */
void LinePickingAllProblems(char **names, char **, int *, double **);


/* lookup problems by name or number, respectively */
void LinePickingNameLookup(int *, char **);
void LinePickingProblemLookup(int *, char**, char**,  int *, double *);

/* given a problem lookup how many parameters it takes */
void LinePickingProblemNparLookup(int *problem, int *Npar); 


/* check that a problem and a set of parameters are valid */
void LinePickingCheckParameters(int *, double *, int *, int *, char **);

/* compute support of the density */
void LinePickingSupport(double *, int *, double*, int *, int *, char **);

/* primary function for calculating PDF for any region 
 * through a uniform interface, for multiple t values 
 */
void LinePickingPDF(double *, double *, int *,
                    int *, double*, int *, int*, char **);

/* primary function for calculating CDF for any region 
 * through a uniform interface, for multiple t values 
 */
void LinePickingCDF(double *, double *, int *,
                    int *, double*, int *, int*, char **);

/* primary function for calculating Mean line length for any region */
void LinePickingMean(double *, int *, double*, int *, int*, char **);

/* primary function for calculating Variance of line lengths for any region */
void LinePickingVar(double *, int *, double*, int *, int*, char **);

/* return the number of coordinates, and a description of the coordinate system */
void LinePickingNcoords(int *, char **, int *, double*, int *, int *, char **);

/* generate a set of points suitable for use in simulating a problem */
void LinePickingSimPoints(double **points, int *Npoints, int *Ncoords,
			  int *problem, double* parameters, int *Npar,
			  int *result, char **error_str);

/* generate a set of distances by simulating a problem */
void LinePickingSimDistances(double *distances, int *N, int *problem, 
 			     double* parameters, int *Npar, int *result, 
			     char **error_str);


#endif /* _LINEPICKING_H */



