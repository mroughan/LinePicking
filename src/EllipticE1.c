#include <math.h>
#include <float.h>

static const long double L_PI_4 = 0.7853981633974483096156608458198757L; 

double EllipticE1(double parameter)
{
    /* 
     * This is defined in the same way as the Mathmatica 
     * function of the same name so parameter = k^2
     */
    long double average, prev_average; 
    long double geometric_mean, prev_geometric_mean; 
    long double pow2n, E1;
    long double m = parameter; /* promote to long double */
    
    if (1.0 == parameter) return 1.0;
    if (0.0 == parameter) return M_PI_2;

    /* powers of 2 starting at 0 */
    pow2n = 1.0L;
    E1 = 2.0L - m;
    average = 1.0L;
    geometric_mean = sqrtl(1.0L - m);
    
    do {
        pow2n += pow2n;
        prev_average = average;
        prev_geometric_mean = geometric_mean;
        average = (prev_geometric_mean + prev_average) / 2.0L;
        geometric_mean = prev_average * prev_geometric_mean;
        
        E1 -= pow2n * (average * average - geometric_mean);
        geometric_mean = sqrtl(geometric_mean);
        
    } while ((prev_average * DBL_EPSILON) < 
             fabsl(prev_geometric_mean - prev_average));
    
    return E1 * L_PI_4 / average; 
}
