# Monte Carlo: Buffon's needle method

## Overview
Monte Carlo methods are a class of algorithms that rely on random numbers to solve numerical problems. The basic idea is to sample random variables from a selected proabability
distribution and employ them to compute the outcomes for the given experiment through a mathematical model. Since these algorithms involve randomness, the results will be different
every time, yielding a range of possible outcomes with the probability of each result occurring.

Monte Carlo methods for different applications may be different, but they can be summarized in the following steps:
1. Define a predictive model, identifying both the dependent variable to be predicted and the independent variables
2. Select a suitable probability distribution and generate indipendent (random) inputs from it
3. Run the simulation using the model to compute the dependent variables from the random inputs
4. Aggregate the results and estimate the error 


Let's analyze some *pros* and *cons* of Monte Carlo methods:
#### Pros
- Makes it possible the simulation of complex systems, for which there are no mathematical (exact) solutions
- Useful to model phenomena with significant uncertainty in input
- Highly parallelizable
- Employed in lots of different scientific fields due to their flexibility

#### Cons
- Results are highly dependent on the input distributions and requires a stable random number generator
- Might take excessive computational power (and time) to perform Monte Carlo experiments
- The uncertainty on the result (i.e. the *mean standard deviation*) scales only as $1/\sqrt{N}$ with the number of samples

## Model
A surprising way of calculating $\pi$ was discovered in the 18th century by *Georges-Louis Leclerc, Comte de Buffon*, by
posing a simple question of geometric probability theory: *"What is the chance that a needle dropped randomly onto a floor marked with equally spaced parallel lines will cross one of the lines?"*
Since the exact solution for the probability involve the factor $\pi$, a simple algorithm can be made on top of that to have an estiation of the irrational constant $\pi$.

Let's see a quick proof for the exact formula for the probability $P$.\
Consider a set of parallel lines equally spaced with distance $d$ and a collection of identical needles with length $l$. Let $x$ be the distance between the center needle 
and the nearest parallel line ($x = 0$ a needle centered on a line) and $\theta$ be the acute angle between the needle and the line. Both follows uniform distributions:
$$
\begin{align*}
f_X(x) &= \frac{2}{d} \qquad 0 \leq x \leq \frac{d}{2}   \\
f_\Theta(\theta) &= \frac{2}{\pi} \qquad 0 \leq \theta \leq \frac{\pi}{2}
\end{align*}
$$
and the joint probability is
$$
f_{X,\Theta}(x,\theta) = f_X(x) \, f_\Theta(\theta) = \frac{4}{\pi d} \qquad 0 \leq x \leq \frac{\pi}{2} \,\text{ and }\, 0 \leq x \leq \frac{d}{2}
$$
The needle crosses a line only if $x \leq \frac{l}{2} \sin\theta$. The total probability can be compute by integrating the $f_{X,\Theta}$. 

#### Short needle $\bigl( l \leq d \bigr)$
$$
P_{short} = \int_0^{\frac{\pi}{2}} \int_0^{\frac{l}{2} \sin\theta} \frac{4}{\pi d} \,dxd\theta = \frac{2l}{\pi d}
$$

#### Long needle $\bigl( l > d \bigr)$
$$
P_{long} = \int_0^{\frac{\pi}{2}} \int_0^{\min\left(\frac{l}{2} \sin\theta, \,\frac{d}{2}\right)} \frac{4}{\pi d} \,dxd\theta = 
\frac{2}{\pi} \Biggl[ \arccos\frac{d}{l} + \frac{l}{d} \left(1 - \sqrt{1 - (d/l)^2} \right)  \Biggr]
$$


Reversing the formula for $P$ gives  a method of calculation for $\pi$:
$$
\pi = \frac{2l}{d} \frac{N}{N_{hit}}
$$
where $P = N_{hit} / N$ can be approximated by "throwing" a huge number of needles and counting the hits. 

**N.B:** The simulation runs only in the *short needle* case, since the formula for $P$ doesn't require any trigonometric function, that can use the value of $\pi$
in some calculation and add a bias in the results.

## Implementation
The algorithm is implemented in $C\hspace{-.05em}\raisebox{.4ex}{\tiny\bf ++}$ for performance reasons, since the number of required samples is huge in order to get a 
reasonable result. The code is ready to be compiled using the given *Makefile* and the single simulation can be customize by
specifying different input parameters.

The program requires $5$ input parameters:
- Spacing: distance between the parallel lines
- Length: needles' length
- Points: number of random needles sampled for the simulation
- Blocks: number of blocks used for the average procedure
- Seed: random number generator seed (for reproducibility)

The error on the Monte Carlo estimation is computed using the standard *block average method*.

Every run of the program makes a new file in the **results** folder. The given example can be reproduced by using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Spacing | $1$ |
| Length | $0.5$ |
| Points | $10^8$ |
| Blocks | $1000$ |
| Seed | $1234$ |

## Results
It's well known that Buffon's method, although it works, produces **poor results**, since it requires an excessive number of throws just for few correct digits of $\pi$.
The example simulation produced the following result, which is fully compatible with the accepted value:
$$
\pi = 3.1415 \pm 0.0005
$$

A chance to improve results is the **Buffon-Laplace method** (see [here](https://mathworld.wolfram.com/Buffon-LaplaceNeedleProblem.html)), that considers a grid insted of a set of parallel lines.
This method should require less than half of the points to obtain the same precision.