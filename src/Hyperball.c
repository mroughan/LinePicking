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
#include <stdlib.h>
#include <stdio.h>

#include "LinePickingData.h"
#include "metrics.h"
#include "Rand.h"
#include "Hyperball.h"
#include "beta.h" 

LinePickingData HyperballDistanceData =
{
   "hyper-ball",
    "hyper-ball, with dimension parameters[0], and radius parameters[1]",
    2,
    {3, 1}
};


/**
 * Implements the PDF of the distance between two random points in a hyper-ball.
 *
 * From Tu, S.-J. and Fischbach, E.
 * "A New Geometric Probability Technique for an {N}-Dimensional 
 * Sphere and Its Applications"
 *
 * @param $t The distance to calculate the density for.
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
    /* double d = 2 * r; */
    double r2 = r * r;
    double t2 = t * t;			     
    double p, q, x, Ix;
    int result;
    
    x = 1.0 - t2 / (4.0 * r2);
    p = (n + 1.0) / 2.0;
    q = 1.0 / 2.0;
    
    /* 
     * we dont need to check the result from beta_inc
     * because the parameters to this function have
     * been checked thus what we pass to beta_inc is 
     * also correct */
    Ix = beta_inc(p, q, x, &result);
    
    return n * (pow(t, n - 1.0) / pow(r, n)) * Ix;
}


/**
 * Will implement the CDF of the distance between two random points
 * in a hyper-ball.
 *
 * @param $t The distance to calculate the cumulative density for.
 * @param $parameters $parameters[0] is the dimension of the hyper-ball and 
 * $parameters[1] is the radius of the hyper-ball. 
 * @return The cumulative density at $t.
 */
double HyperballDistanceCDF(double t, double* parameters)
{    
    double n = ceil(parameters[0]); 
    double r = parameters[1];
    /* double d = 2 * r; */
    double r2 = r * r;
    double t2 = t * t;			     
    double p, q, x, Ix, Bx;
    int result;
    
    x = 1.0 - t2 / (4.0 * r2);
    p = (n + 1.0) / 2.0;
    q = 1.0 / 2.0;
    
    /* 
     * we dont need to check the result from beta_inc
     * because the parameters to this function have
     * been checked thus what we pass to beta_inc is 
     * also correct */
    Ix = beta_inc(p, q, x, &result);
    Bx = beta_inc(q+n/2, p, 1-x, &result) * beta(q+n/2, p) / beta(q,p);

    return pow(2,n) * ( pow(t/(2*r), n) * Ix + Bx);
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
 * @return The mean distance between two random points in a hyper-ball.
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
                    (tgamma((n + m) /2.0) * tgamma(n + 1 + m / 2.0));
    
    return tmp - pow(HyperballDistanceMean(parameters),2.0);
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


/**
 * Returns the number of coordinates used given input problem and parameters.
 *
 * @param $Ncoords returns the number of coordinates
 * @param $CoordSystem returns a brief description of the coordinate system
 * @param $parameters parameters[0] is the length of the sides of 
 * the square under consideration.
 */
void HyperballDistanceNcoords(int *Ncoords, char **CoordSystem, double* parameters) 
{
    *Ncoords= (int) (parameters[0]);
    *CoordSystem="Euclidean"; /* We could use cicular coordinates, but why?" */
}

/**
 * Simulate a set of points from the problem of interest.
 *
 * @param $points = Npoints x Ncoords array of coordinates, in the correct system.
 * @param $Npoints = number of points to generate.
 * @param $Ncoords = number of coordinates for each point.
 * @param $parameters $parameters[] is the diameter of the hyper-ball under
 * consideration.
 */
void HyperballDistanceSimPoints(double **points, int *Npoints, int *Ncoords, double* parameters)
{
    int i, j;
    double *normals;
    double sum, u;
    
    /* not the most efficient use of normal random number generation, but it should work for all nballs */
    normals = (double *) malloc(sizeof(double)*(*Ncoords));
    for (i=0; i<*Npoints; i++)
    {
	/* generate n normal random variables */
	rand_normal(*Ncoords, normals);

	/* normalize them so that they lie on the (n-1)-sphere */
	sum = 0;
	for (j=0; j<*Ncoords; j++) sum += normals[j]*normals[j];
	for (j=0; j<*Ncoords; j++) points[i][j] = normals[j]/sqrt(sum);
	
	/* now distribute them through the disk */
	u = pow(drand48(), 1.0 / *Ncoords);
	for (j=0; j<*Ncoords; j++)
	{
	    points[i][j] = parameters[1] * u * points[i][j];
	}
    }
    free(normals);
}

/**
 * Calculate distance (using correct metric) between 2 points.
 *
 * @param $Ncoords = number of coordinates for each point.
 * @param $points1 = coordinates of first point.
 * @param $points2 = coordinates of second point.
 * @param $parameters $parameters[1] is the diameter of the hyper-ball under
 * consideration.
 * @return The distance between the two points.
 */
double HyperballDistanceMetric(int Ncoords, double *point1, double* point2, double* parameters)
{
    return DistanceEuclidean(Ncoords, point1, point2);
}
