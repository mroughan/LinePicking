    

#include <math.h>          
#include <float.h>          

/* long double versions of the library constants ie M_PI_2 and M_PI*/
static const long double L_PI_2 =  1.5707963267948966192313216916397514L; 
static const long double L_PI   =  3.1415926535897932384626433832795029L; 


void LandenTransform( long double phi, long double m,
                     double *ellipticF, double *ellipticK) 
{ 
    
    long double average, prev_average;
    long double geometric_mean, prev_geometric_mean;
    long double tan2nphi, pow2n;

    
    pow2n = 1.0L;
    average = 1.0L;
    geometric_mean = sqrtl(1.0L - m);
    do {
        tan2nphi = tanl(phi);
        pow2n += pow2n;
        phi += phi - atanl((average - geometric_mean) * tan2nphi / 
                           (average + geometric_mean * 
                            tan2nphi * tan2nphi));
        prev_geometric_mean = geometric_mean;
        prev_average = average;
        average = (prev_geometric_mean + prev_average) / 2.0L;
        geometric_mean = sqrtl(prev_geometric_mean * prev_average);
        
    } while (fabs(prev_average - prev_geometric_mean) > 
             fabs(prev_average * DBL_EPSILON));
    
    *ellipticK =  L_PI_2 / geometric_mean;
    *ellipticF =  phi / (geometric_mean * pow2n); 
}

void EllipticIntegralF(long double phi, long double m,
                               double *ellipticF, double *ellipticK)
{ 
    int period = trunc(( phi + L_PI_2 ) / L_PI );
    /* center phi around 0*/
    phi -= period * L_PI;
    period *= 2;
    LandenTransform( fabsl(phi), m, ellipticF, ellipticK);
    *ellipticF = period * (*ellipticK) + 
                    ((phi < 0.0L) ? -(*ellipticF) : (*ellipticF)); 
    
}


double ModulusBig(double amplitude, long double k)
{
    double ellipticF, ellipticK; 
    long double phi = amplitude; /* up cast amplitude */
    long double sin_phi;
    
    int period = trunc(( phi + L_PI_2 ) / L_PI );
    /* center phi around 0 */
    phi -= period * L_PI;
    period *=2;
    
    /* sin of centered phi */
    sin_phi = sinl(phi);
    
    if (fabsl(sin_phi) >= 1.0L / k )
        phi = ((phi > 0.0L) ? L_PI_2 : -L_PI_2);
    else 
        phi = asinl(k * sin_phi);
    
    
    LandenTransform( fabsl(phi), 1.0L / (k*k) , &ellipticF, &ellipticK);
    
    ellipticF = period * ellipticK + ((phi < 0.0L) ? -ellipticF : ellipticF); 
    
    return ellipticF/k;
}

double EllipticF(double amplitude,  double parameter)
{
    long double phi, k , m;
    double ellipticF, ellipticK, modulus;
    int direction;
    
    /* promote to a long double */
    m = parameter;
    k = sqrtl(fabsl(m));
    
    /* if the amplitude is 0 then the modulus has no effect */
    if ( amplitude == 0.0 ) return 0.0;
    
    /* direction of amplitude */
    direction = (amplitude < 0.0) ? -1 : 1;
    
    /* corner cases */

    if ( m == 0.0L) 
        return amplitude;
    
    if ( m > 1.0L ) 
        return direction * ModulusBig(fabs(amplitude), k);
    
    if ( m == 1.0L ) 
    {
        if (fabs(amplitude) >= M_PI_2) 
            return direction * DBL_MAX;
        
        modulus = tan(amplitude);
        return direction * (log(fabs(modulus) + sqrt(1.0 + modulus * modulus)));
    }
    
    if (m < 0.0L ) 
    {
        phi = L_PI_2 - fabsl(amplitude);
        EllipticIntegralF( fabsl(phi), fabsl(m / (1.0L - m)), 
                                  &ellipticF, &ellipticK);
        return (direction * 
                (ellipticK + ((phi > L_PI_2) ? ellipticF : -ellipticF)) / 
                    sqrtl(1.0L - m));
        
    }
    
    /*  m in (0,1) this is the main case wae are interested in */
    EllipticIntegralF(fabs(amplitude), m, &ellipticF, &ellipticK);
    return direction * ellipticF;
    
}
