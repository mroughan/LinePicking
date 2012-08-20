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
#include <math.h>
#include <stdio.h>

/* 
   Incomplete beta function fusing information from
@article{Didonato:1992:ASD:131766.131776,
 author = {Didonato, Armido R. and Morris,Jr., Alfred H.},
 title = {Algorithm 708: Significant digit computation of the incomplete beta function ratios},
 journal = {ACM Trans. Math. Softw.},
 issue_date = {Sept. 1992},
 volume = {18},
 number = {3},
 month = sep,
 year = {1992},
 issn = {0098-3500},
 pages = {360--373},
 numpages = {14},
 url = {http://doi.acm.org/10.1145/131766.131776},
 doi = {10.1145/131766.131776},
 acmid = {131776},
 publisher = {ACM},
 address = {New York, NY, USA},
 keywords = {F-distribution, continued fractions, minimax approximations},
} 

and http://www.boost.org/doc/libs/1_38_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/sf_beta/ibeta_function.html

but mainly from http://dlmf.nist.gov/8.17

HOWEVER NOTE

   this is all pretty crude, perhaps you're better off using a public library like
      http://www.mymathlib.com/functions/gamma_beta.html
      http://www.boost.org/doc/libs/1_38_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/sf_beta/ibeta_function.html

 */

/* beta function in terms of gamma functions */
double beta(double a, double b)
{
    /* C gamma function is deprecated, use tgamma instead */
    return( exp( lgamma(a) + lgamma(b) - lgamma(a+b)) );

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

/* regularized incomplete beta function */
double beta_inc(double a, double b, double x)
{
    double cf;

    /* check input arguments */
    if (x < 0.0 || x > 1.0) 
    {
	fprintf(stderr, "beta_inc: x (=%.3f) must be in the interval [0,1]\n", x);
	exit(1);
    }
    if (a < 0)
    {
	fprintf(stderr, "beta_inc: a (=%.3f) must be > 0\n", a);
	exit(1);
    }
    if (b < 0)
    {
	fprintf(stderr, "beta_inc: b (=%.3f) must be > 0\n", b);
	exit(1);
    }
    /* printf("    a=%.2f, b=%.2f, x=%6f, (a+1.0)/(a+b+2.0)=%6f\n", a, b, x,(a+1.0)/(a+b+2.0));     */
	
    /* deal with some extreme cases */
    if (x==0.0) return(0.0);
    else if (x==1.0) return(1.0);
 
    if (a==0.0) return(1.0);
    else if (b==0.0) return(0.0);

    if (a==1.0 && b==1.0) return (x);
    else if (a==1.0) return( (1 - pow(1-x,b))/(b*beta(a,b)) );
    else if (b==1.0) return( pow(x,a)/(a*beta(a,b)) );

    /* use identities to get a>1 and b>1  */
    if (a < 1 && b < 1) {
	return( (a*beta_inc(a+1,b,x) + b*beta_inc(a,b+1,x))/(a+b)  );
    } else if (a < 1) {
	return( beta_inc(a+1,b,x) + pow(x,a)*pow(1-x,b)/(a*beta(a,b)) );
    } else if (b < 1) {
	return( beta_inc(a,b+1,x) - pow(x,a)*pow(1-x,b)/(b*beta(a,b)) );
    }

    /* get started */
    if (x <= (a+1.0)/(a+b+2.0)) {
	/* use continued fractions */
	cf = beta_cont_frac(a,b,x);
	return( pow(x,a)*pow(1-x,b)*cf/(a*beta(a,b)) );
    } else {
	/* look at complement */
	/* cf = beta_cont_frac(b, a, 1-x); */
	/* return( 1.0 -  pow(x,a)*pow(1-x,b)*cf/(b*beta(b,a)) );*/
	return( 1.0 - beta_inc(b, a, 1.0-x) ); 
    }
    
}

