# Blocks collisions

## Model
The model is based on the physical process of *elastic collision* between two bodies in 1 dimension, in which the total kinetic energy is conserved as well as the total momentum of the system.
The system of equations can be expressed as:

$$
\left\{
    \begin{align}
        \frac{1}{2}m_1 v_{1i}^2 + \frac{1}{2}m_2 v_{2i}^2 &= \frac{1}{2}m_1 v_{1f}^2 + \frac{1}{2}m_2 v_{2f}^2 \\
        m_1 v_{1i} + m_2 v_{2i} &= m_1 v_{1f} + m_2 v_{2f}
    \end{align}
$$

The resulting variables are the final velocities:

$$
\left\{
    \begin{align}
        v_{1f} &= \frac{m_1 - m_2}{m_1 + m_2} v_{1i} + \frac{2 m_2}{m_1 + m_2} v_{2i}\\
        v_{2f} &= \frac{2 m_1}{m_1 + m_2} v_{1i} + \frac{m_2 - m_1}{m_1 + m_2} v_{2i}\\ 
    \end{align}
\right
$$

Considering the phase space (i.e. the cartesian place given by $v_1$ and $v_2$) it is pretty straightforward to notice that the feasible values of velocities are equally distributed on an ellipse (or a circumference, under specific rescaling) given by the conservation of energy.

A simple geometrical argument allows to prove that the number of collision is determined by:

$$
N \cdot \theta < \pi
$$
where $\theta$, which is an approximation of the arctangent for small angles, is linked to the square root of the ration between the masses of the blocks:

$$
\theta \approx \arctan(\theta) = \arctan(\sqrt{m_2 / m_1})
$$

A comprehensive explanation was realized by [3B1B](https://www.3blue1brown.com/lessons/colliding-blocks-v2) (highly recommended!).

## Implementation
The algorithm is implemented in C++ for performance reasons, since the number of required collisions is huge in order to get a reasonable result. The code is ready to be compiled using the given *Makefile* and the single simulation can be customize by specifying different input parameters.

The program requires $2$ input parameters:
- Mass: mass of the bigger block ($m > 1$)
- Velocity: initial velocity of the bigger block ($v < 0$)

The number of collision for a given simulation are printed on screen. The given example can be reproduced by using the following set of parameters:
| Name | Value |
| ----------- | ----------- |
| Mass | $10^{22}$ |
| Velocity | $-5$ |

## Results
The example simulation produced the following result, which is exact up to the $11\text{th}$ digit:

$$
\pi = 3.14159265358
$$

This method is pretty powerful, at least for the fist digits, since the simulation time is short. However, it starts to become seriously expensive after exceeding the mass value of $10^{20}$.