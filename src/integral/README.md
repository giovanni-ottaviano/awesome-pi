# Numeric integration

## Model
The irrational constant $\pi$ can be found in the result of lots of different integrals, just think of trigonometric functions or Gaussian integrals.
A remarkable case is the polynomial $f(x) = 1 / (1 + x^2)$, which is linked to a trigonometric function: it's the derivative of the *arcotanget* function,
that has lots of well know values proportional to $\pi$.

$$
\frac{\pi}{4} = \arctan (1) = \int_0^1 \frac{1}{1 + x^2} \,dx
$$

It is useful to notice that a non-trigonometric integrand function was chosen in order to to avoid possible bias on the resulting value of $\pi$.

Let's talk for a moment about the **numerical integration**, also called *quadrature*. There are different techniques both deterministic,
such as the *[Newton - Cotes formulas](https://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas)*, and non-deterministic,
such as *[Monte Carlo integration](https://en.wikipedia.org/wiki/Monte_Carlo_integration)*.
The latter class of methods is chosen, since Monte Carlo methods were already presented for other ways to estimate $\pi$.
Here, it is implemented its most straightforward version, the *uniform sampling Monte Carlo*.

## Implementation
The algorithm is implemented in $C\hspace{-.05em}\raisebox{.4ex}{\tiny\bf ++}$ for performance reasons, since the number of required samples is huge in order to get a 
reasonable result. The code is ready to be compiled using the given *Makefile* and the single simulation can be customize by
specifying different input parameters.

The program requires $3$ input parameters:
- Points: number of random needles sampled for the simulation
- Blocks: number of blocks used for the average procedure
- Seed: random number generator seed (for reproducibility)

The error on the Monte Carlo estimation is computed using the standard *block average method*.

Every run of the program makes a new file in the **results** folder. The given example can be reproduced by using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Points | $10^8$ |
| Blocks | $1000$ |
| Seed | $1234$ |

## Results
The example simulation produced the following result, which is fully compatible with the accepted value:
$$
\pi = 3.14158 \pm 0.00006
$$

It should be noted that the number of random points required to get more precise results is particularly huge and may test the stability of the random number generator.