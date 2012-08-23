/* LinePicking.h
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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
 * Compute the
 *   Distance distribution between two random points in a region.
 *
 * Most of the actual distributions are included here as inline
 * function (as most are pretty short).
 *
 * $Header$
 */
#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>

#include "Square.h"
#include "Disk.h"
#include "Hyperball.h"
#include "Rectangle.h"
#include "Line.h"	
#include "Cube.h"



#ifndef _LINEPICKING_H
#define _LINEPICKING_H

typedef struct 
{
    double (* PDF)(double, double *); 
    double (* CDF)(double, double *);
    double (* MEAN)(double *);
    double (* VAR)(double *);
    void   (* SUPPORT)(double*, double *);
    void   (* CHECK_PAR)(double*, int *, char *);
    int *Npar;
    char ** name;
    char ** description;
    
} LinePickingRec;


#define ExpandFields(_x) &_x##DistancePDF,&_x##DistanceCDF,\
&_x##DistanceMean,&_x##DistanceVar,\
&_x##DistanceSupport,&_x##DistanceCheckParameters,\
&_x##DistanceNpar,&_x##DistanceName,\
&_x##DistanceDescription

LinePickingRec LinePickingFields[] = 
{ 
    {ExpandFields(Square)},
    {ExpandFields(Disk)},
    {ExpandFields(Hyperball)},
    {ExpandFields(Rectangle)},
    {ExpandFields(Line)},
    {ExpandFields(Cube)} 
};

#define elements(x)  (sizeof(x) / sizeof(x[0]))
#define NUMBER_OF_MODES elements(LinePickingFields)


/* give details of a mode */
void LinePickingModeLookup(int *, char**, char**);
void LinePickingAllmodes();

/* check that a mode and a set of parameters are valid */
void LinePickingCheckParameters(int *, double *, int *, int *, char **);

/* compute support of the density */
void LinePickingSupport(double *, int *, double*, int *, int *, char **);

/* primary function for calculating PDF for any region through a uniform interface, for multiple t values */
void LinePickingPDF(double *, double *, int *, int *, double*, int *, int*, char **);

/* primary function for calculating CDF for any region through a uniform interface, for multiple t values */
void LinePickingCDF(double *, double *, int *, int *, double*, int *, int*, char **);

/* primary function for calculating Mean line length for any region */
void LinePickingMean(double *, int *, double*, int *, int*, char **);

/* primary function for calculating Mean line length for any region */
void LinePickingVar(double *, int *, double*, int *, int*, char **);


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */
static void usage_LinePicking();
static void set_pars_LinePicking(int argc, char *argv[], char **, int *, double *, int *);
int main(int argc, char *argv[]);
#endif


#endif


