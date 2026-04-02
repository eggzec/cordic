"""CORDIC — COordinate Rotation DIgital Computer.

An iterative algorithm for evaluating trigonometric, hyperbolic,
exponential, logarithmic, and square-root functions using only
shifts, additions, and a small look-up table.

Functions
---------
* :func:`arccos` — inverse cosine via CORDIC
* :func:`arcsin` — inverse sine via CORDIC
* :func:`arctan` — inverse tangent via CORDIC
* :func:`cos` — cosine via CORDIC
* :func:`sin` — sine via CORDIC
* :func:`tan` — tangent via CORDIC
* :func:`exp` — exponential via CORDIC
* :func:`ln` — natural logarithm via CORDIC
* :func:`sqrt` — square root via CORDIC
* :func:`cbrt` — cube root via CORDIC
* :func:`multiply` — multiplication via CORDIC shift-and-add
* :func:`angle_shift` — shift angle into [beta, beta+2π)

Example
-------
>>> import cordic
>>> cordic.cos(1.0)  # ≈ 0.5403...
"""

from ._cordic import angle_shift
from ._cordic import arccos_cordic as _arccos
from ._cordic import arcsin_cordic as _arcsin
from ._cordic import arctan_cordic as _arctan
from ._cordic import cbrt_cordic as _cbrt
from ._cordic import cos_cordic as _cos
from ._cordic import exp_cordic as _exp
from ._cordic import ln_cordic as _ln
from ._cordic import multiply_cordic as _multiply
from ._cordic import sin_cordic as _sin
from ._cordic import sqrt_cordic as _sqrt
from ._cordic import tan_cordic as _tan


_DEFAULT_N = 25


def arccos(t: float, n: int = _DEFAULT_N) -> float:
    """Return the arccosine of *t* using the CORDIC algorithm.

    Parameters
    ----------
    t : float
        Cosine value, must satisfy -1 <= *t* <= 1.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Angle in radians whose cosine is *t*.
    """
    return _arccos(t, n)


def arcsin(t: float, n: int = _DEFAULT_N) -> float:
    """Return the arcsine of *t* using the CORDIC algorithm.

    Parameters
    ----------
    t : float
        Sine value, must satisfy -1 <= *t* <= 1.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Angle in radians whose sine is *t*.
    """
    return _arcsin(t, n)


def arctan(x: float, y: float = 1.0, n: int = _DEFAULT_N) -> float:
    """Return the arctangent of *y*/*x* using the CORDIC algorithm.

    Parameters
    ----------
    x : float
        X-component.
    y : float, optional
        Y-component (default 1.0).
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Angle in radians whose tangent is *y*/*x*.
    """
    return _arctan(x, y, n)


def cos(beta: float, n: int = _DEFAULT_N) -> float:
    """Return the cosine of *beta* (radians) using the CORDIC algorithm.

    Parameters
    ----------
    beta : float
        Angle in radians.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Cosine of *beta*.
    """
    return _cos(beta, n)


def sin(beta: float, n: int = _DEFAULT_N) -> float:
    """Return the sine of *beta* (radians) using the CORDIC algorithm.

    Parameters
    ----------
    beta : float
        Angle in radians.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Sine of *beta*.
    """
    return _sin(beta, n)


def tan(beta: float, n: int = _DEFAULT_N) -> float:
    """Return the tangent of *beta* (radians) using the CORDIC algorithm.

    Parameters
    ----------
    beta : float
        Angle in radians.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Tangent of *beta*.
    """
    return _tan(beta, n)


def exp(x: float, n: int = _DEFAULT_N) -> float:
    r"""Return e\ :sup:`x` using the CORDIC algorithm.

    Parameters
    ----------
    x : float
        Exponent.
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Approximate value of e\ :sup:`x`.
    """
    return _exp(x, n)


def ln(x: float, n: int = _DEFAULT_N) -> float:
    """Return the natural logarithm of *x* using the CORDIC algorithm.

    Parameters
    ----------
    x : float
        Input value (must be > 0).
    n : int, optional
        Number of CORDIC iterations (default 25).

    Returns
    -------
    float
        Approximate value of ln(*x*).
    """
    return _ln(x, n)


def sqrt(x: float, n: int = _DEFAULT_N) -> float:
    """Return the square root of *x* using the CORDIC algorithm.

    Parameters
    ----------
    x : float
        Non-negative input value.
    n : int, optional
        Number of binary-search iterations (default 25).

    Returns
    -------
    float
        Approximate square root of *x*.
    """
    return _sqrt(x, n)


def cbrt(x: float, n: int = _DEFAULT_N) -> float:
    """Return the cube root of *x* using the CORDIC algorithm.

    Parameters
    ----------
    x : float
        Input value.
    n : int, optional
        Number of binary-search iterations (default 25).

    Returns
    -------
    float
        Approximate cube root of *x*.
    """
    return _cbrt(x, n)


def multiply(x: float, y: float) -> float:
    """Multiply *x* and *y* using CORDIC shift-and-add.

    Parameters
    ----------
    x : float
        First factor.
    y : float
        Second factor.

    Returns
    -------
    float
        Product *x* x *y*.
    """
    return _multiply(x, y)


__all__ = [
    "angle_shift",
    "arccos",
    "arcsin",
    "arctan",
    "cbrt",
    "cos",
    "exp",
    "ln",
    "multiply",
    "sin",
    "sqrt",
    "tan",
]
