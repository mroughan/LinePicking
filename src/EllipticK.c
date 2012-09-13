#include <math.h>       
#include <float.h>  
#include "EllipticK.h"

double EllipticK(double parameter)
{
    /* 
     * This is defined in the same way as the Mathmatica 
     * function of the same name so parameter = k^2
     */
    
    long double average, prev_average; 
    long double geometric_mean, prev_geometric_mean;      
    long double m = parameter; 
    
    /* deal with the extremes */
    if(0.0 >= parameter) return M_PI_2;
    if(1.0 <= parameter) return DBL_MAX; 
    
    average = 1.0L;
    geometric_mean = sqrtl(1.0L - m);
    
    do  
    {
        prev_average = average;
        prev_geometric_mean = geometric_mean;
        
        average = (prev_geometric_mean + prev_average) / 2.0L;
        geometric_mean = sqrtl(prev_geometric_mean * prev_average);
        
    } while (fabs(prev_average * DBL_EPSILON) < 
             fabs(prev_geometric_mean - prev_average));
    
    return M_PI_2 / geometric_mean; 
}
