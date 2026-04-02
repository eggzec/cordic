/**
 * @file cordic.h
 * @brief CORDIC — COordinate Rotation DIgital Computer
 *
 * An iterative algorithm for evaluating trigonometric, hyperbolic,
 * exponential, logarithmic, and root functions using only shifts,
 * additions, and a small look-up table.
 *
 * @author  John Burkardt
 * @date    2012
 *
 * @par License
 *   Distributed under the GNU LGPL license.
 *
 * @par Reference
 *   Jean-Michel Muller,
 *   "Elementary Functions: Algorithms and Implementation",
 *   2nd ed., Birkhäuser, 2006, ISBN 978-0-8176-4372-0.
 */

#ifndef CORDIC_H
#define CORDIC_H

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Shift angle @p alpha into the interval [@p beta, @p beta + 2π).
     *
     * @param alpha  Angle to be shifted (radians).
     * @param beta   Lower bound of the target interval (radians).
     * @return       Shifted angle in [@p beta, @p beta + 2π).
     */
    double angle_shift(double alpha, double beta);

    /**
     * @brief Compute arccosine via the CORDIC algorithm.
     *
     * @param t  Cosine value, must satisfy −1 ≤ @p t ≤ 1.
     * @param n  Number of CORDIC iterations (≥ 20 recommended).
     * @return   Angle whose cosine is @p t (radians).
     */
    double arccos_cordic(double t, int n);

    /**
     * @brief Compute arcsine via the CORDIC algorithm.
     *
     * @param t  Sine value, must satisfy −1 ≤ @p t ≤ 1.
     * @param n  Number of CORDIC iterations (≥ 20 recommended).
     * @return   Angle whose sine is @p t (radians).
     */
    double arcsin_cordic(double t, int n);

    /**
     * @brief Compute arctangent of @p y / @p x via the CORDIC algorithm.
     *
     * @param x  X-component.
     * @param y  Y-component.
     * @param n  Number of CORDIC iterations (≥ 20 recommended).
     * @return   Angle whose tangent is @p y / @p x (radians).
     */
    double arctan_cordic(double x, double y, int n);

    /**
     * @brief Compute cube root via the CORDIC method.
     *
     * @param x  Input value.
     * @param n  Number of binary-search iterations (up to 53).
     * @return   Approximate cube root of @p x.
     */
    double cbrt_cordic(double x, int n);

    /**
     * @brief Compute cosine and sine simultaneously via the CORDIC algorithm.
     *
     * @param      beta  Angle in radians.
     * @param      n     Number of CORDIC iterations (≥ 20 recommended).
     * @param[out] c     Pointer receiving cos(@p beta).
     * @param[out] s     Pointer receiving sin(@p beta).
     */
    void cossin_cordic(double beta, int n, double *c, double *s);

    /**
     * @brief Compute exponential e^x via the CORDIC method.
     *
     * @param x  Input value.
     * @param n  Number of iterations.
     * @return   Approximate value of e^x.
     */
    double exp_cordic(double x, int n);

    /**
     * @brief Compute natural logarithm via the CORDIC method.
     *
     * @param x  Input value (must be > 0).
     * @param n  Number of iterations.
     * @return   Approximate value of ln(@p x).
     */
    double ln_cordic(double x, int n);

    /**
     * @brief Multiply two doubles via CORDIC shift-and-add.
     *
     * @param x  First factor.
     * @param y  Second factor.
     * @return   Product @p x × @p y.
     */
    double multiply_cordic(double x, double y);

    /**
     * @brief Compute square root via the CORDIC method.
     *
     * @param x  Non-negative input value.
     * @param n  Number of binary-search iterations (up to 53).
     * @return   Approximate square root of @p x.
     */
    double sqrt_cordic(double x, int n);

    /**
     * @brief Compute tangent via the CORDIC algorithm.
     *
     * @param beta  Angle in radians.
     * @param n     Number of CORDIC iterations (≥ 20 recommended).
     * @return      Approximate tangent of @p beta.
     */
    double tan_cordic(double beta, int n);

    /* ---- Test-value helpers (used by test drivers) ---- */

    /** @brief Return tabulated arccosine values. */
    void arccos_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated arcsine values. */
    void arcsin_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated arctangent values. */
    void arctan_values(int *n_data, double *x, double *f);

    /** @brief Return tabulated cube-root values. */
    void cbrt_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated cosine values. */
    void cos_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated exponential values. */
    void exp_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated natural-log values. */
    void ln_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated sine values. */
    void sin_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated square-root values. */
    void sqrt_values(int *n_data, double *x, double *fx);

    /** @brief Return tabulated tangent values. */
    void tan_values(int *n_data, double *x, double *fx);

    /* ---- Utility helpers ---- */

    /** @brief Return a "huge" 32-bit integer (INT_MAX equivalent). */
    int i4_huge(void);

    /** @brief Return the minimum of two integers. */
    int i4_min(int i1, int i2);

    /** @brief Linear-congruential PRNG returning a value in (0, 1). */
    double r8_uniform_01(int *seed);

    /** @brief Print a YMDHMS timestamp to stdout. */
    void timestamp(void);

#ifdef __cplusplus
}
#endif

#endif /* CORDIC_H */
