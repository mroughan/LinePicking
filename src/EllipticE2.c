#include <math.h>
#include <float.h> 

/* long double versions of the library constants ie M_PI_2 and M_PI*/
static const long double L_PI_4 = 0.7853981633974483096156608458198757L;
static const long double L_PI_2 =  1.5707963267948966192313216916397514L;
static const long double L_PI   =  3.1415926535897932384626433832795029L; 


static void LandenTransform(long double phi, long double m,
                            double *ellipticF, double *ellipticK, 
                            double *ellipticE1, double *ellipticE2) 
{ 
    
    long double average, prev_average;
    long double geometric_mean, prev_geometric_mean;
    long double tan2nphi, pow2n, sum, integral;
  
    
    pow2n = 1.0L;
    average = 1.0L;
    geometric_mean = sqrtl(1.0L - m);
    sum = 2.0L * (2.0L - m);
    integral = 0.0L;
    
    do {
        tan2nphi = tanl(pow2n * phi);
        sum -= pow2n * pow((average - geometric_mean), 2);
        pow2n += pow2n;
        phi -= atanl((average - geometric_mean) * tan2nphi / 
                     (average + geometric_mean * tan2nphi * tan2nphi)) / pow2n;
        integral += (average - geometric_mean) * sinl(pow2n * phi);
        prev_geometric_mean = geometric_mean;
        prev_average = average;
        average = 0.5L * (prev_geometric_mean + prev_average);
        geometric_mean = sqrtl(prev_geometric_mean * prev_average);
        
    } while (fabsl(prev_average - prev_geometric_mean) > 
             (prev_average * DBL_EPSILON));
    
    *ellipticK = L_PI_2 / geometric_mean;
    *ellipticF = phi / geometric_mean;
    *ellipticE1 = (L_PI_4 / average) * sum / 2.0L;
    *ellipticE2 = (integral / 2.0L) + (sum * phi) / (4.0L * geometric_mean);
    
}


static void EllipticIntegralE(long double phi, long double m,
                              double *ellipticE1, double *ellipticE2)
{
    double ellipticF, ellipticK;
    int period = trunc(( phi + L_PI_2 ) / L_PI );
    /* center phi around 0 */
    phi -= period * L_PI;
    period *= 2;
    LandenTransform(fabsl(phi), m, &ellipticF, &ellipticK, 
                    ellipticE1, ellipticE2);
    *ellipticE2 = period * *ellipticE1 + 
                    ((phi >= 0.0) ? *ellipticE2 : - *ellipticE2);
   
    
    return;
}


static double ModulusBig(double amplitude, long double k)
{
    double ellipticF, ellipticK, ellipticE2, ellipticE1; 
    long double phi = amplitude; /* up cast amplitude */
    long double sin_phi;
    
    int period = trunc(( phi + L_PI_2 ) / L_PI );
    /* center phi around 0 */
    phi -= period * L_PI;
    period *=2;
    
    /* sin of centered phi */
    sin_phi = sinl(phi);
    
    if ( fabsl(sin_phi) >= 1.0L / k ) 
        phi = ((phi > 0.0L) ? L_PI_2 : -L_PI_2);
    else 
        phi = asinl(k * sin_phi);
    
    
    LandenTransform( fabsl(phi), 1.0L / (k * k) , 
                    &ellipticF, &ellipticK, &ellipticE1, &ellipticE2);
    
    ellipticE1 = k * ellipticE1 + (1.0L - k * k) * ellipticK / k;
    ellipticE2 = k * ellipticE2 + (1.0L - k * k) * ellipticF / k;
    
    return period * ellipticE1 + ((phi >= 0.0L) ? ellipticE2 : -ellipticE2);     
  
}


double EllipticE2(double amplitude,  double parameter)
{
    long double phi, k, m;
    double ellipticE1, ellipticE2;
    int n;
    int direction;
    
    
    /* promote to a long double */
    m = parameter;
    k = sqrtl(fabsl(m));
    
    /* if the amplitude is 0 then the modulus has no effect */
    if ( amplitude == 0.0 ) return 0.0;
    
    /* direction of amplitude */
    direction = (amplitude < 0.0) ? -1 : 1;
    
    /* corner cases */
    
    if (m == 0.0L) 
        return amplitude;
    
    if (m > 1.0L)
        return direction * ModulusBig(fabs(amplitude), k);
    
    if (m == 1.0L) 
    {
        if ( fabs(amplitude) <= M_PI_2) 
            return sin(amplitude);
        
        n = (int) ( (amplitude + M_PI_2) / M_PI );
        n += n;
        return (double) n + sin(amplitude - n * M_PI);
    }
    
    if (m < 0.0L) 
    {
        phi = L_PI_2 - fabsl( amplitude);
        EllipticIntegralE(fabsl(phi), fabsl(m / (1.0L - m)),
                                      &ellipticE1, &ellipticE2);

        return (direction * (ellipticE1 + 
                ((phi > L_PI_2) ? ellipticE2 : -ellipticE2)) * sqrtl(1.0L - m));    

    }
    
    /*  m in (0,1) this is the main case we are interested in */
    
        EllipticIntegralE(fabsl(amplitude), m, &ellipticE1, &ellipticE2);
        return direction * ellipticE2;
}
