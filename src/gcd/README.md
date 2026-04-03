# Monte Carlo: Random GCD Method (C++11)

## Overview

This project estimates the value of $\pi$ using a surprising result from number theory: the probability that two randomly chosen integers are **coprime** (share no common factor) is exactly $6 / \pi^2$. By sampling millions of random pairs and measuring how often their GCD equals 1, we can back out an approximation of thi fundamental mathematical constant.

This method belongs to the family of **Monte Carlo estimators** (check the Overview in the README for the _Circle method_ if you need a deeper explanation)- it is simple and requires no mathematical libraries beyond a GCD function.

The implementation targets **C++11** and has no external dependencies.

---

## Model

For two integers *a* and *b* drawn uniformly at random, the probability that they are coprime is:

$$P(\gcd(a, b) = 1) = \frac{6}{\pi^2} = \prod_{p \text{ prime}} \left(1 - \frac{1}{p^2}\right)$$

This follows from the Euler product formula applied to the Riemann zeta function at $s = 2$. The key identity is $\xi(2) = \pi^2 / 6, and the probability of two integers sharing no prime factor $p$ is $(1 − 1/p^2)$, so multiplying over all primes gives $6 / \pi^2$.

In practice, after *N* trials with *N*_coprime coprime pairs observed, we estimate $\pi$ as:

$$\hat{\pi} = \sqrt{\frac{6 \cdot N}{N_{\text{coprime}}}}$$

**Convergence rate.** Each trial is a Bernoulli experiment, so the standard error of the estimated probability shrinks as $1/\sqrt{N}$. Via the delta method, this error propagates into the parameter estimation with the same rate:

$$\sigma_{\hat{\pi}} \propto \frac{1}{\sqrt{N}}$$

---

## Implementation

The algorithm is implemented in C++ for performance reasons, since the number of required samples is huge in order to get a reasonable result. The code is ready to be compiled using the given Makefile and the single simulation can be customize by specifying different input parameters.

The program requires 5 input parameters:

    Max: Greatest integer value the function will sample
    Length: needles' length
    Trials: number of random integers sampled for the simulation
    Blocks: number of blocks used for the average procedure
    Seed: random number generator seed (for reproducibility)

The error on the Monte Carlo estimation is computed using the standard *block average method*.

Every run of the program makes a new file in the results folder. The given example can be reproduced by using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Max | $10^8$ |
| Trials | $10^8$ |
| Blocks | $1000$ |
| Seed | $1234$ |

---

## Results

The example simulation produced the following result, which is fully compatible with the accepted value: $$ \pi = 3.14165 \pm 0.00012 $$

It should be noted that the number of random points required to get more precise results is particularly huge and may test the stability of the random number generator. Anyway, it is well know that Monte Carlo methods are excellent to estimate the first digits but they become quickly very poor in estimating the following digits.
