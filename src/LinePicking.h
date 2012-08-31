
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
#include "Square.h"
#include "Disk.h"
#include "Hyperball.h"
#include "Rectangle.h"
#include "Line.h"	
#include "Cube.h"
#include "Sphere.h"
#include "SphereGeodesic.h"
#include "PrismGeodesic.h"
#include "RectangleManhattan.h"
#include "RectangleMax.h"
#include "HyperSphere.h"


#ifndef _LINEPICKING_H
#define _LINEPICKING_H


#ifndef _NOTR
#include <R.h> /* only include this if we are compiling for R */
#endif


#ifndef PRINT_STDOUT
/* http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html#Variadic-Macros */
#if defined(_MEX) /* MEX */
#define PRINT_STDOUT(...) mexPrintf(__VA_ARGS__)
#elif defined(_NOTR) /* Standalone code or library */
#define PRINT_STDOUT(...) fprintf(stdout, __VA_ARGS__)
#else  /* R */
#define PRINT_STDOUT(...) Rprintf(__VA_ARGS__)
#endif
#endif


typedef struct 
{
    double (* PDF)(double, double *); 
    double (* CDF)(double, double *);
    double (* MEAN)(double *);
    double (* VAR)(double *);
    void   (* SUPPORT)(double*, double *);
    void   (* CHECK_PAR)(double*, int *, char *);
    LinePickingData *DATA; 
    
} LinePickingRec;


#define ExpandFields(_x) &_x##DistancePDF,&_x##DistanceCDF,\
&_x##DistanceMean,&_x##DistanceVar,\
&_x##DistanceSupport,&_x##DistanceCheckParameters,\
&_x##DistanceData

LinePickingRec LinePickingFields[] = 
{ 
    {ExpandFields(Square)},
    {ExpandFields(Disk)},
    {ExpandFields(Hyperball)},
    {ExpandFields(Rectangle)},
    {ExpandFields(Line)},
    {ExpandFields(Cube)},
    {ExpandFields(Sphere)}, 
    {ExpandFields(SphereGeodesic)},
    {ExpandFields(PrismGeodesic)},
    {ExpandFields(RectangleManhattan)},
    {ExpandFields(RectangleMax)},
    {ExpandFields(HyperSphere)}
};

#define elements(x)  (sizeof(x) / sizeof(x[0]))
#define NUMBER_OF_PROBLEMS elements(LinePickingFields)


/** @defgroup api LinePicking API 
 *\addtogroup api 
 *  @{
 */

void LinePickingNumberOfProblems(int *);

void LinePickingPrintAllProblems(void);

void LinePickingAllProblems(char **, char **);

void LinePickingProblemLookup(int *, char**, char**);

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

/* primary function for calculating Mean line length for any region */
void LinePickingVar(double *, int *, double*, int *, int*, char **);


/** @}*/


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */
static void usage_LinePicking();
static void set_pars_LinePicking(int argc, char *argv[],
                                 char **, int *, double *, int *);
int main(int argc, char *argv[]);
#endif /* _STANDALONE */


#endif /* _LINEPICKING_H */



