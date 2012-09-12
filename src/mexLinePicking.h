
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

#include "LinePicking.h"

#ifndef _MEX_LINEPICKING_H
#define _MEX_LINEPICKING_H

#ifdef _MEX
#include "mex.h"
#include "matrix.h"

typedef struct 
{
    void (* CMD)(int nlhs, mxArray *plhs[], 
                 int nrhs, const mxArray *prhs[], 
                 int *result, char **error_str, int cmd);
    char *MatlabCmdName;
    int InputArgs;
    int OutputArgs;
} MatlabCallRec;


/* 
 * define ExpandForMatlab in a way that produces function 
 * prototypes when MatlabDefinitions.def is included 
 */
#ifdef ExpandForMatlab
#undef ExpandForMatlab
#endif
#define ExpandForMatlab(_x, _in, _out) void mex##_x (int nlhs, mxArray *plhs[],\
int nrhs, const mxArray *prhs[], int *result, \
char **error_str, int cmd);

#include "MatlabDefinitions.def"


/* 
 * define ExpandForMatlab in a way that produces an array of  
 * MatlabCallRec structs when MatlabDefinitions.def is included 
 */
#ifdef ExpandForMatlab
#undef ExpandForMatlab
#endif
#define ExpandForMatlab(_x, _in, _out) { &mex##_x, #_x, _in, _out },

MatlabCallRec MatlabCallList[] =
{
#include "MatlabDefinitions.def"
};

#define elements(x)  (sizeof(x) / sizeof(x[0]))
#define NUMBER_OF_MATLAB_CMDS elements(MatlabCallList)
/* 
 * Note the following prototypes are already created by the def file 
 * included above. However doxygen doesn't include them in the
 * documentation unless they are explictly defined
 */

/** @defgroup matlabapi LinePicking [Matlab] API 
 *\addtogroup matlabapi 
 *  @{
 */


void mexLinePickingPDF(int nlhs, mxArray *plhs[], 
                       int nrhs, const mxArray *prhs[], 
                       int *result, char **error_str, int cmd);

void mexLinePickingCDF(int nlhs, mxArray *plhs[], 
                       int nrhs, const mxArray *prhs[], 
                       int *result, char **error_str, int cmd);

void mexLinePickingMean(int nlhs, mxArray *plhs[], 
                        int nrhs, const mxArray *prhs[], 
                        int *result, char **error_str, int cmd);

void mexLinePickingVar(int nlhs, mxArray *plhs[], 
                       int nrhs, const mxArray *prhs[], 
                       int *result, char **error_str, int cmd);

void mexLinePickingSupport(int nlhs, mxArray *plhs[], 
                           int nrhs, const mxArray *prhs[], 
                           int *result, char **error_str, int cmd);

void mexLinePickingProblemLookup(int nlhs, mxArray *plhs[], 
                                 int nrhs, const mxArray *prhs[], 
                                 int *result, char **error_str, int cmd);

void mexLinePickingNameLookup(int nlhs, mxArray *plhs[], 
                              int nrhs, const mxArray *prhs[], 
                              int *result, char **error_str, int cmd);

void mexLinePickingPrintAllProblems(int nlhs, mxArray *plhs[], 
                                    int nrhs, const mxArray *prhs[], 
                                    int *result, char **error_str, int cmd);

void mexLinePickingCheckParameters(int nlhs, mxArray *plhs[], 
                                   int nrhs, const mxArray *prhs[], 
                                   int *result, char **error_str, int cmd);

void mexLinePickingAllProblems(int nlhs, mxArray *plhs[], 
                               int nrhs, const mxArray *prhs[], 
                               int *result, char **error_str, int cmd);

void mexLinePickingNumberOfProblems(int nlhs, mxArray *plhs[], 
                                    int nrhs, const mxArray *prhs[], 
                                    int *result, char **error_str, int cmd);


void mexLinePickingSimPoints(int nlhs, mxArray *plhs[], 
                             int nrhs, const mxArray *prhs[], 
                             int *result, char **error_str, int cmd);

void mexLinePickingSimDistances(int nlhs, mxArray *plhs[], 
                                int nrhs, const mxArray *prhs[], 
                                int *result, char **error_str, int cmd);

/** @}*/

#endif /* _MEX */

#endif /* _MEX_LINEPICKING_H */



