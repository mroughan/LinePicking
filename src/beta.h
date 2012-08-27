/**
 * @file Beta.h
 * @brief Implements the beta function and the regularized incomplete 
 * beta function.
 *
 * @author Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @date 22/09/2012 
 */

/*
 *     Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au> 
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
#include <stdio.h>
#include <stdlib.h>

#ifndef _BETA_H
#define _BETA_H

/* beta function in terms of gamma functions */
double beta(double, double);

/* regularized incomplete beta function */
double beta_inc(double, double, double);

#endif
