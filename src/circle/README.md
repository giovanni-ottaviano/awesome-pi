# Monte Carlo: Circle method

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
The concept of this method is very simple: the value of $\pi$ is proportional to the ratio between the area of a square and the inscribed circle.
For instance, consider a square with side $l = 2r$ so that the inscrible circle have radius $r$

$$
A_{square} = l^2 = 4r^2 \\
A_{circle} = \pi r^2
$$
and
$$
\pi = 4 \frac{A_{circle}}{A_{square}}
$$

The area of the circle can be estimated using the probability of a point falling inside of it.


## Implementation
The algorithm is implemented in $C\hspace{-.05em}\raisebox{.4ex}{\tiny\bf ++}$ for performance reasons, since the number of required samples is huge in order to get a 
reasonable result. The code is ready to be compiled using the given *Makefile* and the single simulation can be customize by
specifying different input parameters.

The program requires $4$ input parameters:
- Radius: radius of the inscribed circle
- Points: number of random points sampled on the square
- Blocks: number of blocks used for the average procedure
- Seed: random number generator seed (for reproducibility)

The error on the Monte Carlo estimation is computed using the standard *block average method*.

Every run of the program makes a new file in the **results** folder. The given example can be reproduced by using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Radius | $1$ |
| Points | $10^8$ |
| Blocks | $1000$ |
| Seed | $1234$ |

## Results
The example simulation produced the following result, which is fully compatible with the accepted value:
$$
\pi = 3.1414 \pm 0.0002
$$

It should be noted that the number of random points required to get more precise results is particularly huge and may test the stability of the random number generator.