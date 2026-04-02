/**
 * @file test_cordic.c
 * @brief CTest test suite for the CORDIC library.
 *
 * Test data is taken from the tabulated values embedded in cordic.c
 * (originally from the legacy test suite by John Burkardt).
 * At n=25 CORDIC iterations the results agree to roughly 1e-7.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cordic.h"

#define ATOL  1.0e-6
#define N     25

static int g_pass = 0;
static int g_fail = 0;

static void check(const char *name, double got, double expected, double tol) {
    double diff = fabs(got - expected);
    if (diff > tol) {
        fprintf(stderr, "FAIL  %-20s  got %16.10g  expected %16.10g  diff %g\n",
                name, got, expected, diff);
        g_fail++;
    } else {
        g_pass++;
    }
}

/* ---- arccos -------------------------------------------------------------- */

static void test_arccos(void) {
    static const double data[][2] = {
        {-0.1, 1.6709637479564564156},
        { 0.0, 1.5707963267948966192},
        { 0.1, 1.4706289056333368229},
        { 0.2, 1.3694384060045658278},
        { 0.3, 1.2661036727794991113},
        { 0.4, 1.1592794807274085998},
        { 0.5, 1.0471975511965977462},
        { 0.6, 0.92729521800161223243},
        { 0.7, 0.79539883018414355549},
        { 0.8, 0.64350110879328438680},
        { 0.9, 0.45102681179626243254},
        { 1.0, 0.00000000000000000000},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = arccos_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "arccos(%.1f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- arcsin -------------------------------------------------------------- */

static void test_arcsin(void) {
    static const double data[][2] = {
        {-0.1, -0.10016742116155979635},
        { 0.0,  0.00000000000000000000},
        { 0.1,  0.10016742116155979635},
        { 0.2,  0.20135792079033079146},
        { 0.3,  0.30469265401539750797},
        { 0.4,  0.41151684606748801938},
        { 0.5,  0.52359877559829887308},
        { 0.6,  0.64350110879328438680},
        { 0.7,  0.77539749661075306374},
        { 0.8,  0.92729521800161223243},
        { 0.9,  1.1197695149986341867},
        { 1.0,  1.5707963267948966192},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = arcsin_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "arcsin(%.1f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- arctan -------------------------------------------------------------- */

static void test_arctan(void) {
    static const double data[][2] = {
        { 0.00, 0.00000000000000000000},
        { 0.25, 0.24497866312686415417},
        { 0.50, 0.46364760900080611621},
        { 1.00, 0.78539816339744830962},
        { 2.00, 1.1071487177940905030},
        { 3.00, 1.2490457723982544258},
        { 4.00, 1.3258176636680324651},
        { 5.00, 1.3734007669450158609},
        {10.00, 1.4711276743037345919},
        {20.00, 1.5208379310729538578},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double z = data[i][0];
        double result = arctan_cordic(1.0, z, N);
        char label[64];
        snprintf(label, sizeof(label), "arctan(%.2f)", z);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- cos ----------------------------------------------------------------- */

static void test_cos(void) {
    static const double data[][2] = {
        {0.0,                    1.0},
        {0.26179938779914943654, 0.96592582628906828675},
        {0.50000000000000000000, 0.87758256189037271612},
        {0.52359877559829887308, 0.86602540378443864676},
        {0.78539816339744830962, 0.70710678118654752440},
        {1.0,                    0.54030230586813971740},
        {1.0471975511965977462,  0.50000000000000000000},
        {1.5707963267948966192,  0.00000000000000000000},
        {2.0,                   -0.41614683654714238700},
        {3.0,                   -0.98999249660044545727},
        {4.0,                   -0.65364362086361191464},
        {5.0,                    0.28366218546322626447},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double c, s;
        cossin_cordic(data[i][0], N, &c, &s);
        char label[64];
        snprintf(label, sizeof(label), "cos(%.4f)", data[i][0]);
        check(label, c, data[i][1], ATOL);
    }
}

/* ---- sin ----------------------------------------------------------------- */

static void test_sin(void) {
    static const double data[][2] = {
        {0.0,                    0.00000000000000000000},
        {0.26179938779914943654, 0.25881904510252076235},
        {0.50000000000000000000, 0.47942553860420300027},
        {0.52359877559829887308, 0.50000000000000000000},
        {0.78539816339744830962, 0.70710678118654752440},
        {1.0,                    0.84147098480789650665},
        {1.0471975511965977462,  0.86602540378443864676},
        {1.5707963267948966192,  1.00000000000000000000},
        {2.0,                    0.90929742682568169540},
        {3.0,                    0.14112000805986722210},
        {4.0,                   -0.75680249530792825137},
        {5.0,                   -0.95892427466313846889},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double c, s;
        cossin_cordic(data[i][0], N, &c, &s);
        char label[64];
        snprintf(label, sizeof(label), "sin(%.4f)", data[i][0]);
        check(label, s, data[i][1], ATOL);
    }
}

/* ---- tan ----------------------------------------------------------------- */

static void test_tan(void) {
    static const double data[][2] = {
        {0.0,                    0.00000000000000000000},
        {0.26179938779914943654, 0.26794919243112270647},
        {0.50000000000000000000, 0.54630248984379051326},
        {0.52359877559829887308, 0.57735026918962576451},
        {0.78539816339744830962, 1.0000000000000000000},
        {1.0,                    1.5574077246549022305},
        {1.0471975511965977462,  1.7320508075688772935},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = tan_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "tan(%.4f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- exp ----------------------------------------------------------------- */

static void test_exp(void) {
    static const double data[][2] = {
        {-1.0, 0.36787944117144232160},
        { 0.0, 1.0},
        { 0.1, 1.1051709180756476248},
        { 0.5, 1.6487212707001281468},
        { 1.0, 2.7182818284590452354},
        { 2.0, 7.3890560989306502272},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = exp_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "exp(%.1f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- ln ------------------------------------------------------------------ */

static void test_ln(void) {
    static const double data[][2] = {
        {0.1,  -2.3025850929940456840},
        {0.5,  -0.69314718055994530942},
        {1.0,   0.0},
        {2.0,   0.69314718055994530942},
        {10.0,  2.3025850929940456840},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = ln_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "ln(%.1f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- sqrt ---------------------------------------------------------------- */

static void test_sqrt(void) {
    static const double data[][2] = {
        {0.0,                   0.0},
        {0.09,                  0.3},
        {0.1,                   0.3162277660168379},
        {1.0,                   1.0},
        {2.0,                   1.414213562373095},
        {3.0,                   1.732050807568877},
        {3.1415926535897932385,  1.772453850905516},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = sqrt_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "sqrt(%.4f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- cbrt ---------------------------------------------------------------- */

static void test_cbrt(void) {
    static const double data[][2] = {
        { 0.0,                    0.0},
        { 0.09,                   0.44814047465571647087},
        {-0.1,                   -0.46415888336127788924},
        { 2.0,                    1.2599210498948731648},
        {-3.0,                   -1.4422495703074083823},
        { 3.1415926535897932385,  1.4645918875615232630},
    };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    for (int i = 0; i < n; i++) {
        double result = cbrt_cordic(data[i][0], N);
        char label[64];
        snprintf(label, sizeof(label), "cbrt(%.4f)", data[i][0]);
        check(label, result, data[i][1], ATOL);
    }
}

/* ---- multiply ------------------------------------------------------------ */

static void test_multiply(void) {
    check("multiply(3,7)",   multiply_cordic(3.0, 7.0),   21.0, 1e-10);
    check("multiply(-4,5)",  multiply_cordic(-4.0, 5.0), -20.0, 1e-10);
    check("multiply(0,42)",  multiply_cordic(0.0, 42.0),   0.0, 1e-10);
}

/* ---- angle_shift --------------------------------------------------------- */

static void test_angle_shift(void) {
    double pi = 3.141592653589793;
    double result;

    result = angle_shift(7.0, 0.0);
    if (result < 0.0 || result >= 2.0 * pi) {
        fprintf(stderr, "FAIL  angle_shift(7,0) = %g not in [0, 2pi)\n", result);
        g_fail++;
    } else {
        g_pass++;
    }

    result = angle_shift(-1.0, 0.0);
    if (result < 0.0 || result >= 2.0 * pi) {
        fprintf(stderr, "FAIL  angle_shift(-1,0) = %g not in [0, 2pi)\n", result);
        g_fail++;
    } else {
        g_pass++;
    }
}

/* ---- main ---------------------------------------------------------------- */

int main(void) {
    printf("CORDIC CTest suite\n");
    printf("==================\n\n");

    test_arccos();
    test_arcsin();
    test_arctan();
    test_cos();
    test_sin();
    test_tan();
    test_exp();
    test_ln();
    test_sqrt();
    test_cbrt();
    test_multiply();
    test_angle_shift();

    printf("\n%d passed, %d failed\n", g_pass, g_fail);

    return g_fail > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
