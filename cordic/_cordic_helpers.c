/**
 * @file _cordic_helpers.c
 * @brief Helper wrappers for f2py Python bindings.
 *
 * cossin_cordic returns cos/sin via output pointers; these thin wrappers
 * expose them as scalar-returning functions suitable for f2py.
 */

#include "cordic.h"

/**
 * @brief Compute cosine via cossin_cordic (scalar-returning wrapper).
 *
 * @param beta  Angle in radians.
 * @param n     Number of CORDIC iterations.
 * @return      cos(@p beta).
 */
double cos_cordic_wrapper(double beta, int n) {
    double c, s;
    cossin_cordic(beta, n, &c, &s);
    return c;
}

/**
 * @brief Compute sine via cossin_cordic (scalar-returning wrapper).
 *
 * @param beta  Angle in radians.
 * @param n     Number of CORDIC iterations.
 * @return      sin(@p beta).
 */
double sin_cordic_wrapper(double beta, int n) {
    double c, s;
    cossin_cordic(beta, n, &c, &s);
    return s;
}
