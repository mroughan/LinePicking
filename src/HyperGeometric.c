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


#include "HyperGeometric.h"


/**
 * Computes the hypergeometric function using a series expansion.
 * @param $a
 * @param $b
 * @param $c The Hypergeometric function converges only for 
 * $c != 0, -1, -2, -3, ...
 * @param $x The Hypergeometric function converges only for |$x| < 1
 * param $n Number of terms in the seres to evaluate
 * @return
 * The result of evaluating the hypergeometric function.
 */


double hypergeometric2f1_(double a, double  b, double c, double x, int n)
{
    /* quick hack does series expansion up to n terms */
    
    int m;
    double z;
    double delta;
    
    m = 0;
    z = 0;
    delta = 1;
    
    
    while (m < n)
    {
        if (m != 0)
            delta = delta * x * (a + (m - 1)) * (b + (m - 1)) / m / 
            (c + (m - 1));
        
        z = z + delta;
        m = m + 1;
    }
    return z;
}