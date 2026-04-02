# Quickstart

This page walks through progressively richer examples of using `cordic`.
Each example is self-contained and can be pasted directly into a Python script
or interactive session. For mathematical background, see the [Theory](theory.md) section.

---

## Basic trigonometry

Compute cosine, sine, and tangent of an angle in radians:

```python
import cordic

print(cordic.cos(1.0))  # ≈ 0.5403
print(cordic.sin(1.0))  # ≈ 0.8415
print(cordic.tan(1.0))  # ≈ 1.5574
```

## Inverse trigonometric functions

Recover angles from trigonometric values:

```python
import math
import cordic

print(cordic.arccos(0.5))  # ≈ π/3 ≈ 1.0472
print(cordic.arcsin(0.5))  # ≈ π/6 ≈ 0.5236
print(cordic.arctan(1.0))  # ≈ π/4 ≈ 0.7854
```

## Exponential and logarithm

```python
import cordic

print(cordic.exp(1.0))  # ≈ e ≈ 2.7183
print(cordic.exp(0.0))  # = 1.0
print(cordic.ln(1.0))  # = 0.0
print(cordic.ln(2.718281828))  # ≈ 1.0
```

## Square root and cube root

```python
import cordic

print(cordic.sqrt(2.0))  # ≈ 1.4142
print(cordic.sqrt(9.0))  # ≈ 3.0
print(cordic.cbrt(27.0))  # ≈ 3.0
print(cordic.cbrt(-8.0))  # ≈ -2.0
```

## Multiplication without a multiplier

CORDIC can multiply two numbers using only shift-and-add operations:

```python
import cordic

print(cordic.multiply(3.0, 4.0))  # ≈ 12.0
print(cordic.multiply(-2.5, 6.0))  # ≈ -15.0
```

## Angle normalization

Shift an angle into the interval $[\beta, \beta + 2\pi)$:

```python
import math
import cordic

# Shift 7.0 radians into [0, 2π)
print(cordic.angle_shift(7.0, 0.0))  # ≈ 0.7168

# Shift into [-π, π)
print(cordic.angle_shift(7.0, -math.pi))  # ≈ 0.7168
```

## Controlling accuracy with iteration count

All functions accept an optional `n` parameter controlling the number of
CORDIC iterations. More iterations yield higher accuracy at negligible cost:

```python
import math
import cordic

exact = math.cos(1.0)

for n in [5, 10, 15, 20, 25, 30]:
    approx = cordic.cos(1.0, n=n)
    error = abs(approx - exact)
    print(f"n={n:2d}  cos(1.0)={approx:.12f}  error={error:.2e}")
```

## Comparing with the standard library

```python
import math
import cordic

angles = [0.0, 0.5, 1.0, 1.5]

print(f"{'angle':>8s}  {'cordic.cos':>12s}  {'math.cos':>12s}  {'error':>10s}")
for a in angles:
    c = cordic.cos(a)
    m = math.cos(a)
    print(f"{a:8.4f}  {c:12.8f}  {m:12.8f}  {abs(c - m):10.2e}")
```

## Verifying identities

Use CORDIC functions to check well-known trigonometric identities:

```python
import cordic

# sin²(x) + cos²(x) = 1
x = 0.7
s = cordic.sin(x)
c = cordic.cos(x)
print(f"sin²({x}) + cos²({x}) = {s**2 + c**2:.10f}")

# exp(ln(x)) = x
t = 2.5
print(f"exp(ln({t})) = {cordic.exp(cordic.ln(t)):.10f}")

# sqrt(x)² = x
print(f"sqrt(3)² = {cordic.sqrt(3.0) ** 2:.10f}")
```

## Tips

!!! tip "Default accuracy"
    The default `n=25` iterations gives ≈7.5 decimal digits of accuracy.
    For most applications this is more than sufficient. Increase to `n=53`
    if you need full double-precision accuracy.

!!! tip "Performance"
    Each CORDIC iteration is a single shift-and-add: increasing `n` from 25
    to 53 roughly doubles the work but still completes in microseconds.

!!! tip "Lambda-style usage"
    All `cordic` functions work as callbacks:

    ```python
    import cordic

    angles = [0.1, 0.5, 1.0, 1.5]
    cosines = list(map(cordic.cos, angles))
    ```
