"""Pytest tests for the cordic Python package.

Test data is derived from the tabulated values in the legacy C test
suite (bin/legacy/cordic_test.c) and the reference output
(bin/legacy/cordic_test.txt).  At n=25 iterations the CORDIC results
agree with the tabulated mathematics-library values to roughly 1e-7.
"""

import math

import pytest

import cordic


# ---------------------------------------------------------------------------
# Tolerance: at n=25, legacy tests show differences of ~1e-7 or better.
# ---------------------------------------------------------------------------
ATOL = 1.0e-6
N = 25


# ---- arccos ---------------------------------------------------------------

ARCCOS_DATA = [
    (-0.1, 1.6709637479564564156),
    (0.0, 1.5707963267948966192),
    (0.1, 1.4706289056333368229),
    (0.2, 1.3694384060045658278),
    (0.3, 1.2661036727794991113),
    (0.4, 1.1592794807274085998),
    (0.5, 1.0471975511965977462),
    (0.6, 0.92729521800161223243),
    (0.7, 0.79539883018414355549),
    (0.8, 0.64350110879328438680),
    (0.9, 0.45102681179626243254),
    (1.0, 0.00000000000000000000),
]


@pytest.mark.parametrize("t, expected", ARCCOS_DATA)
def test_arccos(t: float, expected: float) -> None:
    """Arccosine via CORDIC matches tabulated values."""
    assert cordic.arccos(t, N) == pytest.approx(expected, abs=ATOL)


# ---- arcsin ---------------------------------------------------------------

ARCSIN_DATA = [
    (-0.1, -0.10016742116155979635),
    (0.0, 0.00000000000000000000),
    (0.1, 0.10016742116155979635),
    (0.2, 0.20135792079033079146),
    (0.3, 0.30469265401539750797),
    (0.4, 0.41151684606748801938),
    (0.5, 0.52359877559829887308),
    (0.6, 0.64350110879328438680),
    (0.7, 0.77539749661075306374),
    (0.8, 0.92729521800161223243),
    (0.9, 1.1197695149986341867),
    (1.0, 1.5707963267948966192),
]


@pytest.mark.parametrize("t, expected", ARCSIN_DATA)
def test_arcsin(t: float, expected: float) -> None:
    """Arcsine via CORDIC matches tabulated values."""
    assert cordic.arcsin(t, N) == pytest.approx(expected, abs=ATOL)


# ---- arctan ---------------------------------------------------------------

ARCTAN_DATA = [
    (0.0, 0.00000000000000000000),
    (0.25, 0.24497866312686415417),
    (1.0 / 3.0, 0.32175055439664219340),
    (0.5, 0.46364760900080611621),
    (1.0, 0.78539816339744830962),
    (2.0, 1.1071487177940905030),
    (3.0, 1.2490457723982544258),
    (4.0, 1.3258176636680324651),
    (5.0, 1.3734007669450158609),
    (10.0, 1.4711276743037345919),
    (20.0, 1.5208379310729538578),
]


@pytest.mark.parametrize("z, expected", ARCTAN_DATA)
def test_arctan(z: float, expected: float) -> None:
    """Arctangent via CORDIC matches tabulated values."""
    result = cordic.arctan(1.0, z, N)
    assert result == pytest.approx(expected, abs=ATOL)


# ---- cos ------------------------------------------------------------------

COS_DATA = [
    (0.0, 1.0),
    (0.26179938779914943654, 0.96592582628906828675),
    (0.50000000000000000000, 0.87758256189037271612),
    (0.52359877559829887308, 0.86602540378443864676),
    (0.78539816339744830962, 0.70710678118654752440),
    (1.0, 0.54030230586813971740),
    (1.0471975511965977462, 0.50000000000000000000),
    (1.5707963267948966192, 0.00000000000000000000),
    (2.0, -0.41614683654714238700),
    (3.0, -0.98999249660044545727),
    (math.pi, -1.0),
    (4.0, -0.65364362086361191464),
    (5.0, 0.28366218546322626447),
]


@pytest.mark.parametrize("angle, expected", COS_DATA)
def test_cos(angle: float, expected: float) -> None:
    """Cosine via CORDIC matches tabulated values."""
    assert cordic.cos(angle, N) == pytest.approx(expected, abs=ATOL)


# ---- sin ------------------------------------------------------------------

SIN_DATA = [
    (0.0, 0.00000000000000000000),
    (0.26179938779914943654, 0.25881904510252076235),
    (0.50000000000000000000, 0.47942553860420300027),
    (0.52359877559829887308, 0.50000000000000000000),
    (0.78539816339744830962, 0.70710678118654752440),
    (1.0, 0.84147098480789650665),
    (1.0471975511965977462, 0.86602540378443864676),
    (1.5707963267948966192, 1.00000000000000000000),
    (2.0, 0.90929742682568169540),
    (3.0, 0.14112000805986722210),
    (math.pi, 0.00000000000000000000),
    (4.0, -0.75680249530792825137),
    (5.0, -0.95892427466313846889),
]


@pytest.mark.parametrize("angle, expected", SIN_DATA)
def test_sin(angle: float, expected: float) -> None:
    """Sine via CORDIC matches tabulated values."""
    assert cordic.sin(angle, N) == pytest.approx(expected, abs=ATOL)


# ---- tan ------------------------------------------------------------------

TAN_DATA = [
    (0.0, 0.00000000000000000000),
    (0.26179938779914943654, 0.26794919243112270647),
    (0.50000000000000000000, 0.54630248984379051326),
    (0.52359877559829887308, 0.57735026918962576451),
    (0.78539816339744830962, 1.0000000000000000000),
    (1.0, 1.5574077246549022305),
    (1.0471975511965977462, 1.7320508075688772935),
]


@pytest.mark.parametrize("angle, expected", TAN_DATA)
def test_tan(angle: float, expected: float) -> None:
    """Tangent via CORDIC matches tabulated values."""
    assert cordic.tan(angle, N) == pytest.approx(expected, abs=ATOL)


# ---- exp ------------------------------------------------------------------

EXP_DATA = [
    (-1.0, 0.36787944117144232160),
    (0.0, 1.0),
    (0.1, 1.1051709180756476248),
    (0.5, 1.6487212707001281468),
    (1.0, 2.7182818284590452354),
    (2.0, 7.3890560989306502272),
]


@pytest.mark.parametrize("x, expected", EXP_DATA)
def test_exp(x: float, expected: float) -> None:
    """Exponential via CORDIC matches tabulated values."""
    assert cordic.exp(x, N) == pytest.approx(expected, abs=ATOL)


# ---- ln -------------------------------------------------------------------

LN_DATA = [
    (0.1, -2.3025850929940456840),
    (0.5, -0.69314718055994530942),
    (1.0, 0.0),
    (2.0, 0.69314718055994530942),
    (math.e, 1.0),
    (10.0, 2.3025850929940456840),
]


@pytest.mark.parametrize("x, expected", LN_DATA)
def test_ln(x: float, expected: float) -> None:
    """Natural logarithm via CORDIC matches tabulated values."""
    assert cordic.ln(x, N) == pytest.approx(expected, abs=ATOL)


# ---- sqrt -----------------------------------------------------------------

SQRT_DATA = [
    (0.0, 0.0),
    (0.09, 0.3),
    (0.1, 0.3162277660168379),
    (1.0, 1.0),
    (2.0, 1.414213562373095),
    (3.0, 1.732050807568877),
    (math.pi, 1.772453850905516),
]


@pytest.mark.parametrize("x, expected", SQRT_DATA)
def test_sqrt(x: float, expected: float) -> None:
    """Square root via CORDIC matches tabulated values."""
    assert cordic.sqrt(x, N) == pytest.approx(expected, abs=ATOL)


# ---- cbrt -----------------------------------------------------------------

CBRT_DATA = [
    (0.0, 0.0),
    (0.09, 0.44814047465571647087),
    (-0.1, -0.46415888336127788924),
    (2.0, 1.2599210498948731648),
    (-3.0, -1.4422495703074083823),
    (math.pi, 1.4645918875615232630),
]


@pytest.mark.parametrize("x, expected", CBRT_DATA)
def test_cbrt(x: float, expected: float) -> None:
    """Cube root via CORDIC matches tabulated values."""
    assert cordic.cbrt(x, N) == pytest.approx(expected, abs=ATOL)


# ---- multiply -------------------------------------------------------------


def test_multiply_basic() -> None:
    """CORDIC multiplication matches standard multiplication."""
    assert cordic.multiply(3.0, 7.0) == pytest.approx(21.0)


def test_multiply_negative() -> None:
    """CORDIC multiplication handles negative operands."""
    assert cordic.multiply(-4.0, 5.0) == pytest.approx(-20.0)


def test_multiply_zero() -> None:
    """CORDIC multiplication with zero returns zero."""
    assert cordic.multiply(0.0, 42.0) == pytest.approx(0.0)


# ---- angle_shift ----------------------------------------------------------


def test_angle_shift_basic() -> None:
    """angle_shift brings angle into [beta, beta+2pi)."""
    result = cordic.angle_shift(7.0, 0.0)
    assert 0.0 <= result < 2.0 * math.pi
    assert math.cos(result) == pytest.approx(math.cos(7.0), abs=1e-12)


def test_angle_shift_negative() -> None:
    """angle_shift handles negative angles."""
    result = cordic.angle_shift(-1.0, 0.0)
    assert 0.0 <= result < 2.0 * math.pi
    assert math.sin(result) == pytest.approx(math.sin(-1.0), abs=1e-12)
