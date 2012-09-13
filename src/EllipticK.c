/* HyperGeometric.c
 *
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
#include <float.h>  
#include "EllipticK.h"
/**
 * Computes complete elliptic integral of the first kind.
 * @param $parameter The parameter as discussed in the literature.
 * @return The result of evaluating the complete elliptic integral of 
 * the first kind.
 */

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
