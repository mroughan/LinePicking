LinePicking
============

Numerical code for geometric probability problems, in particular
density functions for the "line picking" problem, i.e., what is the
length of a line picked at random from some region.

Details:

 src/

    LinePicking.h

        Contains C library routines to compute the densities for "line
        picking" problems on various regions.

    beta.h: has required incomplete and complete beta functions
	  LinePicking_test.m: has Matlab test scripts, which
	  also generate nice plots of the distributions

    LinePicking.c

        Contains bridges to allow the routines in .h to be called from
        another C program, Matlab (through MEX) and eventually through R.


 Matlab/ - Matlab code and location for mex files

    LinePicking_test.m

       Matlab code to show how to call the MEX routines, and to test
       out various cases, compute Laplace transforms, and draw plots.

    LinePicking_numerical.m

       A comparison of exact computations with simulation-based
       estimates. 

 R/ - 
    DistanceDist.R
 
      R wrapper function

    ????

      Example of how to call the function in R

 man/ - documentation


Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

