/* beta.c
 *
 * Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
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

#include "beta.h"
   
#ifndef _NOTR 
#include <R.h> /* only include this if we are compiling for R */
#endif

/**
 * Implements the beta function. i.e., the Euler integral of the first kind, 
 * defined by \f$ \mathrm{B}(x,y) = \int_0^1t^{x-1}(1-t)^{y-1}\,dt \f$.
 * 
 * @param $x in \f$ \mathrm{B}(x,y) = \int_0^1t^{x-1}(1-t)^{y-1}\,dt \f$.
 * @param $y in \f$ \mathrm{B}(x,y) = \int_0^1t^{x-1}(1-t)^{y-1}\,dt \f$.
 *
 * @return
 * The result of evaluating Eulers integral of the first 
 * kind with the given parameters.
 */
double beta(double x, double y)
{
    /* C gamma function is deprecated, use tgamma instead */
    return( exp( lgamma(x) + lgamma(y) - lgamma(x+y)) );

}


/* beta continued fraction calculation 
      don't use this directly -- its used below
*/
double beta_cont_frac(double a, double b, double x)
{
    double d, cf=0;
    int i, m;
    int n = 10;
    for (i=n; i>=1; i--) {
	m = i/2;
	if (i % 2 == 0) {
	    /* even case */
	    d = m*(b-m)*x / ((a+2*m-1)*(a+2*m));
	} else {
	    /* odd case */
	    d = - (a+m)*(a+b+m)*x / ( (a+2*m)*(a+2*m+1) );
	}
	cf = d / (1 + cf);
    }
    cf = 1 / (1 + cf);
    return(cf);
}


/**
 * Implements the regularized incomplete beta function. 
 * Defined as \f$ I_x(a,b) = \dfrac{B(x;\,a,b)}{B(a,b)}. \f$ Where 
 * \f$ \mathrm{B}(a,b) = \int_0^1t^{a-1}(1-t)^{b-1}\,dt \f$ and
 * \f$ B(x;\,a,b) = \int_0^x t^{a-1}\,(1-t)^{b-1}\,dt. \f$ \n
 * @see http://doi.acm.org/10.1145/131766.131776 
 * @see http://www.boost.org/doc/libs/1_38_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/sf_beta/ibeta_function.html 
 * @see http://dlmf.nist.gov/8.17
 * @param $a in \f$ I_x(a,b) = \dfrac{B(x;\,a,b)}{B(a,b)}. \f$
 * @param $b in  \f$ I_x(a,b) = \dfrac{B(x;\,a,b)}{B(a,b)}. \f$
 * @param $x in  \f$ I_x(a,b) = \dfrac{B(x;\,a,b)}{B(a,b)}. \f$
 * @param $result is non zero if some error occured.  
 * @return
 * The result of evaluating the incomplete beta function with 
 * the given parameters or an error conditon returned in $result 
 */
/* regularized incomplete beta function */
double beta_inc(double a, double b, double x, int *result)
{
    double cf;

    /* result = 0 if no error is encontered */
    *result = 0;
    
    /* check input arguments */
    if (x < 0.0 || x > 1.0) 
    {
        PRINT_STDOUT("beta_inc: x (=%.3f) must be in the interval [0,1]\n", x);
        *result = 1;
        return 0;
    }
    if (a < 0)
    {
        PRINT_STDOUT("beta_inc: a (=%.3f) must be > 0\n", a);
        *result = 2;
        return 0;
    }
    if (b < 0)
    {
        PRINT_STDOUT("beta_inc: b (=%.3f) must be > 0\n", b);
        *result = 3;
        return 0;
    }
	
    /* deal with some extreme cases */
    if (x == 0.0) 
        return 0.0;
    else 
        if (x == 1.0) return 1.0;
    
    if (a == 0.0) 
        return 1.0;
    else
    {
        if (b == 0.0) 
            return 0.0;
    }
    
    if (a == 1.0 && b == 1.0) 
        return x;
    else
    {
        if (a == 1.0) 
            return (1 - pow(1 - x, b))/(b * beta(a, b));
        else 
            if (b == 1.0) 
                return pow(x, a) / (a * beta(a, b));
    }
    
    /* use identities to get a>1 and b>1  */
    if (a < 1 && b < 1) 
    {
        return (a * beta_inc(a + 1, b, x, result) + 
                b * beta_inc(a, b + 1, x, result)) / (a + b)  ;
    } 
    else if (a < 1) 
    {
        return beta_inc(a + 1, b, x, result) + 
                pow(x, a) * pow(1 - x, b) / (a * beta(a, b));
    } 
    else if (b < 1) 
    {
        return beta_inc(a,b+1,x, result) - 
                pow(x, a) * pow(1 - x, b) / (b * beta(a, b));
    }

    /* get started */
    if (x <= (a + 1.0) / (a + b + 2.0)) 
    {
        /* use continued fractions */
        cf = beta_cont_frac(a, b, x);
        return pow(x, a) * pow(1 - x, b) * cf / (a * beta(a,b )) ;
    } 
    else 
    {
        /* look at complement */
        /* cf = beta_cont_frac(b, a, 1-x); */
        /* return( 1.0 -  pow(x,a)*pow(1-x,b)*cf/(b*beta(b,a)) );*/
        return 1.0 - beta_inc(b, a, 1.0-x, result); 
    }
    
}

