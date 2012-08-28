/* Hyperball.c	
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
#include <stdio.h>
#include "Hyperball.h"
#include "beta.h" 

char *HyperballDistanceName = "hyper-ball";
char *HyperballDistanceDescription = "hyper-ball, with dimension parameters[0]"
                                        ", and radius parameters[1]";
int HyperballDistanceNpar = 2;


/**
 * Implements the PDF of the distance between two random points in a hyper-ball.
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $t The distance to calcuate the density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball. 
 * @return The density at $t.
 * @see  http://arxiv.org/abs/math-ph/0004021
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double HyperballDistancePDF(double t, double* parameters)
{
    double n = ceil(parameters[0]); 
    double r = parameters[1];
    double d = 2 * r;
    double r2 = r * r;
    double t2 = t * t;			     
    double p, q, x, Ix, Ix2;
    int result;
    
    x = 1.0 - t2 / (4.0 * r2);
    p = (n + 1.0) / 2.0;
    q = 1.0 / 2.0;
    Ix = beta_inc(p, q, x);
    
    return n * (pow(t, n - 1.0) / pow(r, n)) * Ix);
}


/**
 * Will implement the CDF of the distance between two random points
 * in a hyper-ball.
 
 * Not yet implemented.
 *
 * @todo Implement!
 * @param $t The distance to calcuate the density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball. 
 * @return The culmative density at $t, currently -1 for all $t.
 */
double HyperballDistanceCDF(double a, double* b)
{    
    return -1;
}


/**
 * Calculates the mean distance between two random points in a hyper-ball.
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball. 
 * @return The mean distance between wo random points in a hyper-ball.
 * @see  http://arxiv.org/abs/math-ph/0004021
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double HyperballDistanceMean(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 1;
    double tmp = pow((n / (n + m)), 2.0) * pow(parameters[1], m) *
                    tgamma(n + m + 1.0) * tgamma(n / 2.0) / 
                        (tgamma((n + m) / 2.0) * tgamma(n + 1 + m / 2.0));
    return tmp;
}


/**
 * Calculates the variance of distances between two random points in 
 a hyper-ball.
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball. 
 * @return The variance of distances between two random points in a hyper-ball.
 * @see  http://arxiv.org/abs/math-ph/0004021
 * @see  http://mathworld.wolfram.com/BallLinePicking.html
 */
double HyperballDistanceVar(double* parameters)
{
    double n = ceil(parameters[0]); 
    double m = 2;
    double tmp = pow((n / (n + m)), 2.0) * pow(parameters[1], m) *
                    tgamma(n + m + 1.0) * 
                    tgamma(n / 2.0) / 
                    ( tgamma((n + m) /2.0) * tgamma(n + 1 + m / 2.0));
    
    return tmp - pow(HyperballDistanceMean(parameters),2 .0);
}



/**
 * Calculates the support for the PDF and CDF of the distance between 
 * two random in a hyper-ball.
 *
 * @param $t Pointer to storage for lower and upper ends of the support for
 * the PDF and CDF of the distance between two random points
 * in a hyper-ball.
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball.
 * @return The lower end of the interval is returned in $t[0] and the 
 * upper end of the interval is returned in $t[1].
 */
void HyperballDistanceSupport(double *t, double *parameters)
{
    /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    t[0] = 0;
    t[1] = 2*parameters[1];
}


/**
 * Determines if the parameters supplied are valid input 
 * to the other functions implemented in this file.
 * @param $parameters $parameters[0] is the dimension of the hyper-ball under 
 * consideration and $parameters[1] is the radius of the hyper-ball under
 * consideration.
 * @param $result Pointer to storage for an integer indicating any errors  
 * in the supplied parameters.
 * @param $error_str Pointer to storage for a message explaining any errors
 * in the supplied parameters. 
 * @return Any error conditions are indicated by placing a value other than 0 
 * in the location pointed to by $result and a message explaining the error 
 * is copied in to the location pointed to $error_str
 * The only condition this function needs to check is that the dimesnion
 * of the hyper-ball consider is at least 1.
 */
void HyperballDistanceCheckParameters(double *parameters, int *result, 
                                      char *error_str)
{
    *result=0;
    /* hyper-ball, with dimension parameters[0], and radius parameters[1] */
    if (parameters[0] < 1) 
    {
        sprintf(error_str, 
                "LinePickingCheckParameters: hyperball,"
                " must have parameter[0]>=1, but  parameter[0]=%lf", 
                parameters[0]);
        *result=2;
    }
}
