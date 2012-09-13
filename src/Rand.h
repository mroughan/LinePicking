/* Rand.h
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

#ifndef _RAND_H
#define _RAND_H

void rand_normal(int N, double *normals);


#endif
