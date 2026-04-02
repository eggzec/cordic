# Theory

## Overview

`cordic` implements the **CORDIC** (COordinate Rotation DIgital Computer)
algorithm, an iterative method for computing trigonometric, hyperbolic,
exponential, logarithmic, and root functions using only shifts, additions,
and a small look-up table. The algorithm is particularly well-suited for
hardware implementations and embedded systems where multiplier circuits are
expensive.

---

## Background: Elementary function evaluation

Computing elementary functions — $\sin$, $\cos$, $\exp$, $\ln$, $\sqrt{}$ —
is a fundamental requirement in scientific computing, signal processing, and
computer graphics. Classical approaches include:

- **Taylor / Maclaurin series** — converge slowly, require many multiplications
- **Chebyshev polynomials** — fast convergence but need multiplication
- **Table look-up with interpolation** — fast but memory-intensive
- **CORDIC** — uses only shifts and additions, ideal for hardware

CORDIC stands out because its core loop avoids multiplication entirely. Each
iteration performs a fixed sequence of shift, add/subtract, and table look-up
operations, making it particularly efficient on architectures without fast
multipliers.

---

## The CORDIC algorithm

### Rotation mode (vectoring and rotation)

The CORDIC algorithm operates by rotating a 2-D vector through a sequence of
progressively smaller angles. The key identity is that a rotation by angle
$\alpha_i = \arctan(2^{-i})$ can be performed without multiplication:

$$
\begin{bmatrix} x_{i+1} \\ y_{i+1} \end{bmatrix}
= \begin{bmatrix} 1 & -\sigma_i 2^{-i} \\ \sigma_i 2^{-i} & 1 \end{bmatrix}
\begin{bmatrix} x_i \\ y_i \end{bmatrix},
$$

where $\sigma_i \in \{-1, +1\}$ is the rotation direction chosen at each step.
The multiplication by $2^{-i}$ is implemented as a binary right-shift.

### Angle accumulator

A third variable $z_i$ tracks the accumulated angle:

$$
z_{i+1} = z_i - \sigma_i \arctan(2^{-i}).
$$

The values $\arctan(2^{-i})$ for $i = 0, 1, 2, \ldots$ are pre-computed and
stored in a small look-up table.

### Gain factor

Each pseudo-rotation introduces a scaling factor $K_i = \sqrt{1 + 2^{-2i}}$.
After $n$ iterations the accumulated gain is:

$$
K_n = \prod_{i=0}^{n-1} \sqrt{1 + 2^{-2i}} \approx 1.6468.
$$

This constant is pre-computed and divided out at the end. For large $n$, $K_n$
converges rapidly to the constant $K_\infty \approx 1.6468$.

### Two operating modes

| Mode | Direction rule | After $n$ iterations |
|---|---|---|
| **Rotation** | $\sigma_i = \operatorname{sign}(z_i)$ | $(x_n, y_n) \approx K_n(x_0\cos z_0 - y_0\sin z_0,\; x_0\sin z_0 + y_0\cos z_0)$ |
| **Vectoring** | $\sigma_i = -\operatorname{sign}(y_i)$ | $z_n \approx z_0 + \arctan(y_0/x_0)$, $x_n \approx K_n\sqrt{x_0^2 + y_0^2}$ |

**Rotation mode** drives $z_i \to 0$ and computes $\cos$ and $\sin$.
**Vectoring mode** drives $y_i \to 0$ and computes $\arctan$ and the vector
magnitude.

---

## Computing trigonometric functions

### Cosine and sine

To compute $\cos\theta$ and $\sin\theta$, initialize:

$$
x_0 = 1/K_n, \quad y_0 = 0, \quad z_0 = \theta,
$$

and run CORDIC in **rotation mode**. After $n$ iterations:

$$
x_n \approx \cos\theta, \quad y_n \approx \sin\theta.
$$

The input angle $\theta$ must lie in $[-\pi/2, \pi/2]$; angles outside this
range are first reduced using the identity $\cos(\theta \pm \pi) = -\cos\theta$.

### Tangent

Computed as $\tan\theta = \sin\theta / \cos\theta$ from the rotation-mode
outputs.

### Arctangent

Initialize $x_0 = 1$, $y_0 = t$, $z_0 = 0$ and run in **vectoring mode**.
The accumulated angle $z_n \approx \arctan(t)$.

### Arcsine and arccosine

Derived from $\arctan$ using the identities:

$$
\arcsin(t) = \arctan\!\left(\frac{t}{\sqrt{1-t^2}}\right), \quad
\arccos(t) = \frac{\pi}{2} - \arcsin(t).
$$

---

## Hyperbolic CORDIC

A variant of CORDIC replaces circular rotations with **hyperbolic rotations**
by using the identity $\tanh^{-1}(2^{-i})$ instead of $\arctan(2^{-i})$. The
iteration becomes:

$$
\begin{aligned}
x_{i+1} &= x_i + \sigma_i 2^{-i} y_i, \\
y_{i+1} &= y_i + \sigma_i 2^{-i} x_i, \\
z_{i+1} &= z_i - \sigma_i \tanh^{-1}(2^{-i}).
\end{aligned}
$$

!!! note "Repeated iterations"
    The hyperbolic CORDIC requires certain iterations to be repeated
    (at indices $i = 4, 13, 40, \ldots$) to guarantee convergence. This is
    because the hyperbolic arctangent values do not sum to cover the full
    range without repetition.

### Exponential function

To compute $e^t$, initialize $x_0 = 1$, $y_0 = 1$, $z_0 = t$ and run
hyperbolic CORDIC in rotation mode:

$$
x_n \approx K_h(\cosh t + \sinh t) = K_h e^t,
$$

where $K_h$ is the hyperbolic gain factor.

### Natural logarithm

To compute $\ln(t)$, initialize $x_0 = t + 1$, $y_0 = t - 1$, $z_0 = 0$
and run hyperbolic CORDIC in vectoring mode:

$$
z_n \approx \tanh^{-1}\!\left(\frac{t-1}{t+1}\right) = \frac{1}{2}\ln(t).
$$

---

## Square root and cube root

### Square root

The square root is computed using the identity:

$$
\sqrt{t} = \frac{t + 1/4}{\sqrt{t + 1/4}} \cdot \frac{1}{\sqrt{1}},
$$

combined with hyperbolic CORDIC vectoring to compute the magnitude
$\sqrt{x_0^2 - y_0^2}$.

### Cube root

The cube root uses iterative refinement based on Newton's method seeded by
a CORDIC-computed initial estimate:

$$
x_{k+1} = \frac{1}{3}\left(2x_k + \frac{t}{x_k^2}\right).
$$

---

## Convergence and accuracy

### Bits of accuracy

Each CORDIC iteration adds approximately one bit of accuracy to the result.
After $n$ iterations, the error is bounded by:

$$
|\epsilon| \le \arctan(2^{-n}) \approx 2^{-n} \text{ radians}.
$$

For the default $n = 25$ iterations, this gives roughly 25 bits of accuracy
($\approx 7.5$ decimal digits), which is sufficient for single-precision
floating point but not for full double-precision.

| Iterations $n$ | Approximate decimal digits |
|---|---|
| 10 | 3.0 |
| 15 | 4.5 |
| 20 | 6.0 |
| **25** (default) | **7.5** |
| 30 | 9.0 |
| 40 | 12.0 |
| 53 | 16.0 (double precision) |

!!! tip "Choosing the iteration count"
    The default `n=25` provides ≈7.5 decimal digits of accuracy, suitable
    for most applications. For full double-precision accuracy, use `n=53`.
    Increasing `n` adds negligible computational cost — each iteration is
    a single shift-and-add operation.

### Domain restrictions

| Function | Valid input domain |
|---|---|
| `cos`, `sin`, `tan` | Any real (reduced to $[-\pi, \pi]$ internally) |
| `arccos` | $[-1, 1]$ |
| `arcsin` | $[-1, 1]$ |
| `arctan` | Any real |
| `exp` | $\|t\| \lesssim 1.1182$ (hyperbolic CORDIC convergence range) |
| `ln` | $t > 0$ |
| `sqrt` | $t \ge 0$ |
| `cbrt` | Any real |
| `multiply` | Any real pair |

!!! warning "Exponential range"
    The hyperbolic CORDIC for `exp` converges only for
    $|t| \le \sum_{i=1}^{\infty} \tanh^{-1}(2^{-i}) \approx 1.1182$.
    The implementation extends the range using the identity
    $e^t = 2^k \cdot e^r$ where $r$ is in the convergence region.
