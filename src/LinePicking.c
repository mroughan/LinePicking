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
#include "beta.h" 

#ifndef _NOTR
#include <R.h> /* only include this if we are compiling for R */
#include <Rinternals.h>
#endif

#ifdef _MEX
#include "mex.h"
#include "matrix.h"
#endif







/**
 * Helper function returns the number of currently implemented problems.
 * @param $N Pointer to an integer to store the number of currently 
 * implemented problems. 
 * @return The number of currently implemented problems is returned in the 
 * location pointed to by $N. 
 */
void LinePickingNumberOfProblems(int *N) 

{
    *N = NUMBER_OF_PROBLEMS;
}


/**
 * Helper function returns the number of parameters a currently implemented 
 * problem uses.
 * @param $problem Represents a problem. 
 * @param $Npar Is the number of parameters problem $problem uses. 
 * @return The number of parameters problem $problem uses is returned in 
 * $Npar. -1 is returned if $problem is not implemented.
 */
void LinePickingProblemNparLookup(int *problem, int *Npar) 
{

	if (*problem < 0 || *problem  >= NUMBER_OF_PROBLEMS)
	{
		*Npar = -1;
		return;
	}

	*Npar = LinePickingFields[*problem].DATA->Npar;
	return;
}


/**
 * Problems are represented as integers. Given such a name, this finds
 * the problem corresponding to that name, if one exists
 * @param $problem Represents a problem. 
 * @param $name Address of a memory location to set to the address of a string
 * containing the name of the problem.
 * @return $problem returns the problem corresponding to the name, 
 * or -1 if none exists.
 */
void LinePickingNameLookup(int *problem, char **name) 
{
    int i;
    *problem = -1;
    
    for (i = 0; i < NUMBER_OF_PROBLEMS; i++)
    {
        if (strcmp(*name, LinePickingFields[i].DATA->name) == 0) 
        {
            *problem = i;
        }
    }
}


/**
 * Problems are represented as integers. Given such an integer this function
 * returns the problem name and description as a string.
 * @param $problem Represents a problem. 
 * @param $name Address of a memory location to set to the address of a string
 * containing the name of the problem.
 * @param $description Address of a memory location to set to the address of a 
 * string containing the description of the problem.
 * @return Strings containing the name and description of the problem are 
 * retuned in the locations pointed to by $name and $description.
 * @todo Implement dynamic memory allocation of string outputs.
 */
void LinePickingProblemLookup(int *problem, char **name, char **description , 
                              int *Npar, double *parameters) 
{
    int i;
    
    if (*problem < 0 || *problem >= NUMBER_OF_PROBLEMS) 
    {
        *name = "Unsupported problem!";
        *description = 
            "The entered problem number does not correspond to anything.";
        return;
    }

    *name = LinePickingFields[*problem].DATA->name;
    *description = LinePickingFields[*problem].DATA->description;
    *Npar = LinePickingFields[*problem].DATA->Npar;
    for (i =0 ;i < *Npar ; i++) 
    {
        parameters[i] = LinePickingFields[*problem].DATA->DefaultParameters[i];
    }
     
}


/**
 * Prints to stdout a list of all implemented problems giving the number of 
 * the problem and its associated name.
 * @todo Do we want to print out the descriptions here?
 */
/* write out the list of problems */
void LinePickingPrintAllProblems(void)

{
    int i;
    
    for (i = 0; i < NUMBER_OF_PROBLEMS; i++)
    {
        PRINT_STDOUT(" problem[%d] = %s\n", i, LinePickingFields[i].DATA->name);
    }
}


/**
 * This function is passed two arrays of uninitialised pointers to strings. 
 * On its return these pointers are initialised. The firat contains pointers
 * to strings containing the names of all the problems implemented and the 
 * second contains pointers to strings containing the descriptions of all the
 * problems implemented.
 * @param $name Pointer to array that this function will fill with pointers to 
 * strings containing the names of all the problems currently implemented.
 * @param $description Pointer to array that this function will fill with 
 * pointers to strings containing the descriptons  of all the problems 
 * currently implemented.
 * @return The two uninitialised arrays passed to the function are initialised 
 * with pointers to strings. 
 * @todo Implement dynamic memory allocation of string outputs and the 
 * array that points to them.
 */
void LinePickingAllProblems(char **names, char **descriptions,
                            int *Npars, double **parameters)
{
    int i;
    
    for (i = 0; i < NUMBER_OF_PROBLEMS; i++)
    {
        names[i] = LinePickingFields[i].DATA->name;
        descriptions[i] = LinePickingFields[i].DATA->description;
        Npars[i] = LinePickingFields[i].DATA->Npar;
        parameters[i] = LinePickingFields[i].DATA->DefaultParameters; 
    }
}



/**
 * Determines if the supplied parameters are valid input for other functions
 * in this library.
 *
 * 
 * @param $problem The number of the problem for which the the 
 * supplied $parameters are checked against. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. 
 * The following values are implemented:
 *      - 0: parameters are valid.
 *      - 1: unsupported problem.
 *      - 2: parameters out of range.
 *      - 3: not enough parameters were entered.
 *      - 4: other error.. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The validity of the supplied parameters as input for other functions 
 * in this library is retuned in $result.
 */
void LinePickingCheckParameters(int *problem, double* parameters, 
                                int *Npar, int *result, char **error_str)

{
    int i;
    
    *result = 0;
    
    /* 
     * longest error string is 255 characters 
     * the memory can be allocated staticaly because  
     * in Matlab we explicitly create a copy of this 
     * string and in R the caller makes a copy.
     */
    *error_str  = global_error_str;
    
    /* 
     * start with an empty string so if there   
     * is no error we get an empty string
     */
    *error_str[0] = '\0';
    
    /* 
     * Previously this caused a memory leak: 
     * *error_str  = (char *) malloc((size_t) sizeof(char)*256); 
     * because we had no way of freeing this memory but as
     * explained above we did not need to allocate it dynamically
     */
    
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
    if (*Npar !=  LinePickingFields[*problem].DATA->Npar) 
    {
        *result=3;
        sprintf(*error_str, 
                "LinePickingCheckParameters:"
                " problem %d requires %d parameters (%d were input).", 
                *problem, LinePickingFields[*problem].DATA->Npar, *Npar);
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
 * Compute the support of the PDF and CDF of the distance between two 
 * random points for a given problem.
 *
 * 
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points 
 * for a given problem.  
 * @param $problem The number of the problem for which the PDF's and CDF's
 * support will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 * @todo allocate memeory for the result dynamically.
 * @bug potential array bounds overrun.
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
 * Implements the PDF of the distance between two random points for the 
 * given problem.
 *
 * 
 * @param $t An array of distances to calculate the density for.
 * @param $g An array in which the calculated densities are returned.
 * @param $N The value pointed to by $N is the number of entries in $T
 * @param $problem The number of the problem for which the PDF 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required calculated densities are returned in $g.
 * @todo The matlab version allocates memory dynamically for the array 
 * of densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
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
    for (i = 0; i < *N; i++) 
    {
        if (t[i] < support[0] || t[i] > support[1]) 
            g[i] = 0;
        else 
            g[i] = (*LinePickingFields[*problem].PDF)(t[i], parameters);
    }
}

/**
 * Implements the CDF of the distance between two random points for the 
 * given problem.
 *
 * 
 * @param $t An array of distances to calculate the cumulative density for.
 * @param $g An array in which the calculated cumulative densities are returned.
 * @param $N The value pointed to by $N is the number of entries in $T
 * @param $problem The number of the problem for which the PDF 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters.
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required calculated cumulative densities are returned in $g.
 * @todo The matlab version allocates memory dynamically for the array 
 * of cumulative densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
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



/**
* Calculates the mean distance between two random points for the 
* given problem.
*
* 
* @param $mean A pointer to the location where the mean will be stored.
* @param $problem The number of the problem for which the mean 
* will be calculated. 
* @param $parameters Pointer to the values required to describe 
* the geometry of the problem.
* @param $Npar The number of parameters that $parameters contains.
* @param $result Pointer so that the result of the evaluation can be returned. 
* A non-zero value indicates there was a problem in the input. A description 
* of the error is returned in $error_str. The integer values returned are 
* described in @ref LinePickingCheckParameters.
* @param $error_str A string describing the result of evaluating the function.
* @return The required calculated mean is returned in $mean.
*/
void LinePickingMean(double *mean, int *problem, 
                     double* parameters, int *Npar, int *result, 
                     char **error_str) 

{
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
 * Calculates the variance of the distances between two random points for the 
 * given problem.
 *
 * 
 * @param $var A pointer to the location where the variance will be stored.
 * @param $problem The number of the problem for which the mean 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters.
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required calculated variance is returned in $var.
 */
void LinePickingVar(double *var, int *problem, 
                    double* parameters, int *Npar, int *result, 
                    char **error_str) 
{
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


/**
 * Return the number of coordinates used to describe a point in some problem.
 *
 * @Ncoords The number of coordinates.
 * @CoordSystem A description of the coordinate system being used.
 * @param $problem The number of the problem for which the PDF 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required points are returned in $g.
 * @todo The matlab version allocates memory dynamically for the array 
 * of densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
 */
void LinePickingNcoords(int *Ncoords, char **CoordSystem, int *problem, 
			double* parameters, int *Npar, int *result, 
			char **error_str)
{
    /* first check input parameters */
    LinePickingCheckParameters(problem, parameters, Npar, result, error_str);
    
    if (*result != 0) /* something was wrong with parameters */
        return;

    /* get the number of coordinates and their description */
    (*LinePickingFields[*problem].NCOORDS)(Ncoords, CoordSystem, parameters);
}


/**
 * Generate a set of points suitable for use in simulating a problem 
 *
 * @param $points An array in which the coordinates of the simulated points 
 * are returned.
 * @param $N The value pointed to by $N is the number of entries there should 
 * be in $points
 * @param $problem The number of the problem for which the PDF 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required points are returned in $g.
 * @todo The matlab version allocates memory dynamically for the array 
 * of densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
 */
void LinePickingSimPoints(double **points, int *Npoints, int *Ncoords, 
			  int *problem, double* parameters, int *Npar,
			  int *result, char **error_str)
{
    /* first check input parameters */
    LinePickingCheckParameters(problem, parameters, Npar, result, error_str);
    
    if (*result != 0) /* something was wrong with parameters */
        return;

    /* generate points */
    (*LinePickingFields[*problem].SIM_POINTS)(points, 
                                              Npoints, Ncoords, parameters);
}

/**
 * Generate a set of distances by simulating a problem
 *
 * @param $distances An array in which the simulated distances are returned.
 * @param $N The value pointed to by $N is the number of entries in $T
 * @param $problem The number of the problem for which the PDF 
 * will be calculated. 
 * @param $parameters Pointer to the values required to describe 
 * the geometry of the problem.
 * @param $Npar The number of parameters that $parameters contains.
 * @param $result Pointer so that the result of the evaluation can be returned. 
 * A non-zero value indicates there was a problem in the input. A description 
 * of the error is returned in $error_str. The integer values returned are 
 * described in @ref LinePickingCheckParameters. 
 * @param $error_str A string describing the result of evaluating the function.
 * @return The required calculated densities are returned in $g.
 * @todo The matlab version allocates memory dynamically for the array 
 * of densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
 */
void LinePickingSimDistances(double *distances, int *N, int *problem, 
			     double* parameters, int *Npar, int *result, 
			     char **error_str)
{
    int i, Ncoords;
    int Npoints = 2;
    char *CoordSystem;
    double **points;

    /* first check input parameters */
    LinePickingCheckParameters(problem, parameters, Npar, result, error_str);

    if (*result != 0) /* something was wrong with parameters */
        return;

    /* work out the number of coordinates */
    (*LinePickingFields[*problem].NCOORDS)(&Ncoords, &CoordSystem, parameters); 
    /* allocate memory for the pointers */
    points = (double **) malloc((size_t) sizeof(double *)*(2));
    points[0] = (double *) malloc((size_t) sizeof(double)*(Ncoords));
    points[1] = (double *) malloc((size_t) sizeof(double)*(Ncoords));

    for (i=0; i<*N; i++) 
    {
	/* generate a pair of points */
	(*LinePickingFields[*problem].SIM_POINTS)
        (points, &Npoints, &Ncoords, parameters);

	/* compute the distances */
	distances[i] = (*LinePickingFields[*problem].DISTANCE)
                        (Ncoords, points[0], points[1], parameters);
    }
    free(points[0]);
    free(points[1]);
    free(points);
}






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
  
  const char *names[] = { "problem", "name", "description", 
    "npar", "parameters" };
  int problem;
  int Npar;
  int parameter;
  int i;
  
  SEXP list_names = PROTECT(allocVector(STRSXP,elements(names)));
  for(i = 0; i < elements(names); i++)
    SET_STRING_ELT(list_names,i,mkChar(names[i]));
  
  /*  This is the cector we will return to R it will ve a vector of vectors*/ 
  SEXP result = PROTECT(allocVector(VECSXP, NUMBER_OF_PROBLEMS));
  
  for (problem = 0;  problem  < NUMBER_OF_PROBLEMS; problem++)
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
 * @param $plhs[0] The output, a vector containing the values g(t) of the CDF 
 * at the points provided.
 */
void mexLinePickingCDF(int nlhs, mxArray *plhs[], int nrhs, 
                       const mxArray *prhs[], int *result, 
                       char **error_str ,  int cmd)
{
    double *t; /* points at which to calculate the distribution */
    double *g; /* value of the distribution at the points t */
    
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
    g = mxGetPr(plhs[0]);
    
    LinePickingCDF(t, g, &N, &problem, parameters, 
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
    const mwSize dims[1] = {NUMBER_OF_PROBLEMS}; 
    /* used to output a list of names of the problems */
    char *names[NUMBER_OF_PROBLEMS];
     /* used to output a list of descriptions of the problems */
    char *descriptions[NUMBER_OF_PROBLEMS];
    int Npars[NUMBER_OF_PROBLEMS];
    double *parameters[NUMBER_OF_PROBLEMS];
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
    for (i=0; i < NUMBER_OF_PROBLEMS; i++)
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
    
    double *g; /* value of the distribution at the points t */
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    
    /* output argument 1: no_of_problems, the number of implemented problems */
    g = mxGetPr(plhs[0]);
    g[0] = NUMBER_OF_PROBLEMS;
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


#ifdef _STANDALONE
/*
 * bits needed to run this as a stand alone command-line function
 *
 */

static void 
usage_LinePicking()
{
    fprintf(stderr, "Usage: LinePicking -f input_file "
                    "-m problem -p parameter[0]"
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
    *Npar = LinePickingFields[*problem].DATA->Npar;
}

int main(int argc, char *argv[])
{
    int i=0;
    int problem;
    double parameters[3];
    double DefaultParameters[MAX_PARAMETERS];
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
    LinePickingCheckParameters(&problem, parameters, &Npar, 
                               &result, &error_str);
    if (result != 0) 
    {
        fprintf(stderr, "LinePicking: %s\n", error_str);
        exit(1);
    }
    /* get the problem's name and description */
    LinePickingProblemLookup(&problem, &Problems_name, 
                             &Problems_description, &Npar, 
                             DefaultParameters);
    fprintf(stderr, 
            "%%  problem=%d, %s (%s)\n", 
            problem, Problems_name, Problems_description);
    
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

