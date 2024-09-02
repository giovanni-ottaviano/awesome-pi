# Leibniz's formula

## Model
A classic way of calculating $\pi$ is picking a convergent series (i.e. a summation with an infinite number of terms) whose value is proportional to $\pi$.
There are lots of such examples and the most known is the *Leibniz series*, an alternating series known since the 14th century:

$$
\sum_{k=0}^\infty \frac{(-1)^k}{2k + 1} = \frac{\pi}{4}
$$

Proving the equality is very simple, since the Leibniz series is just the *Taylor expansion* for the inverse tanget in $x=1$:
$$
\arctan (x) = \sum_{k=0}^\infty \frac{(-1)^k}{2k + 1} x^{2k + 1}
$$
and $\arctan (1) = \frac{\pi}{4}$.

It's useful to notice that a pairwise combination of the terms in the Leibniz series gives a new non-alternating series:
$$
\frac{\pi}{4} = \sum_{k=0}^\infty \frac{2}{(4k + 1)(4k + 3)}
$$

Let's talk for a moment about the convergence of the series: \
this formula converges extremely slowly (*sublinear convergence*) and calculating the first few digits requires thousands for terms.
However, there are lots of *acceleration techniques* that can be implemented to increase the rate of convergence. For example, **Shanks transformation** $S$
is a non-linear transformation performed on the sequence of partial sums $A_n$ of a given sequence $\{a_n\}_{n \in \N}$:
$$
A_n = \sum_{m=0}^n a_m
$$
$$
S(A_n) = A_{n + 1} - \frac{(A_{n + 1} - A_n)^2}{(A_{n + 1} - A_n) - (A_n - A_{n - 1})}
$$
where the sequence $S(A_n)$ usually converges more rapidly that the sequence of the partial sums.\
It's also possible to further speed-up the convergence by iterating the transformation: $S^2(A_n) \equiv S(S(A_n))$ and so on.

## Implementation
The implemented code is written in *Python* and allows runs for 3 different methods: the alternating series, the non-alternating series and the Shanks transformation. In particular, the latter employs
the **Wynn’s epsilon algorithm**, an efficient recursive way of computing repeated Shanks transformations on a sequence
(more details [here](https://dlmf.nist.gov/3.9#iv)).

The program takes $3$ input parameters:
- Mode: the method used for $\pi$ estimation (*LB = Leibniz, NLB = Non-alternating Leibniz, WEPS = Wynn's epsilon*)
- Order: (Optional) the order of the last term to be computed in the sequence
- Iteration: (Optional) the number of iterated Shanks tranformation to be applied (only for *mode = WEPS*)

The example in the **results** folder can be reproduced using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Mode | $\text{WEPS}$ |
| Order | $20$ |
| Iteration | $3$ |

## Results
The example simulation produced the following result, which is exact up to the $8\text{th}$ digit:
$$
\pi = 3.141592652259
$$

Compared to the other methods implemented in this repository, Wymm's epsilon technique on Leibniz series is the most powerful, for sure.\
It's possible to get even more correct digits of $\pi$ just by tuning the input parameters, but requesting too many transformations or orders 
can result in precision loss due to floating-point arithmetic and finite machine precision. 