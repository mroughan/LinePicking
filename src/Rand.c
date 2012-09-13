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
 * @mainpage Rand
 * 
 * @brief Various random number generators
 * 
 * Various random number generators
 *    rand_normal = generate a series of normal (N(0,1)) random variates
 *
 * The goal of these is to provide common support for the simulation
 * routines. Their not really intended for external use.
 * 
 * @authors Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @authors Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @authors Jonothan Tuke <simon.tuke@adelaide.edu.au>
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Rand.h"

/* from http://en.wikipedia.org/wiki/Normal_distribution#Generating_values_from_normal_distribution */
void rand_normal(int N, double *normals) 
{
    int i;
    double tmp, u, v;

    for (i=0; i<floor(N/2); i++)
    {
	u = drand48();
	v = drand48();
	tmp = sqrt(-2.0*log(u));
	normals[2*i] = tmp*cos(2*M_PI*v);
	normals[2*i+1] = tmp*sin(2*M_PI*v);
    }
    if (N % 2 == 1)
    {
	u = drand48();
	v = drand48();
	tmp = sqrt(-2.0*log(u));
	normals[N-1] = tmp*cos(2*M_PI*v);
	/* waste  tmp*sin(2*M_PI*v) */
    }
}



