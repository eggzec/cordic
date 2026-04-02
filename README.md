# cordic

**CORDIC Algorithm for Python**

[![Tests](https://github.com/eggzec/cordic/actions/workflows/test.yml/badge.svg)](https://github.com/eggzec/cordic/actions/workflows/test.yml)
[![Documentation](https://github.com/eggzec/cordic/actions/workflows/docs.yml/badge.svg)](https://github.com/eggzec/cordic/actions/workflows/docs.yml)
[![Ruff](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/astral-sh/ruff/main/assets/badge/v2.json)](https://github.com/astral-sh/ruff)

[![codecov](https://codecov.io/github/eggzec/cordic/graph/badge.svg)](https://codecov.io/github/eggzec/cordic)
[![License: LGPL-2.1](https://img.shields.io/badge/License-LGPL--2.1-blue.svg)](LICENSE)

[![PyPI Downloads](https://img.shields.io/pypi/dm/cordic.svg?label=PyPI%20downloads)](https://pypi.org/project/cordic/)
[![Python versions](https://img.shields.io/pypi/pyversions/cordic.svg)](https://pypi.org/project/cordic/)

`cordic` is a high-performance Python library for evaluating trigonometric,
hyperbolic, exponential, logarithmic, and root functions using the
[CORDIC](https://en.wikipedia.org/wiki/CORDIC) (COordinate Rotation DIgital
Computer) algorithm — an iterative method that uses only shifts, additions,
and a small look-up table.

## Quick example

```python
import cordic

print(cordic.cos(1.0))  # ≈ 0.5403
print(cordic.exp(1.0))  # ≈ 2.7183
print(cordic.sqrt(2.0))  # ≈ 1.4142
print(cordic.arctan(1.0))  # ≈ 0.7854
```

## Installation

```bash
pip install cordic
```

Requires Python 3.10+ and NumPy. See the
[full installation guide](https://eggzec.github.io/cordic/installation/) for
uv, poetry, and source builds.

## Documentation

- [Theory](https://eggzec.github.io/cordic/theory/) — CORDIC algorithm, rotation modes, convergence
- [Quickstart](https://eggzec.github.io/cordic/quickstart/) — runnable examples
- [API Reference](https://eggzec.github.io/cordic/api/) — function signatures and parameters
- [References](https://eggzec.github.io/cordic/references/) — literature citations

## Routines

| Function | Description |
|---|---|
| `arccos(t, n)` | Arccosine via CORDIC |
| `arcsin(t, n)` | Arcsine via CORDIC |
| `arctan(t, n)` | Arctangent via CORDIC |
| `cos(a, n)` | Cosine via CORDIC |
| `sin(a, n)` | Sine via CORDIC |
| `tan(a, n)` | Tangent via CORDIC |
| `exp(t, n)` | Exponential via CORDIC |
| `ln(t, n)` | Natural logarithm via CORDIC |
| `sqrt(t, n)` | Square root via CORDIC |
| `cbrt(t, n)` | Cube root via CORDIC |
| `multiply(x, y, n)` | Multiplication via CORDIC shift-and-add |
| `angle_shift(alpha, beta)` | Shift angle into $[\beta,\, \beta + 2\pi)$ |

All functions accept an optional iteration count `n` (default 25).

## References

- Pitts Jarvis, "Implementing CORDIC Algorithms," *Dr. Dobb's Journal*, October 1990.
- Jean-Michel Muller, *Elementary Functions: Algorithms and Implementation*, Second Edition, Birkhäuser, 2006, ISBN 978-0-8176-4372-0.
- Allan Sultan, "CORDIC: How Hand Calculators Calculate," *The College Mathematics Journal*, 40(2), 87–92, March 2009.
- Jack Volder, "The CORDIC Computing Technique," *IRE Transactions on Electronic Computers*, 8(3), 330–334, 1959.
- Jack Volder, "The Birth of CORDIC," *Journal of VLSI Signal Processing Systems*, 25(2), 101–105, June 2000.
- Anthony Williams, "Optimizing Math-Intensive Applications with Fixed-Point Arithmetic," *Dr. Dobb's Journal*, 33(4), 38–43, April 2008.

## Attribution

The original C library was written by
[John Burkardt](https://people.math.sc.edu/Burkardt/c_src/cordic/cordic.html)
and is distributed under the LGPL-2.1 license.

## License

LGPL-2.1 — see [LICENSE](LICENSE).
