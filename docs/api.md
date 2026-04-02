# API Reference

`cordic` provides a Python interface to the CORDIC C library (Burkardt, 2017)
for evaluating elementary mathematical functions. The numerical core is
implemented in C and compiled via `f2py`, providing near-native performance
with a clean Python interface. See the [Theory](theory.md) and
[Quickstart](quickstart.md) for mathematical background and usage examples.

---

## Main Features

- Trigonometric functions: `cos`, `sin`, `tan`, `arccos`, `arcsin`, `arctan`
- Exponential and logarithmic: `exp`, `ln`
- Root functions: `sqrt`, `cbrt`
- Shift-and-add multiplication: `multiply`
- Angle normalization: `angle_shift`
- Configurable iteration count for speed/accuracy trade-off

## Function Summary

| Function | Category | Computes |
|---|---|---|
| `cos(beta, n)` | Trigonometric | $\cos(\beta)$ |
| `sin(beta, n)` | Trigonometric | $\sin(\beta)$ |
| `tan(beta, n)` | Trigonometric | $\tan(\beta)$ |
| `arccos(t, n)` | Inverse trig | $\cos^{-1}(t)$ |
| `arcsin(t, n)` | Inverse trig | $\sin^{-1}(t)$ |
| `arctan(x, y, n)` | Inverse trig | $\tan^{-1}(y/x)$ |
| `exp(x, n)` | Exponential | $e^x$ |
| `ln(x, n)` | Logarithmic | $\ln(x)$ |
| `sqrt(x, n)` | Root | $\sqrt{x}$ |
| `cbrt(x, n)` | Root | $\sqrt[3]{x}$ |
| `multiply(x, y)` | Arithmetic | $x \times y$ |
| `angle_shift(alpha, beta)` | Utility | Shift $\alpha$ into $[\beta, \beta+2\pi)$ |

---

## Common interface

Most functions share the same calling convention: a primary input value and
an optional iteration count `n`.

### The iteration parameter `n`

| Argument | Type | Description |
|---|---|---|
| `n` | `int` | Number of CORDIC iterations. Default: 25. Higher values give more accuracy. |

Each iteration adds ≈1 bit of accuracy. The default `n=25` provides ≈7.5
decimal digits. Use `n=53` for full double-precision accuracy.

!!! tip "Performance"
    Each iteration is a single shift-and-add operation. Increasing `n` from
    25 to 53 roughly doubles the work but still completes in microseconds.

---

## `cos(beta, n=25)`

Return the cosine of *beta* (radians) using the CORDIC rotation mode.

| Parameter | Type | Description |
|---|---|---|
| `beta` | `float` | Angle in radians |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\cos(\beta)$ |

```python
import cordic

cordic.cos(0.0)  # 1.0
cordic.cos(3.14159)  # ≈ -1.0
```

---

## `sin(beta, n=25)`

Return the sine of *beta* (radians) using the CORDIC rotation mode.

| Parameter | Type | Description |
|---|---|---|
| `beta` | `float` | Angle in radians |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\sin(\beta)$ |

```python
import cordic

cordic.sin(0.0)  # 0.0
cordic.sin(1.5707963)  # ≈ 1.0
```

---

## `tan(beta, n=25)`

Return the tangent of *beta* (radians) using the CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `beta` | `float` | Angle in radians |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\tan(\beta)$ |

```python
import cordic

cordic.tan(0.7854)  # ≈ 1.0
```

---

## `arccos(t, n=25)`

Return the arccosine of *t* using the CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `t` | `float` | Cosine value, must satisfy $-1 \le t \le 1$ |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | Angle in radians whose cosine is $t$ |

```python
import cordic

cordic.arccos(0.5)  # ≈ π/3 ≈ 1.0472
cordic.arccos(1.0)  # ≈ 0.0
```

---

## `arcsin(t, n=25)`

Return the arcsine of *t* using the CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `t` | `float` | Sine value, must satisfy $-1 \le t \le 1$ |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | Angle in radians whose sine is $t$ |

```python
import cordic

cordic.arcsin(0.5)  # ≈ π/6 ≈ 0.5236
cordic.arcsin(1.0)  # ≈ π/2 ≈ 1.5708
```

---

## `arctan(x, y=1.0, n=25)`

Return the arctangent of *y*/*x* using the CORDIC vectoring mode.

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | X-component |
| `y` | `float` | Y-component (default 1.0) |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | Angle in radians whose tangent is $y/x$ |

```python
import cordic

cordic.arctan(1.0)  # ≈ π/4 ≈ 0.7854
cordic.arctan(1.0, 1.0)  # ≈ π/4 ≈ 0.7854
```

---

## `exp(x, n=25)`

Return $e^x$ using the hyperbolic CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | Exponent |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $e^x$ |

```python
import cordic

cordic.exp(0.0)  # 1.0
cordic.exp(1.0)  # ≈ 2.7183
```

---

## `ln(x, n=25)`

Return the natural logarithm of *x* using the hyperbolic CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | Input value (must be $> 0$) |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\ln(x)$ |

```python
import cordic

cordic.ln(1.0)  # 0.0
cordic.ln(2.718281828)  # ≈ 1.0
```

---

## `sqrt(x, n=25)`

Return the square root of *x* using the CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | Non-negative input value |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\sqrt{x}$ |

```python
import cordic

cordic.sqrt(4.0)  # ≈ 2.0
cordic.sqrt(2.0)  # ≈ 1.4142
```

---

## `cbrt(x, n=25)`

Return the cube root of *x* using the CORDIC algorithm.

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | Input value (any real number) |
| `n` | `int` | Number of iterations (default 25) |
| **return** | `float` | $\sqrt[3]{x}$ |

```python
import cordic

cordic.cbrt(27.0)  # ≈ 3.0
cordic.cbrt(-8.0)  # ≈ -2.0
```

---

## `multiply(x, y)`

Multiply *x* and *y* using CORDIC shift-and-add (no hardware multiplier).

| Parameter | Type | Description |
|---|---|---|
| `x` | `float` | First factor |
| `y` | `float` | Second factor |
| **return** | `float` | $x \times y$ |

!!! note "No iteration parameter"
    `multiply` does not accept an `n` parameter — the number of iterations
    is determined internally by the bit width of the operands.

```python
import cordic

cordic.multiply(3.0, 4.0)  # ≈ 12.0
```

---

## `angle_shift(alpha, beta)`

Shift angle *alpha* into the interval $[\beta, \beta + 2\pi)$.

| Parameter | Type | Description |
|---|---|---|
| `alpha` | `float` | Angle to shift (radians) |
| `beta` | `float` | Lower bound of target interval (radians) |
| **return** | `float` | Equivalent angle in $[\beta, \beta + 2\pi)$ |

```python
import math
import cordic

cordic.angle_shift(7.0, 0.0)  # ≈ 0.7168
cordic.angle_shift(7.0, -math.pi)  # ≈ 0.7168
```

---

## C Library Routines

The underlying C library exposes additional helper functions not wrapped in
the Python interface:

| Routine | Description |
|---|---|
| `angle_shift` | Shifts angle $\alpha$ to lie between $\beta$ and $\beta + 2\pi$ |
| `arccos_cordic` | Arccosine via CORDIC |
| `arccos_values` | Tabulated arccosine reference values |
| `arcsin_cordic` | Arcsine via CORDIC |
| `arcsin_values` | Tabulated arcsine reference values |
| `arctan_cordic` | Arctangent via CORDIC |
| `arctan_values` | Tabulated arctangent reference values |
| `cbrt_cordic` | Cube root via CORDIC |
| `cbrt_values` | Tabulated cube root reference values |
| `cos_values` | Tabulated cosine reference values |
| `cossin_cordic` | Simultaneous cosine and sine via CORDIC |
| `exp_cordic` | Exponential via CORDIC |
| `exp_values` | Tabulated exponential reference values |
| `i4_huge` | Returns a large integer constant |
| `i4_min` | Returns the minimum of two integers |
| `ln_cordic` | Natural logarithm via CORDIC |
| `ln_values` | Tabulated logarithm reference values |
| `r8_uniform_01` | Unit pseudorandom number generator |
| `sin_values` | Tabulated sine reference values |
| `sqrt_cordic` | Square root via CORDIC |
| `sqrt_values` | Tabulated square root reference values |
| `tan_cordic` | Tangent via CORDIC |
| `tan_values` | Tabulated tangent reference values |
| `timestamp` | Prints current date/time stamp |
