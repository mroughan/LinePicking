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

#ifndef _LINEPICKING_H
#define _LINEPICKING_H

/* arrays to map modes to name  */
#define NUMBER_OF_MODES 6
char *mode_name[NUMBER_OF_MODES] = {"square", "disk", "hyper-ball", "rectangle", "line", "cube"};
char *mode_description[NUMBER_OF_MODES] = {
    "square, with side length parameters[0]",
    "disk, with radius parameters[0]",
    "hyper-ball, with dimension parameters[0], and radius parameters[1] ",
    "rectangle, side lengths parameters[0], parameters[1]",
    "line, length parameters[0]",
    "cube, side length parameters[0]",
};
/* how many parameters each mode takes */
int mode_pars[NUMBER_OF_MODES] = {1, 1, 2, 2, 1, 1}; 

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

/* functions that actually implement each region, for a single t value */
/*    but don't call these directly, as they don't check for valid inputs 
      call via LinePickingPDF */ 
double UnknownDistancePDF(double, double*);
double SquareDistancePDF(double, double*);
double DiskDistancePDF(double, double*);
double HyperballDistancePDF(double, double*);
double RectangleDistancePDF(double, double*);
double LineDistancePDF(double, double*);
double CubeDistancePDF(double, double*);

/* means */
double UnknownDistanceMean(double*);
double SquareDistanceMean(double*);
double DiskDistanceMean(double*);
double HyperballDistanceMean(double*);
double RectangleDistanceMean(double*);
double LineDistanceMean(double*);
double CubeDistanceMean(double*);

/* Cumulative Distribution Functions, where known */
double UnknownDistanceCDF(double, double*);
double SquareDistanceCDF(double, double*);
/* double DiskDistanceCDF(double, double*); */
/* double HyperballDistanceCDF(double, double*); */
/* double RectangleDistanceCDF(double, double*); */
double LineDistanceCDF(double, double*);
/* double CubeDistanceCDF(double, double*); */

/* variances, where known */
double UnknownDistanceVar(double*);
double SquareDistanceVar(double*);
double DiskDistanceVar(double*);
double HyperballDistanceVar(double*);
double RectangleDistanceVar(double*);
double LineDistanceVar(double*);
double CubeDistanceVar(double*);


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


