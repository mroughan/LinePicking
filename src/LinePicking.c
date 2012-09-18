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

#include <string.h>
#include <unistd.h>
#include <float.h>
#include "LinePicking.h"
#include "beta.h" 
#include "Square.h"
#include "Disk.h"
#include "Hyperball.h"
#include "Rectangle.h"
#include "Line.h"	
#include "Cube.h"
#include "Sphere.h"
#include "SphereGeodesic.h"
#include "PrismGeodesic.h"
#include "RectangleManhattan.h"
#include "RectangleMax.h"
#include "HyperSphere.h"
#include "HyperSphereGeodesic.h"
#include "CylindricalSurface.h"
#include "CylindricalSurfaceGeodesic.h"
#include "Cylinder.h"
#include "CubeMax.h"
#include "HyperCubeMax.h"


/* a buffer available globally for errors */
char global_error_str[256];


typedef struct 
{
    double (* PDF)(double, double *); 
    double (* CDF)(double, double *);
    double (* MEAN)(double *);
    double (* VAR)(double *);
    void   (* SUPPORT)(double*, double *);
    void   (* CHECK_PAR)(double*, int *, char *);
    void   (* NCOORDS)(int *, char **, double *);
    void   (* SIM_POINTS)(double **, int *, int *, double *);
    double (* DISTANCE)(int, double *, double *, double *);
    LinePickingData *DATA; 
} LinePickingRec;


#define ExpandFields(_x) &_x##DistancePDF,&_x##DistanceCDF,\
&_x##DistanceMean,&_x##DistanceVar,\
&_x##DistanceSupport,&_x##DistanceCheckParameters,\
&_x##DistanceNcoords,&_x##DistanceSimPoints,&_x##DistanceMetric,\
&_x##DistanceData

LinePickingRec LinePickingFields[] = 
{ 
    {ExpandFields(Square)},
    {ExpandFields(Disk)},
    {ExpandFields(Hyperball)},
    {ExpandFields(Rectangle)},
    {ExpandFields(Line)},
    {ExpandFields(Cube)},
    {ExpandFields(Sphere)}, 
    {ExpandFields(SphereGeodesic)},
    {ExpandFields(PrismGeodesic)},
    {ExpandFields(RectangleManhattan)}, 
    {ExpandFields(RectangleMax)}, 
    {ExpandFields(HyperSphere)},
    {ExpandFields(HyperSphereGeodesic)},
    {ExpandFields(CylindricalSurface)},
    {ExpandFields(CylindricalSurfaceGeodesic)},
    {ExpandFields(Cylinder)},
    {ExpandFields(CubeMax)},
    {ExpandFields(HyperCubeMax)}
};

#define elements(x)  (sizeof(x) / sizeof(x[0]))
#define NUMBER_OF_PROBLEMS elements(LinePickingFields)



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
 * Helper function returns a pointer to the LinePickingData struct 
 * associated with a given problem.
 * @param $problem Represents a problem. 
 * @return Pointer to the LinePickingData struct associated with 
 * the given problem, NULL if the problem is not implemented.
 */
LinePickingData *LinePickingGetData(int *problem) 
{
    
	if (*problem < 0 || *problem  >= NUMBER_OF_PROBLEMS)
	{
		
		return NULL;
	}
    
	return  LinePickingFields[*problem].DATA;
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
 * @param $t An array of distances for which to calculate the CDF.
 * @param $G An array in which the calculated cumulative densities are returned.
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
 * @return The required calculated cumulative densities are returned in $G.
 * @todo The matlab version allocates memory dynamically for the array 
 * of cumulative densities which is safe. The R version could go horribly wrong 
 * if a shorter array was passed.
 * @bug potential array bounds overrun.
 */
void LinePickingCDF(double *t, double *G, int *N, int *problem, 
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
            G[i] = 0.0;
        else 
        {
            if (t[i] >= support[1]) 
                G[i] = 1.0;
            else 
                G[i] = (*LinePickingFields[*problem].CDF)(t[i], parameters);
        }
    }
}


/**
 * Implements the InverseCDF of the distance between two random points for the 
 * given problem. CDF's are monotonic non-decreasing, so inverting is simply
 * a matter of searching.
 *
 * Where there is a non-increasing segment, there are multiple possible
 * results, but as we compute the this only over the support, and all of 
 * our current CDFs  are strictly increasing over their support.
 *
 * Also, where we don't know a closed form for the CDF, it returns -1, and so
 * therefore does this function.
 * 
 * @param $t An array of returned distances, such that CDF($t) = $G.
 * @param $G An array in which the calculated cumulative densities are input.
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
void LinePickingInverseCDF(double *G, double *t, int *N, int *problem, 
			   double* parameters, int *Npar, int *result, 
			   char **error_str) 

{
    int i;
    double support[2];
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);
    
     /* something was wrong with parameters */
    if (*result != 0) return;
    
    /* if the CDF isn't implemented, returns -1 */
    if (0 > (*LinePickingFields[*problem].CDF)
                ((support[0] + support[1]) / 2, parameters))
    {
        for (i = 0; i < *N; i++) t[i] = -1;
        return;
    }
    
    /* calculate the inverse CDF */
    for (i = 0; i < *N; i++) 
    {
        if (G[i] >= 1.0) 
        {
            t[i] = support[1];
            continue;  
        }

        if (G[i] <= 0.0)
        {
            t[i] = support[0];
            continue; 
        }

        /* implement the inverse CDF using a search */
        t[i] = search(G[i], parameters, support, 
                      *LinePickingFields[*problem].CDF);
    }
}


/**
 * Simple binary search used for implementing the inverse CDF. 
 * 
 * @param $G the CDF value to match
 * @param $parameters the parameters of the problem
 * @param $support is the support of the PDF, 
 * which is the range over which to search
 * @param $CDF the CDF function of the problem
 * @return $t is such that CDF($t) = $G
 */
double search(double G, double* parameters, double* support, 
              double (* CDF)(double, double *))
{
    static const int MAX_ITTERATIONS = 100; /* necessary ?*/
    double t, Gi;
    int i;
    double lower_bound = support[0];
    double upper_bound = support[1];
   
    
    for(i = 0; i < MAX_ITTERATIONS; i ++) 
    {
        t = (upper_bound + lower_bound) / 2.0;
        Gi = (*CDF)(t, parameters);
               
        if (fabs(G - Gi) < fabs(G * DBL_EPSILON)) 
            break;
            
        if (Gi < G) 
            lower_bound = t;
        else 
            upper_bound = t;
    }
    return t;
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
* Calculates the median distance between two random points for the 
* given problem.
*
* 
* @param $median A pointer to the location where the mean will be stored.
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
* @return The required calculated mean is returned in $median.
*/
void LinePickingMedian(double *median, int *problem, 
		       double* parameters, int *Npar, int *result, 
		       char **error_str) 

{
    double support[2];
    double G = 0.5;
    int N = 1;
    
    /* now calculate the support of the distribution,
     which will incidentally check that the parameters are valid
     */
    LinePickingSupport(support, problem, parameters, Npar, result, error_str);
    if (*result != 0) 
    /* something was wrong with parameters */
        return; 
    
    /* calculate the median, by looking at the 50th percentile */
    LinePickingInverseCDF(&G, median, &N, problem, parameters, Npar, result, error_str);

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

