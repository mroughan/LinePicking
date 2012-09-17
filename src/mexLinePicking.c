/* LinePicking.c	
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
 * @mainpage LinePicking
 * 
 * @brief Numerical code for geometric probability problems, 
 * in particular PDFs, CDFs, means and variances for the "line picking" problem.
 * 
 * The problem is a standard problem in stochastic
 * geometry, where we pick lines at random from some region. The typical
 * questions one asks are: what will the mean line length be? What will
 * the Probability Density Function (PDF) be? This software implements the 
 * current list of known PDFs, CDFs, means and variances for such problems.
 * It also provides solutions to some previously unsolved problems. 
 *
 * The library has been designed to provide a small set of entry points  
 * which are callable from R, Matlab and other C programs. Documentation
 * for the R and Matlab bindings to this libary have been provided 
 * in the a format suitable for each of their help systems.
 *
 * Much of this manual is dedicated to documenting functions specific 
 * to a particular problem but users of the library generally only need to 
 * understand the entry points documented in the @ref api.   
 *
 *
 * A simple method for seamlessly extending the library has been provided and
 * is also documented in the @ref api.
 * 
 * 
 * @authors Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @authors Matthew Roughan <matthew.roughan@adelaide.edu.au> 
 * @authors Jonothan Tuke <simon.tuke@adelaide.edu.au>
 */


/** 
 * This section documents the API exposed for the use of other programs.
 * These are the functions called by the R and Matlab wrappers included 
 * in this package.
 * @todo Add some more preamble about the API.
 * @addtogroup api
 */


#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "LinePicking.h"
#include "mexLinePicking.h"



#ifdef _MEX

/*
 * Matlab parts
 *
 */

/* if we fail this we exit with a message */
void CheckNumberInputArg(int nrhs, int required, char* entry_str)
{
    char buffer[256];
    
    if (nrhs == required) return;
    sprintf(buffer,
            "\n%s entry point: requires exactly %d input parameter(s).",
            entry_str, required);
    mexErrMsgTxt(buffer);  
}


/* if we fail this we exit with a message */
void CheckNumberOutputArg(int nlhs, int max, char* entry_str)
{
    char buffer[256];
    
    if (nlhs <= max) return;
    sprintf(buffer,
            "\n%s entry point: requires at most %d output parameter(s), "
            "%d were provided",
            entry_str, max, nlhs);
    mexErrMsgTxt(buffer);  
}

/* if we fail this we exit with a message */            
void CheckProblem(int problem, char* entry_str)
{
    char buffer[256];
    int number_of_problems; 
    
    LinePickingNumberOfProblems(&number_of_problems);
    if (problem < 0 || problem >= number_of_problems) 
    {
        sprintf(buffer, 
                "\n%s entry point: "
                "the problem %d is unsupported.", 
                entry_str, problem);
        
        mexErrMsgTxt(buffer);  
    }
}


/** 
 * This function returns the PDF for the problem. 
 * @param $prhs[1] A vector of points at which to calculate the PDF.
 * @param $prhs[2] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[3] the parameters of the problem. 
 * @param $plhs[0] The output, a vector containing the values g(t) of the PDF 
 * at the points provided.
 */
void mexLinePickingPDF(int nlhs, mxArray *plhs[], int nrhs, 
                       const mxArray *prhs[], int *result, 
                       char **error_str ,  int cmd)
{
    double *t; /* points at which to calculate the distribution */
    double *g; /* value of the distribution at the points t */
    
    int N, M;    /* number of points */
    int Npar;    /* number of parameters */
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *parameters; /*  input parameter vector  */ 
                        
    /* LinePickingPDF returns the PDF for the problem. */
    
    N = (int) mxGetN(prhs[1]); 
    M = (int) mxGetM(prhs[1]); 
    if (N<1 || M>1) 
        mexErrMsgTxt("LinePickingPDF entry point: "
                     "t should be an Nx1 matrix.");
    

    t = mxGetPr(prhs[1]);
    
    problem = (int)mxGetScalar(prhs[2]);
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
    parameters = mxGetPr(prhs[3]);
    
    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    g = mxGetPr(plhs[0]);
    
    LinePickingPDF(t, g, &N, &problem, parameters, 
                   &Npar, result, error_str);
}


/** 
 * This function returns the CDF for the problem. 
 * @param $prhs[1] A vector of points at which to calculate the CDF.
 * @param $prhs[2] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[3] The parameters of the problem. 
 * @param $plhs[0] The output, a vector containing the values G(t) of the CDF 
 * at the points provided.
 */
void mexLinePickingCDF(int nlhs, mxArray *plhs[], int nrhs, 
                       const mxArray *prhs[], int *result, 
                       char **error_str ,  int cmd)
{
    double *t; /* points at which to calculate the distribution */
    double *G; /* value of the distribution at the points t */
    
    int N, M;       /* number of points */
    int Npar;       /* number of parameters */
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *parameters; /* input parameter vector */
    
    N = (int) mxGetN(prhs[1]); 
    M = (int) mxGetM(prhs[1]); 
    if (N<1 || M>1) 
        mexErrMsgTxt("LinePickingCDF entry point: "
                     "t should be an Nx1 matrix.");
    
    t = mxGetPr(prhs[1]);
    
    problem = (int)mxGetScalar(prhs[2]);
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
    parameters = mxGetPr(prhs[3]);
    
    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    G = mxGetPr(plhs[0]);
    
    LinePickingCDF(t, G, &N, &problem, parameters, 
                   &Npar, result, error_str);
    
}



/** 
 * This function returns the inverse CDF for the problem. 
 * @param $prhs[1] A vector G of CDF values, for which we calculate distances
 * @param $prhs[2] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[3] The parameters of the problem. 
 * @param $plhs[0] The output, a vector containing the values t, such that CDF(t) = G
 * at the points provided.
 */
void mexLinePickingInverseCDF(int nlhs, mxArray *plhs[], int nrhs, 
			      const mxArray *prhs[], int *result, 
			      char **error_str ,  int cmd)
{
    double *t; /* points at which to calculate the distribution */
    double *G; /* value of the distribution at the points t */
    
    int N, M;       /* number of points */
    int Npar;       /* number of parameters */
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *parameters; /* input parameter vector */
    
    N = (int) mxGetN(prhs[1]); 
    M = (int) mxGetM(prhs[1]); 
    if (N<1 || M>1) 
        mexErrMsgTxt("LinePickingCDF entry point: "
                     "t should be an Nx1 matrix.");
    
    G = mxGetPr(prhs[1]);
    
    problem = (int)mxGetScalar(prhs[2]);
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
    parameters = mxGetPr(prhs[3]);
    
    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    t = mxGetPr(plhs[0]);
    
    LinePickingInverseCDF(t, G, &N, &problem, parameters, 
			  &Npar, result, error_str);
    
}

/** 
 * This function returns the mean of the length of lines in a given
 * line picking problem. 
 * @param $prhs[1] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[2] The parameters of the problem. 
 * @param $plhs[0] The output, the mean of the length of lines in the given
 * line picking problem.
 */
void mexLinePickingMean(int nlhs, mxArray *plhs[], int nrhs, 
                        const mxArray *prhs[], int *result, 
                        char **error_str ,  int cmd)
{    
    
    double *g; /* mean of distribution*/
    
    int Npar;    /* number of parameters */
    /* the type of region on which to calculate the distribution */
    int problem; 
    double *parameters; /*  input parameter vector */
    
    /* LinePickingMean returns the mean of the distribution. */
    
    problem = (int)mxGetScalar(prhs[1]);
    
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
    parameters = mxGetPr(prhs[2]);
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    g = mxGetPr(plhs[0]);;
    
    LinePickingMean(g, &problem, parameters, &Npar, result, 
                    error_str); 
}       

/** 
 * This function returns the variance of the length of lines in a given
 * line picking problem. 
 * @param $prhs[1] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[2] The parameters of the problem. 
 * @param $plhs[0] The output, the variance of the length of lines in the given
 * line picking problem.
 */
void mexLinePickingVar(int nlhs, mxArray *plhs[], int nrhs, 
                       const mxArray *prhs[], int *result, 
                       char **error_str ,  int cmd)  
{
    double *g; /* variance of distribution*/
    
    int Npar;    /* number of parameters */
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *parameters; /*  input parameter vector */
    
    problem = (int)mxGetScalar(prhs[1]);
    
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
    parameters = mxGetPr(prhs[2]);
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    g = mxGetPr(plhs[0]);;
    
    LinePickingVar(g, &problem, parameters, &Npar, result, 
                   error_str);
}


/** 
 * This function returns the support for the PDF and CDF of a given
 * line picking problem.
 * @param $prhs[1] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[2] The parameters of the problem. 
 * @param $plhs[0] The output, the support for the PDF and CDF for a given 
 * line picking problem.
 */
void mexLinePickingSupport(int nlhs, mxArray *plhs[], int nrhs, 
                           const mxArray *prhs[], int *result, 
                           char **error_str ,  int cmd)
{    
    
    double *g; /* value of the distribution at the points t */
    int Npar;    /* number of parameters */
    /* the type of region on which to calculate the distribution */
	int problem;    
    double *parameters; /*  input parameter vector */
    
    problem = (int)mxGetScalar(prhs[1]);
    
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
    parameters = mxGetPr(prhs[2]);
    
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    g = mxGetPr(plhs[0]);
    
    LinePickingSupport(g, &problem, parameters, &Npar, result, 
                       error_str);
}

/** 
 * This function returns the number of a problem given its name.
 * line picking problem.
 * @param $prhs[1] The problem name (See mexLinePickingPrintAllProblems).
 * @param $plhs[0] The output, the number of the problem with a name
 * that matches the input.
 */
void mexLinePickingNameLookup(int nlhs, mxArray *plhs[], int nrhs, 
                              const mxArray *prhs[], int *result, 
                              char **error_str ,  int cmd)
{    

    char *name;
    int   name_len, status;
    int   problem;
    double *problem_return_val;
    char error_buffer[256];


    if (mxIsChar(prhs[1]) != 1)
    {
        sprintf(error_buffer, 
                "\n%s entry point: "
                "Input must be a string.", 
                MatlabCallList[cmd].MatlabCmdName);
        mexErrMsgTxt(error_buffer);  
    }


    if (mxGetM(prhs[1]) != 1)
	mexErrMsgTxt("Input must be a row vector.");
    

    name_len = (mxGetM(prhs[1]) * mxGetN(prhs[1])) + 1;

    /* Allocate memory for input and output strings. */
    name = mxCalloc(name_len, sizeof(char));

    /* Copy the string data from prhs[1] into a C string name_buf. */
    status = mxGetString(prhs[1], name, name_len);
    if (status != 0) 
	mexWarnMsgTxt("Not enough space. String is truncated.");

    /* creaturn return variable */
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    problem_return_val = mxGetPr(plhs[0]);

    /* Lookup the problem name */
    LinePickingNameLookup(&problem, &name);
    
    /* Return the problem to Matlab */
    *problem_return_val = problem;
}

/** 
 * This function returns all the information the software holds about a given 
 * problem.
 * @param $prhs[1] The problem number (See mexLinePickingPrintAllProblems).
 * @param $plhs[0] The output, the name of the problem.
 * @param $plhs[1] The output, the description of the problem. 
 * @param $plhs[2] The output, Number of parameters the problem requires to 
 * define the shape or region it is defined on. 
 * @param $plhs[3] The output, a default set of parameters for this problem. 
 */
void mexLinePickingProblemLookup(int nlhs, mxArray *plhs[], int nrhs, 
                                 const mxArray *prhs[], int *result, 
                                 char **error_str ,  int cmd)
{
    
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *tmp;
    int j;
    char *name;
    char *description;
    int Npar;
    double parameters[MAX_PARAMETERS];
    
    problem = (int)mxGetScalar(prhs[1]);
    
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
        
    LinePickingProblemLookup(&problem, &name, &description,
                             &Npar, parameters);
    
    /* output argument 1: name, the name of the problem */
    plhs[0] = mxCreateString(name);
    /* output argument 2: description, a brief description of the problem */
    plhs[1] = mxCreateString(description);
    plhs[2] = mxCreateDoubleScalar((double)Npar);
    
    plhs[3] = mxCreateDoubleMatrix(1, Npar, mxREAL);
    
    tmp = mxGetPr(plhs[3]);
    
    for (j = 0; j < Npar; j++)
        tmp[j] = parameters[j];

}


/** 
 * This function prints a list of currently implemented problems.
 */
void mexLinePickingPrintAllProblems(int nlhs, mxArray *plhs[], int nrhs, 
                                    const mxArray *prhs[], int *result, 
                                    char **error_str ,  int cmd)
{    
    /* LinePickingPrintAllProblems prints out a list of implemented problems */
    LinePickingPrintAllProblems();
}  


/** 
 * This function checks that the the parameters supplied are valid input
 * for a given line picking problem.
 * @param $prhs[1] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[2] The parameters of the problem. 
 * @param $result The output, a non-zero value indicates a problem with 
 * the supplied parameters.
 * @param $error_str The output, a string describing the problem with 
 * the supplied problem parameters.
 */
void mexLinePickingCheckParameters(int nlhs, mxArray *plhs[], int nrhs, 
                                   const mxArray *prhs[], int *result, 
                                   char **error_str ,  int cmd)
{
    /*  LinePickingCheckParameters */
    
    
    double *g; /* value of the distribution at the points t */
    int Npar;    /* number of parameters */
     /* the type of region on which to calculate the distribution */
    int problem;   
    double *parameters; /*  input parameter vector */
    
    problem = (int)mxGetScalar(prhs[1]);
    
    Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
    parameters = mxGetPr(prhs[2]);
    
    LinePickingCheckParameters(&problem, parameters, &Npar, result,  error_str);
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);

    g = mxGetPr(plhs[0]);
    g[0] = *result;

    plhs[1] = mxCreateString(*error_str);
    
    /* reset it so we can carry on */
    result = 0;
}

/** 
 * This function returns all the information the software holds about all the 
 * problems it implements.
 * @param $plhs[0] The output, a cell array of problem names.
 * @param $plhs[1] The output, a cell array of descriptions. 
 * @param $plhs[2] The output,  a cell array of integers giving the number of 
 * parameters a problem requires to define the shape or region it is defined on. 
 * @param $plhs[3] The output, a cell array containing a default set of 
 * parameters for each problem. 
 */
void mexLinePickingAllProblems(int nlhs, mxArray *plhs[], int nrhs, 
                               const mxArray *prhs[], int *result, 
                               char **error_str ,  int cmd)
{   
    int i, j;
    /* useful for creating arrays */
    int number_of_problems; 
    
    LinePickingNumberOfProblems(&number_of_problems);
    
    mwSize dims[1]; 
    dims[0] = number_of_problems;

    /* used to output a list of names of the problems */
    char **names = malloc(number_of_problems * sizeof(char *));
    /* used to output a list of descriptions of the problems */
    char **descriptions = malloc(number_of_problems * sizeof(char *));
    int *Npars = malloc(number_of_problems * sizeof(int));        
    double **parameters = malloc(number_of_problems * sizeof(double *));    
    
    double *tmp;
    mxArray *array_ptr;
    
    /* LinePickingAllProblems returns information about the problems. */
    
    /* output argument 1: names, a cell array of problem names */
    plhs[0] = mxCreateCellArray(1, dims);
    
    /* 
     * output argument 2: descriptions, a cell array 
     * of brief descriptions of each problem 
     */
    plhs[1] = mxCreateCellArray(1, dims);

    /* 
     * output argument 3: Npar, a cell array of the 
     * number of parameters in of each problem 
     */
    plhs[2] = mxCreateCellArray(1, dims);

    /* 
     * output argument 4: parameters, a cell array 
     * of the number of parameters in of each problem 
     */
    plhs[3] = mxCreateCellArray(1, dims);

    
    LinePickingAllProblems(names, descriptions, Npars, parameters);
    for (i=0; i < number_of_problems; i++)
    {
        mxSetCell(plhs[0], i, mxCreateString(names[i]));
        mxSetCell(plhs[1], i, mxCreateString(descriptions[i]));
        mxSetCell(plhs[2], i, mxCreateDoubleScalar((double)Npars[i]));
        mxSetCell(plhs[3], i, mxCreateDoubleMatrix(1, Npars[i], mxREAL));
        array_ptr = mxGetCell(plhs[3], i);
        tmp = mxGetPr(array_ptr);
        
        for (j = 0; j < Npars[i]; j++)
            tmp[j] = parameters[i][j];

    }
    
    free(names);
    free(descriptions);
    free(Npars);
    free(parameters);
}


/** 
 * This function returns the number of problems the software currently 
 * implements.
 * @param $plhs[0] The output, the number of line picking problems currently 
 * implemented.
 *
 */
void mexLinePickingNumberOfProblems(int nlhs, mxArray *plhs[], int nrhs, 
                                    const mxArray *prhs[], int *result, 
                                    char **error_str ,  int cmd) 
{
    
    double *g; 
    int number_of_problems; 
    
    LinePickingNumberOfProblems(&number_of_problems);
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    
    /* output argument 1: no_of_problems, the number of implemented problems */
    g = mxGetPr(plhs[0]);
    
    g[0] = number_of_problems;
}


/** 
 * This function returns a set of points from a simulation of a line picking 
 * problem. 
 * @param $prhs[1] The numebr oof distances to simulate.
 * @param $prhs[2] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[3] the parameters of the problem. 
 * @param $plhs[0] The output, a vector containing a set of points 
 * from a simulation of the line picking problem defined in the input.
 */
void mexLinePickingSimPoints(int nlhs, mxArray *plhs[], int nrhs, 
                             const mxArray *prhs[], int *result, 
                             char **error_str ,  int cmd)
{

    double **Points; /* used to return a set of simulated points */
    int Npar;    /* number of parameters */
    int i;	
     /* the type of region on which to calculate the distribution */
    int problem;   
    double *parameters; /*  input parameter vector */ 
                        
    long int seed;
   
    int Ncoords, Npoints;
    char *CoordSystem;
    
    /* input argument 1: Npoints, the number of points to simulate */
    Npoints = (int)mxGetScalar(prhs[1]);
    
    /* 
     * input argument 2: problem, the problem number 
     * (See LinePickingPrintAllProblems) 
     */
    problem = (int)mxGetScalar(prhs[2]);
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    /* input argument 3: parameters, the parameters of the problem */
    Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
    parameters = mxGetPr(prhs[3]);
    
    /* input argument 4: seed, the seed to the random number generator */
    seed = (long int) mxGetScalar(prhs[4]);
    srand48(seed); /* initialize random number generator */
 
    /* determine the correct number of coordinates */
    LinePickingNcoords(&Ncoords, &CoordSystem, &problem, parameters, 
                       &Npar, result, error_str);               
    if (*result != 0) /* something was wrong with parameters */
    {
	mexErrMsgTxt(*error_str);
    }    

    /* 
     * output argument 1: points, returns a Ncoords x Npoints 
     * array containing the simulated points 
     */
    plhs[0] = mxCreateDoubleMatrix(Ncoords, Npoints, mxREAL);
    Points = (double **) malloc((size_t) sizeof(double)*(Npoints));
    for (i=0;i<Npoints;i++) 
    {
		Points[i] = mxGetPr(plhs[0]) + (i*Ncoords);
    }
    
    LinePickingSimPoints(Points, &Npoints, &Ncoords, &problem, parameters, 
                         &Npar, result, error_str);
    free(Points);
}

/** 
 * This function returns a set of distances from a simulation of a line picking 
 * problem. 
 * @param $prhs[1] The numebr oof distances to simulate.
 * @param $prhs[2] The problem number (See mexLinePickingPrintAllProblems).
 * @param $prhs[3] the parameters of the problem. 
 * @param $plhs[0] The output, a vector containing the lengths of lines 
 * from a simulation of the line picking problem defined in the input.
 */
void mexLinePickingSimDistances(int nlhs, mxArray *plhs[], int nrhs, 
                                const mxArray *prhs[], int *result, 
                                char **error_str ,  int cmd)            
{    
  
    int Npar;    /* number of parameters */	
    /* the type of region on which to calculate the distribution */
    int problem;    
    double *parameters; /*  input parameter vector */
    long int seed;
    int N;;
    double *distances; /* used to return a set of simulated distances */
    
    /* LinePickingSimDistances simulates a set of distances for a problem. */
    
    /* input argument 1: N, the number of distances to simulate */
    N = (int)mxGetScalar(prhs[1]);
    
    /* 
     * input argument 2: problem, the problem 
     * number (See LinePickingPrintAllProblems) 
     */
    problem = (int)mxGetScalar(prhs[2]);
    CheckProblem(problem, MatlabCallList[cmd].MatlabCmdName);
    
    /* input argument 3: parameters, the parameters of the problem */
    Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
    parameters = mxGetPr(prhs[3]);
    
    /* input argument 4: seed, the seed to the random number generator */
    seed = (long int) mxGetScalar(prhs[4]);
    srand48(seed); /* initialize random number generator */
    
    /* 
     * output argument 1: distances, returns 
     * a vector of the simulated distances 
     */
    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    distances = mxGetPr(plhs[0]);
    LinePickingSimDistances(distances, &N, &problem, parameters,
                            &Npar, result, error_str);
}




void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int cmd;
    char buffer[256] = "";
    int result;
    char *error_str;
        
    
    if (nrhs < 1)
        mexErrMsgTxt("LinePicking needs at least one input parameter.");
    
    cmd = (int) mxGetScalar(prhs[0]);
    
    /* 
     * The first parameter is an integer 
     * indicating which function should be called 
     * i.e., which entry point to use.
     */
    
    if (cmd < 0 || cmd >= NUMBER_OF_MATLAB_CMDS) 
    {
        sprintf(buffer, "\nEntry point: %d is unsupported.", cmd);
        mexErrMsgTxt(buffer);  
    }
    
    /*
     * Check the number of input and output arguments 
     * we have been passed from Matlab.
     */
    
    CheckNumberInputArg(nrhs, MatlabCallList[cmd].InputArgs, 
                        MatlabCallList[cmd].MatlabCmdName);
    CheckNumberOutputArg(nlhs, MatlabCallList[cmd].OutputArgs, 
                         MatlabCallList[cmd].MatlabCmdName); 
    
    /* 
     * The entry point exists and the number of input and output args 
     * are consistent with entries in MatlabCallList. Clear any 
     * existing errors and call the implementation.
     */
    
    result = 0;
    
    (*MatlabCallList[cmd].CMD)(nlhs, plhs, nrhs, prhs, &result, 
                               &error_str, cmd);
    
    if (result != 0) 
        mexErrMsgTxt(error_str);
}
#endif /* _MEX */


