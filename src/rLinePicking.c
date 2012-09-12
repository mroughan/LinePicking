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


#ifndef _NOTR
#include <R.h> /* only include this if we are compiling for R */
#include <Rinternals.h>
#endif


#ifndef _NOTR
/*
 * R parts
 *
 */

/**
 * This function is called via the R .Call mechanism. It returns a
 * list of lists detailing the currently implemented problem set.
 * @return A list of lists in an R s-expression detailing the currently 
 * implemented problem set.
 */
SEXP rLinePickingAllProblems(void)
{
  
  const char *names[] = {"problem", "name", "description", 
                         "npar", "parameters" };
  int problem;
  int Npar;
  int parameter;
  int i;
  int number_of_problems; 
    
  LinePickingNumberOfProblems(&number_of_problems);
  
  SEXP list_names = PROTECT(allocVector(STRSXP,elements(names)));
  for(i = 0; i < elements(names); i++)
    SET_STRING_ELT(list_names,i,mkChar(names[i]));
  
  /*  This is the vector we will return to R it will be a vector of vectors*/ 
  SEXP result = PROTECT(allocVector(VECSXP, number_of_problems));
  
  for (problem = 0;  problem  < number_of_problems; problem++)
  {
    /* this vector contains all the data for one problem */
    Npar = LinePickingFields[problem].DATA->Npar;
    SEXP problemData = PROTECT(allocVector(VECSXP, elements(names)));
    /* this vector contains the parameters */
    SEXP defaultParameters = PROTECT(allocVector(VECSXP, Npar));
    
    
    SET_VECTOR_ELT(result, problem, problemData); 
    
    SEXP name = mkString(LinePickingFields[problem].DATA->name);
    SEXP desc = mkString(LinePickingFields[problem].DATA->description);
    
    
    SET_VECTOR_ELT(problemData, 0, ScalarInteger(problem));
    SET_VECTOR_ELT(problemData, 1, name);
    SET_VECTOR_ELT(problemData, 2, desc);
    SET_VECTOR_ELT(problemData, 3, ScalarInteger(Npar));
    SET_VECTOR_ELT(problemData, 4, defaultParameters);
    
    for(parameter = 0; parameter < Npar; parameter++)
    {
      SET_VECTOR_ELT(defaultParameters, parameter, 
                     ScalarReal(LinePickingFields[problem].
                                DATA->DefaultParameters[parameter]));    
    }
    
    
    
    setAttrib(problemData, R_NamesSymbol, list_names); 
  }
  
  UNPROTECT(2 + 2 * NUMBER_OF_PROBLEMS);
  return result; 
}

/**
 * This function is called via the R .Call mechanism. It checks  
 * that a set of parameters describing the space of a line picking problem
 * are valid input for a given problem number.
 *
 * @param $sexpProblem an integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters a vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return exit code. 
 */
SEXP rLinePickingCheckParameters(SEXP sexpProblem, SEXP sexpParameters)            
{    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    int Npar = length(sexpParameters);
    
    char *error_str;
    int  result;
    
    LinePickingCheckParameters(&problem, parameters, 
                               &Npar, &result, &error_str);
    
    /* if we got some error report it and stop */
    if (result != 0) warning(error_str);
    return ScalarInteger(result);                        
}



/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a vector of two reals that give the interval 
 * of the support for the PDF and CDF of a line picking problem 
 * for a given set of parameters.
 *
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return An R s-expression containing a 1 x 2 vector of reals containing the 
 * minimum and maximum values of the support of the PDF and CDF for the 
 * requested problem with the given parameters.
 */
SEXP rLinePickingSupport(SEXP sexpProblem, SEXP sexpParameters)            
{    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    int Npar = length(sexpParameters);
    
    char *error_str;
    int  result;
    
    /* allocate some memory in the R way for the support */
    SEXP sexpt = PROTECT(allocVector(REALSXP, 2));
    
    LinePickingSupport(REAL(sexpt), &problem, parameters, 
                               &Npar, &result, &error_str);
    
    UNPROTECT(1);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return sexpt;                        
}


/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a vector of reals which are the result 
 * of evaluating the PDF of a given line picking problem at each of
 * the values in the supplied input values.
 *
 * @param $sexpt A vector of reals contained in an R s-expression
 * representing the points to evaluate the PDF at. 
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return An R s-expression containing a vector of reals which are the result 
 * of evaluating the PDF of a given line picking problem at each of
 * the values supplied in $sexpt.
 */
SEXP rLinePickingPDF(SEXP sexpt, SEXP sexpProblem, SEXP sexpParameters)            
{    
	double *t = REAL(sexpt);
    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    
    int Npar = length(sexpParameters);
    int N = length(sexpt);
    char *error_str;
    int  result;
    
    
    /* allocate some memory in the R way for the distances */
    SEXP sexpg = PROTECT(allocVector(REALSXP, N));
    
    /* call the function */
    LinePickingPDF(REAL(sexpt), REAL(sexpg), &N, &problem, parameters,
                   &Npar, &result, &error_str);
    
    UNPROTECT(1);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return sexpg;                        
}


/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a vector of reals which are the result 
 * of evaluating the CDF of a given line picking problem at each of
 * the values in the supplied input values.
 *
 * @param $sexpt A vector of reals contained in an R s-expression
 * representing the points to evaluate the CDF at. 
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return An R s-expression containing a vector of reals which are the result 
 * of evaluating the CDF of a given line picking problem at each of
 * the values supplied in $sexpt.
 */
SEXP rLinePickingCDF(SEXP sexpt, SEXP sexpProblem, SEXP sexpParameters)            
{    
	double *t = REAL(sexpt);
    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    
    int Npar = length(sexpParameters);
    int N = length(sexpt);
    char *error_str;
    int  result;
    
    
    /* allocate some memory in the R way for the distances */
    SEXP sexpg = PROTECT(allocVector(REALSXP, N));
    
    /* call the function */
    LinePickingCDF(REAL(sexpt), REAL(sexpg), &N, &problem, parameters,
                   &Npar, &result, &error_str);
    
    UNPROTECT(1);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return sexpg;                        
}


/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a real which is the mean length of lines  
 * in a given line picking problem.
 * 
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return An R s-expression containing a real which is the mean length of 
 * lines in a given line picking problem.
 */
SEXP rLinePickingMean(SEXP sexpProblem, SEXP sexpParameters)            
{    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    int Npar = length(sexpParameters);
    double mean;
    
    char *error_str;
    int  result;
    
    /* call the function */
    LinePickingMean(&mean, &problem, parameters, &Npar, &result, &error_str);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return ScalarReal(mean);                        
}

/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a real which is the variance in the
 * length of lines in a given line picking problem.
 * 
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @return An R s-expression containing a real which is the variance in the 
 * length of lines in a given line picking problem.
 */
SEXP rLinePickingVar(SEXP sexpProblem, SEXP sexpParameters)            
{    
    
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    int Npar = length(sexpParameters);
    double var;
    
    char *error_str;
    int  result;
    
    /* call the function */
    LinePickingVar(&var, &problem, parameters, &Npar, &result, &error_str);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return ScalarReal(var);                        
}

/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a vector of reals representing a set of 
 * randomly selected points from a given line picking problem.
 *
 * 
 * @param $sexpN An integer in an R s-expression giving the number of 
 * points to simulate.
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @param $sexpSeed An integer in an R s-expression giving a seed for the
 * random number generator.
 * @return An R s-expression containing an M x $sexpN vector of reals 
 * representing a set of randomly selected points from the given line picking
 * problem (where M represents the number of dimesnions of the space in which
 * the line picking problem is embedded.
 */
SEXP rLinePickingSimPoints(SEXP sexpNpoints, SEXP sexpProblem, 
                           SEXP sexpParameters, SEXP sexpSeed)            
{    
    
	int Npoints = INTEGER(sexpNpoints)[0];		
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    long int seed = INTEGER(sexpSeed)[0];
    int Npar = length(sexpParameters);
    int i;
    SEXP sexpPoints, dim;
    char *error_str;
    int  result;
    int Ncoords;
    double **Points;
    char *CoordSystem;
    
    
    srand48(seed); /* initialize random number generator */
    
    /* determine the correct number of coordinates */
    LinePickingNcoords(&Ncoords, &CoordSystem, &problem, parameters, 
                       &Npar, &result, &error_str);     
    
    /* something was wrong with parameters */
    if (result != 0) error(error_str);
    
    /* setup the memory needed to store the points */
    sexpPoints = PROTECT(allocVector(REALSXP, Ncoords * Npoints));

    /* the way the points have been setup to prefer the Matlab 
     * way of row major ordering means we are forced to return 
     * Ncoords rows and Npoints colums in R this can be fixed 
     * but requires fixing all the geometry files
     */
     
    dim = PROTECT(allocVector(INTSXP, 2));
    INTEGER(dim)[0] = Ncoords; 
    INTEGER(dim)[1] = Npoints; 
    setAttrib(sexpPoints, R_DimSymbol, dim);
    
    /* 
     * oh why oh why are the functons implemented with the 
     * points indexed in this fashion ? 
     */
    Points = (double **) malloc((size_t) sizeof(double)*(Npoints));
    
    for (i=0;i<Npoints;i++) 
        Points[i] = REAL(sexpPoints) + (i * Ncoords);
    
    LinePickingSimPoints(Points, &Npoints, &Ncoords, &problem, parameters, 
                         &Npar, &result, &error_str);
    free(Points);
    UNPROTECT(2);
    
    if (result != 0) 
        error(error_str);
    else
        return sexpPoints;  
}


/**
 * This function is called via the R .Call mechanism. It returns an 
 * R s-expession containing a vector of reals representing the 
 * lengths of a set of lines randomly selecting from a given line 
 * picking problem.
 *
 * 
 * @param $sexpN An integer in an R s-expression giving the number of 
 * lines to simulate.
 * @param $sexpProblem An integer in an R s-expression referencing one 
 * of the problerms implemented in this software.
 * @param $sexpParameters A vector of reals in an R s-expresssion providing
 * the parameters necessary to describe the space for a given problem.
 * @param $sexpSeed An integer in an R s-expression giving a seed for the
 * random number generator.
 * @return An R s-expression containing a vector of reals representing the 
 * lengths of a set of lines randomly selecting from the given line 
 * picking problem.
*/
SEXP rLinePickingSimDistances(SEXP sexpN, SEXP sexpProblem, 
                              SEXP sexpParameters, SEXP sexpSeed)            
{    
    
	int N = INTEGER(sexpN)[0];		
    int problem = INTEGER(sexpProblem)[0];                          
    double *parameters = REAL(sexpParameters);
    long int seed = INTEGER(sexpSeed)[0];
    int Npar = length(sexpParameters);
    SEXP sexpDistances;
    char *error_str;
    int  result;
    
    srand48(seed); /* initialize random number generator */
    
    /* allocate some memory in the R way for the distances */
    sexpDistances = PROTECT(allocVector(REALSXP, N));
    
    /* call the function */
    LinePickingSimDistances(REAL(sexpDistances), &N, &problem,parameters,
                            &Npar, &result, &error_str);
    UNPROTECT(1);
    
    /* if we got some error report it and stop */
    if (result != 0) error(error_str);
    return sexpDistances;                        
}

#endif

