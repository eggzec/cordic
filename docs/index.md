# cordic

**CORDIC Algorithm for Python**

---

## Overview

`cordic` is a Python library for evaluating trigonometric, hyperbolic,
exponential, logarithmic, and root functions using the
[CORDIC](https://en.wikipedia.org/wiki/CORDIC) (COordinate Rotation DIgital
Computer) algorithm. CORDIC is an iterative method that computes these
functions using only **shifts**, **additions**, and a small **look-up table**
— no multiplications or divisions are needed in the core loop.

Originally developed by Jack Volder in 1959 for real-time navigation computers,
CORDIC became the standard algorithm in pocket calculators and embedded systems
where hardware multipliers were expensive or unavailable. The algorithm remains
relevant today in FPGA and DSP designs where area and power constraints make
dedicated multipliers impractical.

All functions accept an iteration count $n$ that controls the trade-off
between speed and accuracy — each additional iteration roughly doubles the
number of correct bits in the result.

## Requirements

- [NumPy](http://www.numpy.org/)

## Example Usage

```python
import cordic

# Trigonometric functions
print(cordic.cos(1.0))  # ≈ 0.5403
print(cordic.sin(1.0))  # ≈ 0.8415
print(cordic.tan(0.7854))  # ≈ 1.0000

# Inverse trigonometric functions
print(cordic.arccos(0.5))  # ≈ 1.0472
print(cordic.arcsin(0.5))  # ≈ 0.5236
print(cordic.arctan(1.0))  # ≈ 0.7854

# Exponential and logarithmic functions
print(cordic.exp(1.0))  # ≈ 2.7183
print(cordic.ln(2.718281828))  # ≈ 1.0000

# Root functions
print(cordic.sqrt(2.0))  # ≈ 1.4142
print(cordic.cbrt(27.0))  # ≈ 3.0000

# Multiplication via shift-and-add
print(cordic.multiply(3.0, 4.0))  # ≈ 12.0

# Angle normalization
print(cordic.angle_shift(7.0, 0.0))  # shift into [0, 2π)
```

## Main Features

1. **Trigonometric functions** — `cos`, `sin`, `tan` and their inverses `arccos`, `arcsin`, `arctan`.
2. **Exponential and logarithmic** — `exp` and `ln` via hyperbolic CORDIC rotations.
3. **Root functions** — `sqrt` and `cbrt` using CORDIC-based iterative refinement.
4. **Shift-and-add multiplication** — `multiply` without hardware multiplier.
5. **Angle normalization** — `angle_shift` to map angles into any $2\pi$-wide interval.
6. Configurable iteration count `n` for speed/accuracy trade-off.

## See Also

- [NumPy](http://www.numpy.org/): Array library providing the numerical foundation
- [SciPy](http://scipy.org): General scientific computing — complements `cordic` for higher-level numerical work
- [CORDIC C library](https://people.math.sc.edu/Burkardt/c_src/cordic/cordic.html): The original C implementation by John Burkardt

## Acknowledgements

The author thanks [John Burkardt](https://people.math.sc.edu/Burkardt/c_src/cordic/cordic.html)
for the original CORDIC C library, which provides the numerical core of this
package.

## References

- Jarvis, P., "Implementing CORDIC Algorithms," *Dr. Dobb's Journal*, October 1990.
- Muller, J.-M., *Elementary Functions: Algorithms and Implementation*, Second Edition, Birkhäuser, 2006, ISBN 978-0-8176-4372-0.
- Sultan, A., "CORDIC: How Hand Calculators Calculate," *The College Mathematics Journal*, 40(2), 87–92, March 2009.
- Volder, J., "The CORDIC Computing Technique," *IRE Transactions on Electronic Computers*, 8(3), 330–334, 1959.
- Volder, J., "The Birth of CORDIC," *Journal of VLSI Signal Processing Systems*, 25(2), 101–105, June 2000.
- Williams, A., "Optimizing Math-Intensive Applications with Fixed-Point Arithmetic," *Dr. Dobb's Journal*, 33(4), 38–43, April 2008.
