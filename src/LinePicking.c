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
#include "LinePicking.h"
#include "beta.h" 

#ifndef _NOTR
#include <R.h> /* only include this if we are compiling for R */
#endif

#ifdef _MEX
#include "mex.h"
#include "matrix.h"
#endif



/**
 * Helper function to expose the number of currently implemented problems.
 * @param $N Pointer to an integer to store the number of currently 
 * implemented problems. 
 * @return The number of currently implemented problems is returned in $N 
 */
void LinePickingNumberOfProblems(int *N) 

{
    *N = NUMBER_OF_PROBLEMS;
}


/**
 * Given the unction to expose the number of currently implemented problems.
 * @param $N Pointer to an integer to store the number of currently 
 * implemented problems. 
 * @return The number of currently implemented problems is returned in $N 
 */
void LinePickingProblemLookup(int *problem, char **name, char **description) 
{
    if (*problem < 0 || *problem >= NUMBER_OF_PROBLEMS) 
    {
        *name = "Unsupported problem!";
        *description = 
            "The entered problem number does not correspond to anything.";
        return;
    }

    *name = *LinePickingFields[*problem].name;
    *description = *LinePickingFields[*problem].description;
}


/* write out the list of problems */
void LinePickingPrintAllProblems(void)

{
    int i;
    
    for (i = 0; i < NUMBER_OF_PROBLEMS; i++)
    {
        PRINT_STDOUT(" problem[%d] = %s\n", i, *LinePickingFields[i].name);
    }
}


/* return the list of problems:
 assumes memory is allocated for the array of pointers to strings */

void LinePickingAllProblems(char **names, char **descriptions)
{
    int i;
    
    for (i = 0; i < NUMBER_OF_PROBLEMS; i++)
    {
        names[i] = *LinePickingFields[i].name;
        descriptions[i] = *LinePickingFields[i].description;
    }
}

/** 
 *
 * check that a problem and a set of parameters are valid
 *
 * problem = type of region (see LinePickingProblemLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported problem
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, problem and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 * 
 *
 */
void LinePickingCheckParameters(int *problem, double* parameters, 
                                int *Npar, int *result, char **error_str)

{
    int i;
    
    *result = 0;
    
    /* longest error string is 255 characters */
    *error_str  = (char *) malloc((size_t) sizeof(char)*256); 
    
    /* check the problem is supported */
    if (*problem < 0 || *problem >= NUMBER_OF_PROBLEMS) 
    {
        *result=1;
        sprintf(*error_str, 
                "LinePickingCheckParameters: the problem %d is unsupported.", 
                *problem);
        return;
    }
    
    /* check that there are the right number of parameters */
    if (*Npar !=  *LinePickingFields[*problem].Npar) 
    {
        *result=3;
        sprintf(*error_str, 
                "LinePickingCheckParameters:"
                " problem %d requires %d parameters (%d were input).", 
                *problem, *LinePickingFields[*problem].Npar, *Npar);
        return;
    }
    
    /* no non-positive parameters are allowed for any distributions */
    for (i=0;i<*Npar;i++) 
    {
    	if (parameters[i] <= 0) 
        {
            *result=2;
            sprintf(*error_str, "LinePickingCheckParameters:"
                    " all parameters must be >0, but parameter[%d]=%lf", 
                    i, parameters[i]);
            return;
        }
    }
    
    /* do region specific parameter checking */
    (*LinePickingFields[*problem].CHECK_PAR)(parameters, result, *error_str);
}

/** 
 * compute support of distance density g(t) (at points t) between 
 * two points in a region.
 *
 * t = [t_min, t_max]    : assumes 2 spaces are allocated!!!!!
 * problem = type of region (see LinePickingProblemLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported problem
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, problem and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 *
 *
 */
void LinePickingSupport(double *t, int *problem, 
                        double* parameters, int *Npar, int *result, 
                        char **error_str) 

{
    
    /* first check input parameters */
    LinePickingCheckParameters(problem, parameters, Npar, result, error_str);
    
    if (*result != 0) /* something was wrong with parameters */
        return;
    
    /* compute the lower and upper end of the support */
    (*LinePickingFields[*problem].SUPPORT)(t, parameters);
}

/** 
 * compute distance density g(t) (at points t) between two points in a region.
 *
 * t = array of points at which to calculate density 
 * g = array to store output 
 * problem = type of region (see LinePickingProblemLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported problem
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, problem and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 *
 *
 */
void LinePickingPDF(double *t, double *g, int *N, int *problem, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 

{
    int i;
    double support[2];
    
    /* calculate the support and check parameters are valid */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);

    if (*result != 0) /* something was wrong with the parameters */
        return;    

    /* calculate the distribution */
    for (i=0; i<*N; i++) 
    {
        if (t[i] < support[0] || t[i] > support[1]) 
            g[i] = 0;
        else 
            g[i] = (*LinePickingFields[*problem].PDF)(t[i], parameters);
    }
}

/** 
 * compute distance distribution function \int_0^x g(t) dt (at points t) 
 * between two points in a region.
 *
 * t = array of points at which to calculate density 
 * g = array to store output 
 * problem = type of region (see LinePickingProblemLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported problem
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, problem and Npar are all passed in by reference so R can cope, 
 * and similarly,the function must return void, so we return the exit code 
 * in the last argument.
 *
 */
void LinePickingCDF(double *t, double *g, int *N, int *problem, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 

{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);
    
    if (*result != 0)
    /* something was wrong with parameters */
        return;
    
    /* calculate the distribution */
    for (i=0; i<*N; i++) 
    {
        if (t[i] <= support[0]) 
            g[i] = 0.0;
        else 
        {
            if (t[i] >= support[1]) 
                g[i] = 1.0;
            else 
                g[i] = (*LinePickingFields[*problem].CDF)(t[i], parameters);
        }
    }
}


void LinePickingMean(double *mean, int *problem, 
                     double* parameters, int *Npar, int *result, 
                     char **error_str) 

{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid
     */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);
    if (*result != 0) 
    /* something was wrong with parameters */
        return; 
    
    /* calculate the mean */
    *mean = (*LinePickingFields[*problem].MEAN)(parameters);

    return;
}

/** 
 * compute variance between two points in a region.
 *
 * t = array of points at which to calculate density 
 * var = var line length
 * problem = type of region (see LinePickingProblemLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported problem
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that problem and Npar are all passed in by reference so R can cope, 
 * and similarly,the function must return void, so we return the exit code 
 * in the last argument. 
 *
 */

void LinePickingVar(double *var, int *problem, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 
{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid
     */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);
    if (*result != 0) /* something was wrong with parameters */
        return;
    
    /* calculate the variance */
    *var = (*LinePickingFields[*problem].VAR)(parameters);
    
    return;
}


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
    if (problem < 0 || problem >= NUMBER_OF_PROBLEMS) 
    {
        sprintf(buffer, 
                "\n%s entry point: "
                "the problem %d is unsupported.", 
                entry_str, problem);
        
        mexErrMsgTxt(buffer);  
    }
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    
    double *t; /* points at which to calculate the distribution */
    double *g; /* value of the distribution at the points t */
    int N, M;    /* number of points */
    int Npar;    /* number of parameters */
    int i;					
    int problem;    /* the type of region on which to calculate the distribution */
    double *parameters; /*  input parameter vector  
                         note that meaning of parameters depends on the problem */
    int entry;
    
    int result;
    char *error_str;
    
    double stat;

    int ndim = 1; /* useful for creating 1D arrays */
    const mwSize dims[1] = {NUMBER_OF_PROBLEMS}; /* useful for creating arrays */
    char *names[NUMBER_OF_PROBLEMS];       /* used to output a list of names of the problems */
    char *descriptions[NUMBER_OF_PROBLEMS]; /* used to output a list of descriptions of the problems */
    
    if (nrhs < 1)
        mexErrMsgTxt("LinePicking needs at least one input parameter.");
        
    
    /* the first parameter is an integer 
     * indicating which function should be called 
     * i.e., which entry point to use
     */
    
    entry = (int)mxGetScalar(prhs[0]);
    
    switch (entry) {
        case 0: /* LinePickingPDF */
            /* TODO the previous handling of default values 
             * to be implemented in LinePickingPDF.m
             */
             
            CheckNumberInputArg(nrhs, 4, "LinePickingPDF");
            CheckNumberOutputArg(nlhs, 1, "LinePickingPDF");
            
                   
            N = (int) mxGetN(prhs[1]); 
            M = (int) mxGetM(prhs[1]); 
            if (N<1 || M>1) 
                mexErrMsgTxt("LinePickingPDF entry point: "
                             "t should be an Nx1 matrix.");
            
            t = mxGetPr(prhs[1]);
            
            problem = (int)mxGetScalar(prhs[2]);
            CheckProblem(problem, "LinePickingCDF");
            
            Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
            parameters = mxGetPr(prhs[3]);
            
            plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
            g = mxGetPr(plhs[0]);
                
            LinePickingPDF(t, g, &N, &problem, parameters, 
                           &Npar, &result, &error_str);

            break;
            
        case 1: /* LinePickingCDF */
            
            CheckNumberInputArg(nrhs, 4, "LinePickingCDF");
            CheckNumberOutputArg(nlhs, 1, "LinePickingCDF");
            
            
            N = (int) mxGetN(prhs[1]); 
            M = (int) mxGetM(prhs[1]); 
            if (N<1 || M>1) 
                mexErrMsgTxt("LinePickingCDF entry point: "
                             "t should be an Nx1 matrix.");
            
            t = mxGetPr(prhs[1]);
            
            problem = (int)mxGetScalar(prhs[2]);
            CheckProblem(problem, "LinePickingCDF");
            
            Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
            parameters = mxGetPr(prhs[3]);
            
            plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
            g = mxGetPr(plhs[0]);
            
            LinePickingCDF(t, g, &N, &problem, parameters, 
                           &Npar, &result, &error_str);
            
            break;
             
        case 2: /* LinePickingMean */
            CheckNumberInputArg(nrhs, 3, "LinePickingMean");
            CheckNumberOutputArg(nlhs, 1, "LinePickingMean");
            
            /* three parameters the second is the problem */
            problem = (int)mxGetScalar(prhs[1]);
            
            CheckProblem(problem, "LinePickingMean");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);;
        
            LinePickingMean(g, &problem, parameters, &Npar, &result, 
                            &error_str); 
            
            break;
            
        case 3: /* LinePickingVar */
            CheckNumberInputArg(nrhs, 3, "LinePickingVar");
            CheckNumberOutputArg(nlhs, 1, "LinePickingVar");
            /* three parameters the second is the problem */
            problem = (int)mxGetScalar(prhs[1]);
            
            CheckProblem(problem, "LinePickingVar");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);;
            
            LinePickingVar(g, &problem, parameters, &Npar, &result, 
                            &error_str);
            break;
            
        case 4: /* LinePickingSupport */
            CheckNumberInputArg(nrhs, 3, "LinePickingSupport");
            CheckNumberOutputArg(nlhs, 1, "LinePickingSupport");
            
            /* three parameters the second is the problem */
            problem = (int)mxGetScalar(prhs[1]);
            
            CheckProblem(problem, "LinePickingSupport");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
            g = mxGetPr(plhs[0]);
            
            LinePickingSupport(g, &problem, parameters, &Npar, &result, 
                           &error_str);
            
            break;
            
        case 5: /* LinePickingProblemLookup */
            
            CheckNumberInputArg(nrhs, 2, "LinePickingProblemLookup");
            CheckNumberOutputArg(nlhs, 2, "LinePickingProblemLookup");
               
            /* two parameters the second is the problem */
            problem = (int)mxGetScalar(prhs[1]);
            
            CheckProblem(problem, "LinePickingProblemLookup");
            
            /* success */ 
            {
                char *name;
                char *description;
                
                LinePickingProblemLookup(&problem, &name, &description);
                
                plhs[0] = mxCreateString(name);
                plhs[1] = mxCreateString(description);
            }
            return;
            
        case 6: /* LinePickingPrintAllProblems */
            CheckNumberInputArg(nrhs, 1, "LinePickingPrintAllProblems");
            CheckNumberOutputArg(nlhs, 0, "LinePickingPrintAllProblems");
            LinePickingPrintAllProblems();
                       
            return;
            
        case 7: /*  LinePickingCheckParameters */
            CheckNumberInputArg(nrhs, 3, "LinePickingCheckParameters");
            CheckNumberOutputArg(nlhs, 2, "LinePickingCheckParameters");
            
            /* three parameters the second is the problem */
            problem = (int)mxGetScalar(prhs[1]);
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            
            LinePickingCheckParameters(&problem, parameters, &Npar, &result, 
                           &error_str);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);
            g[0] = result;
            plhs[1] = mxCreateString(error_str);
            
            /* reset it so we can carry on */
            result = 0;
            break;

        case 8: /* LinePickingAllProblems */

            CheckNumberInputArg(nrhs, 1, "LinePickingAllProblems");
            CheckNumberOutputArg(nlhs, 2, "LinePickingAllProblems");
            plhs[0] = mxCreateCellArray(1, dims);
            plhs[1] = mxCreateCellArray(1, dims);

            LinePickingAllProblems(names, descriptions);
            for (i=0; i < NUMBER_OF_PROBLEMS; i++)
            {
                mxSetCell(plhs[0], i, mxCreateString(names[i]));
                mxSetCell(plhs[1], i, mxCreateString(descriptions[i]));
            }

            return;
            
       case 9: /* LinePickingNumberOfProblems */

            CheckNumberInputArg(nrhs, 1, " LinePickingNumberOfProblems");
            CheckNumberOutputArg(nlhs, 1, " LinePickingNumberOfProblems");
	    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	    g = mxGetPr(plhs[0]);
            g[0] = NUMBER_OF_PROBLEMS;

	    return;

        default:
	    mexErrMsgTxt("LinePicking unknown entry point requested.");
    }
    
    if (result != 0) 
        mexErrMsgTxt(error_str);
    
}
#endif /* _MEX */


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */

static void 
usage_LinePicking()
{
    fprintf(stderr, "Usage: LinePicking -f input_file -m problem -p parameter[0]"
            " -q parameter[1] -s parameter[2] \n");
    fprintf(stderr, "           input_file contains a list of points t.\n");
    exit(1);
}

static void 
set_pars_LinePicking(int argc, char *argv[], 
                     char **file, int *problem, 
                     double *parameters, int *Npar)
{
    char c;
    extern char    *optarg;
    extern int      optind;
    
    /* defaults */
    *problem = 0;
    /* longest allowed file name is 255 characters */
    *file = (char *) malloc((size_t) sizeof(char)*256);
    parameters[0] = 1.0; 
    parameters[1] = 1.0;
    parameters[2] = 1.0; 
    
    while ((c=getopt(argc,argv,"f:m:p:q:s:z")) != EOF)
        switch ((char)c) 
    { 
        case 'f': 
            if (sscanf(optarg,"%s",*file) != 1) usage_LinePicking(); 
            break; 
        case 'm':  
            if (sscanf(optarg,"%d",problem) != 1) usage_LinePicking(); 
            break; 
        case 'p': 
            if (sscanf(optarg,"%lf",&(parameters[0])) != 1) usage_LinePicking(); 
            break; 
        case 'q': 
            if (sscanf(optarg,"%lf",&(parameters[1])) != 1) usage_LinePicking(); 
            break;  
        case 's': 
            if (sscanf(optarg,"%lf",&(parameters[2])) != 1) usage_LinePicking(); 
            break;  
        case 'h':;
        default: 
            usage_LinePicking(); 
    }
    *Npar = *LinePickingFields[*problem].Npar;
}

int main(int argc, char *argv[])
{
    int i=0;
    char *readbuf;
    double epsilon;
    int problem;
    double parameters[3];
    char *version = "version 1.0";
    char *file;
    FILE *fp;    
    double t, g, G, mean, var;
    int N=1;
    int result, Npar;
    char *error_str;
    char *Problems_name;
    char *Problems_description;
    
    /*print out program name and version*/
    fprintf(stderr,"%% %s: %s \n", *argv, version);
    
    /* read in programs options  */
    set_pars_LinePicking(argc, argv, 
                         &file, &problem, parameters, &Npar);
    fprintf(stderr,"%%   file=%s, problem=%d, Npar=%d,", file, problem, Npar);
    for (i=0;i<Npar;i++) 
    {
        fprintf(stderr, " p[%d]=%.3f", i, parameters[i]);
    }
    fprintf(stderr, "\n");
    
    /* check the problem and parameters are valid */
    LinePickingCheckParameters(&problem, parameters, &Npar, &result, &error_str);
    if (result != 0) 
    {
        fprintf(stderr, "LinePicking: %s\n", error_str);
        exit(1);
    }
    /* get the problem's name and description */
    LinePickingProblemLookup(&problem, &Problems_name, &Problems_description);
    fprintf(stderr, 
            "%%  problem=%d, %s (%s)\n", problem, Problems_name, Problems_description);
    
    /* calculate the mean and variance */
    LinePickingMean(&mean, &problem, parameters, &Npar, &result, &error_str);
    LinePickingVar(&var, &problem, parameters, &Npar, &result, &error_str);
    if (result == 0) 
    {
        fprintf(stderr, 
                "%%  mean line length = %.12lf and var = %.12lf\n", mean, var);
    } 
    else 
    {
        fprintf(stderr, "LinePicking: error, unexpected error.\n");
        exit(result);
    }
    
    /* read in the input file, and output the results */
    fp = fopen(file, "r");  /* open the file for reading */
    if (fp == NULL) 
    {
        fprintf(stderr, "LinePicking: invalid file!\n");
        exit(1);
    }
    
    /* test that we read in exactly one double */  
    while(fscanf(fp, "%lf", &t) == 1) 
    {
        LinePickingPDF(&t, &g, &N, &problem, 
                       parameters, &Npar, &result, &error_str);
        LinePickingCDF(&t, &G, &N, &problem, 
                       parameters, &Npar, &result, &error_str);
        if (result == 0) 
        {
            fprintf(stdout, "%lf, %lf, %lf\n", t, g, G);
        } 
        else 
        {
            fprintf(stderr, "LinePicking: error, unexpected error.\n");
            exit(result);
        }
    }
    fclose(fp);
    
    return(0);
}

#endif /* _STANDALONE */

