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
 * Compute the distance distribution between two point in a region, 
 * often called the "line picking problem".
 *
 * MEX Call as:   [g] = LinePicking( ??? )
 *                   remember: parameter(1) (in matlab) == parameter[0] (in C)
 *
 * C Call as:     result = LinePicking( ??? );
 *
 * Unix command line call as:  
 *  LinePicking -f input_file -m mode -p parameter0 -q parameter1 -s parameter2
 *    
 * Various regions are supported:
 *    0: square, with side length parameters[0]
 *    1: disk, with radius parameters[0]
 *    2: hyper-ball, dimension parameters[0], radius parameters[1]
 *    3: rectangle, side lengths parameters[0], parameters[1]
 *    4: line, length parameters[0]
 *    5: cube, side length parameters[0]
 * with LinePickingModeLookup providing the map from number to name.
 * 
 */

/** 
 * @mainpage LinePicking
 * @version 0.9
 * @brief Numerical code for geometric probability problems, 
 * in particular PDFs, CDFs, means and variances for the "line picking" problem.
 * 
 * @par Description  
 * The problem is a standard problem in stochastic
 * geometry, where we pick lines at random from some region. The typical
 * questions one asks are what will then mean line length be? What will
 * the Probability Density Function (PDF) be? This software implements the 
 * current list of known PDFs, CDFs, means and variances for such problems and
 * extends these with solutions to previously unsolved problems.
 *
 * @author Eric Parsonage <eric.parsonage@adelaide.edu.au>
 * @author Matthew Roughan <matthew.roughan@adelaide.edu.au>
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


void LinePickingModeLookup(int *mode, char **name, char **description) 
/* give details of a mode */
{
    if (*mode<0 || *mode>=NUMBER_OF_MODES) {
	*name = "Unsupported mode!";
	*description = "The entered mode number does not correspond to anything.";
	return;
    }

    *name = *LinePickingFields[*mode].name;
    *description = *LinePickingFields[*mode].description;
    
    return;
}

void LinePickingAllModes(void)
/* write out the list of modes */
{
    int i;
    
    for (i=0; i < NUMBER_OF_MODES; i++)
    {
#ifdef _MEX
        mexPrintf(" mode[%d] = %s\n", i, *LinePickingFields[i].name);
#else /* MEX */
        fprintf(stdout, " mode[%d] = %s\n", i, *LinePickingFields[i].name);
#endif
    }
    
    return;
}


void LinePickingCheckParameters(int *mode, double* parameters, 
                                int *Npar, int *result, char **error_str)
/* check that a mode and a set of parameters are valid
 *
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    int i;
    
    *result = 0;
    
    /* longest error string is 255 characters */
    *error_str  = (char *) malloc((size_t) sizeof(char)*256); 
    
    /* check the mode is supported */
    if (*mode<0 || *mode >= NUMBER_OF_MODES) 
    {
        *result=1;
        sprintf(*error_str, 
                "LinePickingCheckParameters: the mode %d is unsupported.", 
                *mode);
        return;
    }
    
    /* check that there are the right number of parameters */
    if (*Npar !=  *LinePickingFields[*mode].Npar) 
    {
        *result=3;
        sprintf(*error_str, 
                "LinePickingCheckParameters:"
                " mode %d requires %d parameters (%d were input).", 
                *mode, *LinePickingFields[*mode].Npar, *Npar);
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
    (*LinePickingFields[*mode].CHECK_PAR)(parameters, result, *error_str);
    return;
}


void LinePickingSupport(double *t, int *mode, 
                        double* parameters, int *Npar, int *result, 
                        char **error_str) 
/* compute support of distance density g(t) (at points t) between 
 * two points in a region.
 *
 * t = [t_min, t_max]    : assumes 2 spaces are allocated!!!!!
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    
    /* first check input parameters */
    LinePickingCheckParameters(mode, parameters, Npar, result, error_str);
    
    if (*result != 0) /* something was wrong with parameters */
        return;
    
    /* compute the lower and upper end of the support */
    (*LinePickingFields[*mode].SUPPORT)(t, parameters);
    
    return; 
}


void LinePickingPDF(double *t, double *g, int *N, int *mode, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 
/* compute distance density g(t) (at points t) between two points in a region.
 *
 * t = array of points at which to calculate density 
 * g = array to store output 
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, 
 * and similarly, the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    int i;
    double support[2];
    
    /* calculate the support and check parameters are valid */
    LinePickingSupport(support, mode, parameters, Npar, result, error_str);

    if (*result != 0) /* something was wrong with the parameters */
        return;    

    /* calculate the distribution */
    for (i=0; i<*N; i++) 
    {
        if (t[i] < support[0] || t[i] > support[1]) 
            g[i] = 0;
        else 
            g[i] = (*LinePickingFields[*mode].PDF)(t[i], parameters);
    }
    
    return;
}


void LinePickingCDF(double *t, double *g, int *N, int *mode, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 
/* compute distance distribution function \int_0^x g(t) dt (at points t) 
 * between two points in a region.
 *
 * t = array of points at which to calculate density 
 * g = array to store output 
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that N, mode and Npar are all passed in by reference so R can cope, 
 * and similarly,the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid */
    LinePickingSupport(support, mode, parameters, Npar, result, error_str);
    
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
                g[i] = (*LinePickingFields[*mode].CDF)(t[i], parameters);
        }
    }
    
    return;
}


void LinePickingMean(double *mean, int *mode, 
                     double* parameters, int *Npar, int *result, 
                     char **error_str) 
/* compute mean  between two points in a region.
 *
 * t = array of points at which to calculate density 
 * mean = mean line length
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that mode and Npar are all passed in by reference so R can cope, 
 * and similarly,the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid
     */
    LinePickingSupport(support, mode, parameters, Npar, result, error_str);
    if (*result != 0) 
    /* something was wrong with parameters */
        return; 
    
    /* calculate the mean */
    *mean = (*LinePickingFields[*mode].MEAN)(parameters);

    return;
}


void LinePickingVar(double *var, int *mode, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 
/* compute variance between two points in a region.
 *
 * t = array of points at which to calculate density 
 * var = var line length
 * mode = type of region (see LinePickingModeLookup)
 * Npar = number of parameters
 * result = exit code
 *    0: parameters are valid
 *    1: unsupported mode
 *    2: parameters out of range.
 *    3: not enough parameters were entered.
 *    4: other error.
 * error_str: a message explaining the error
 *
 * Note that mode and Npar are all passed in by reference so R can cope, 
 * and similarly,the function must return void, so we return the exit code 
 * in the last argument.
 */
{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid
     */
    LinePickingSupport(support, mode, parameters, Npar, result, error_str);
    if (*result != 0) /* something was wrong with parameters */
        return;
    
    /* calculate the variance */
    *var = (*LinePickingFields[*mode].VAR)(parameters);
    
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
void CheckMode(int mode, char* entry_str)
{
    char buffer[256];
    if (mode < 0 || mode >= NUMBER_OF_MODES) 
    {
        sprintf(buffer, 
                "\n%s entry point: "
                "the mode %d is unsupported.", 
                entry_str, mode);
        
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
    int mode;    /* the type of region on which to calculate the distribution */
    double *parameters; /*  input parameter vector  
                         note that meaning of parameters depends on the mode */
    int entry;
    
    int result;
    char *error_str;
    
    double stat;

    
    
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
            
            mode = (int)mxGetScalar(prhs[2]);
            CheckMode(mode, "LinePickingCDF");
            
            Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
            parameters = mxGetPr(prhs[3]);
            
            plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
            g = mxGetPr(plhs[0]);
                
            LinePickingPDF(t, g, &N, &mode, parameters, 
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
            
            mode = (int)mxGetScalar(prhs[2]);
            CheckMode(mode, "LinePickingCDF");
            
            Npar = (int) mxGetN(prhs[3]) * mxGetM(prhs[3]);
            parameters = mxGetPr(prhs[3]);
            
            plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
            g = mxGetPr(plhs[0]);
            
            LinePickingCDF(t, g, &N, &mode, parameters, 
                           &Npar, &result, &error_str);
            
            break;
             
        case 2: /* LinePickingMean */
            CheckNumberInputArg(nrhs, 3, "LinePickingMean");
            CheckNumberOutputArg(nlhs, 1, "LinePickingMean");
            
            /* three parameters the second is the mode */
            mode = (int)mxGetScalar(prhs[1]);
            
            CheckMode(mode, "LinePickingMean");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);;
        
            LinePickingMean(g, &mode, parameters, &Npar, &result, 
                            &error_str); 
            
            break;
            
        case 3: /* LinePickingVar */
            CheckNumberInputArg(nrhs, 3, "LinePickingVar");
            CheckNumberOutputArg(nlhs, 1, "LinePickingVar");
            /* three parameters the second is the mode */
            mode = (int)mxGetScalar(prhs[1]);
            
            CheckMode(mode, "LinePickingVar");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);;
            
            LinePickingVar(g, &mode, parameters, &Npar, &result, 
                            &error_str);
            break;
            
        case 4: /* LinePickingSupport */
            CheckNumberInputArg(nrhs, 3, "LinePickingSupport");
            CheckNumberOutputArg(nlhs, 1, "LinePickingSupport");
            
            /* three parameters the second is the mode */
            mode = (int)mxGetScalar(prhs[1]);
            
            CheckMode(mode, "LinePickingSupport");
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
            g = mxGetPr(plhs[0]);
            
            LinePickingSupport(g, &mode, parameters, &Npar, &result, 
                           &error_str);
            
            break;
            
        case 5: /* LinePickingModeLookup */
            
            CheckNumberInputArg(nrhs, 2, "LinePickingModeLookup");
            CheckNumberOutputArg(nlhs, 2, "LinePickingModeLookup");
               
            /* two parameters the second is the mode */
            mode = (int)mxGetScalar(prhs[1]);
            
            CheckMode(mode, "LinePickingModeLookup");
            
            /* success */ 
            {
                char *name;
                char *description;
                
                LinePickingModeLookup(&mode, &name, &description);
                
                plhs[0] = mxCreateString(name);
                plhs[1] = mxCreateString(description);
            }
            return;
            
        case 6: /* LinePickingAllModes */
            CheckNumberInputArg(nrhs, 1, "LinePickingAllModes");
            CheckNumberOutputArg(nlhs, 0, "LinePickingAllModes");
            LinePickingAllModes();
                       
            return;
            
        case 7: /*  LinePickingCheckParameters */
            CheckNumberInputArg(nrhs, 3, "LinePickingCheckParameters");
            CheckNumberOutputArg(nlhs, 2, "LinePickingCheckParameters");
            
            /* three parameters the second is the mode */
            mode = (int)mxGetScalar(prhs[1]);
            
            /* three parameters the third are the region parameters */
            Npar = (int) mxGetN(prhs[2]) * mxGetM(prhs[2]);
            parameters = mxGetPr(prhs[2]);
            
            
            LinePickingCheckParameters(&mode, parameters, &Npar, &result, 
                           &error_str);
            
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            g = mxGetPr(plhs[0]);
            g[0] = result;
            plhs[1] = mxCreateString(error_str);
            
            /* reset it so we can carry on */
            result = 0;
            break;
            
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
    fprintf(stderr, "Usage: LinePicking -f input_file -m mode -p parameter[0]"
            " -q parameter[1] -s parameter[2] \n");
    fprintf(stderr, "           input_file contains a list of points t.\n");
    exit(1);
}

static void 
set_pars_LinePicking(int argc, char *argv[], 
                     char **file, int *mode, 
                     double *parameters, int *Npar)
{
    char c;
    extern char    *optarg;
    extern int      optind;
    
    /* defaults */
    *mode = 0;
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
            if (sscanf(optarg,"%d",mode) != 1) usage_LinePicking(); 
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
    *Npar = *LinePickingFields[*mode].Npar;
}

int main(int argc, char *argv[])
{
    int i=0;
    char *readbuf;
    double epsilon;
    int mode;
    double parameters[3];
    char *version = "version 1.0";
    char *file;
    FILE *fp;    
    double t, g, G, mean, var;
    int N=1;
    int result, Npar;
    char *error_str;
    char *mode_name;
    char *mode_description;
    
    /*print out program name and version*/
    fprintf(stderr,"%% %s: %s \n", *argv, version);
    
    /* read in programs options  */
    set_pars_LinePicking(argc, argv, 
                         &file, &mode, parameters, &Npar);
    fprintf(stderr,"%%   file=%s, mode=%d, Npar=%d,", file, mode, Npar);
    for (i=0;i<Npar;i++) 
    {
        fprintf(stderr, " p[%d]=%.3f", i, parameters[i]);
    }
    fprintf(stderr, "\n");
    
    /* check the mode and parameters are valid */
    LinePickingCheckParameters(&mode, parameters, &Npar, &result, &error_str);
    if (result != 0) 
    {
        fprintf(stderr, "LinePicking: %s\n", error_str);
        exit(1);
    }
    /* get the mode's name and description */
    LinePickingModeLookup(&mode, &mode_name, &mode_description);
    fprintf(stderr, 
            "%%  mode=%d, %s (%s)\n", mode, mode_name, mode_description);
    
    /* calculate the mean and variance */
    LinePickingMean(&mean, &mode, parameters, &Npar, &result, &error_str);
    LinePickingVar(&var, &mode, parameters, &Npar, &result, &error_str);
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
        LinePickingPDF(&t, &g, &N, &mode, 
                       parameters, &Npar, &result, &error_str);
        LinePickingCDF(&t, &G, &N, &mode, 
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


