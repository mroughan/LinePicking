/* distance_dist.h
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

#ifndef _DISTANCE_DIST_H
#define _DISTANCE_DIST_H
 
/* compute support of the density */
void distance_dist_support(double *, int *, double*, int *, int*);

/* primary function for calling any region through a uniform interface, for multiple t values */
void distance_dist(double *, double *, int *, int *, double*, int *, int*);

/* functions that actually implement each region, for a single t value */
double RectangleDistanceDensity(double, double*);
double SquareDistanceDensity(double, double*);
double LineDistanceDensity(double, double*);
double CubeDistanceDensity(double, double*);
double DiskDistanceDensity(double, double*);
double HyperballDistanceDensity(double, double*);


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */
static void usage_distance_dist();
static void set_pars_distance_dist(int argc, char *argv[], char **file, int *mode, double *parameters);
int main(int argc, char *argv[]);
#endif


#endif


