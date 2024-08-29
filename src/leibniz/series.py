import argparse
import numpy as np

from argparse_utils import positiveint


def leibniz(order: int=0):
    """Return the summation of the first 'order + 1' terms of the Leibniz series multiplied by 4,
       i.e. 4 * sum_0^k (-1)^k / (2k + 1)
    """
    assert order >= 0

    s = 1

    for k in range(1,order + 1):
        sgn = 1 if k % 2 == 0 else -1
        term = sgn / (2*k + 1)

        s += term

    return 4*s


def nonalternating_leibniz(order: int=0):
    """Return the summation of the first 'order + 1' terms of the non-alternating Leibniz series multiplied by 4,
       i.e. 4 * sum_0^k 2 / ((4k + 1) * (4k + 3))
    """
    assert order >= 0

    s = 0

    for k in range(order + 1):
        s += 2 / ((4*k + 1) * (4*k + 3))

    return 4 * s


def list_leibniz_terms(order: int=0):
    """Return a list with the first 'order + 1' terms of the Leibniz series multiplied by 4"""
    assert order >= 0

    seq = [4.]

    for k in range(1,order + 1):
        sgn = 1 if k % 2 == 0 else -1
        term = 4 * sgn / (2*k + 1)

        seq.append(term)

    # seq = list(map(lambda x: 4*x, seq))

    return seq


def wynn_epsilon(seq: list, iteration: int):
    """Return the table with the series limit estimation using the Wymm's epsilon method,
       for accelerating the series convergence, to all iterations up to 'iteration'

       - seq: list of partial sums
       - iteration: number of repeated Shanks transformation to be applied to seq
    """
    assert iteration >= 1

    n = 2 * iteration + 1
    m = len(seq)

    e = np.zeros((m,n + 1), dtype=np.float64)

    e[:,1] = seq

    for i in range(2, n + 1):
        for j in range(0, m - i):
            e[j,i] = e[j + 1, i - 2] + 1/(e[j + 1, i - 1] - e[j, i - 1])

    return e[:, 1 : m + 1 : 2]


def weps_leibniz(order: int, iteration: int):
    """Return the estimated limit of the Leibniz series (multiplied by 4),
       after applying Wynn's epsilon convergence algorithm.
    """

    terms = list_leibniz_terms(order)
    seq = [np.sum(terms[:i+1], dtype=np.float64) for i in range(len(terms))]

    res = wynn_epsilon(seq, iteration)

    return res[-(2*(iteration-1) + 4), iteration]


def main():

    """
        Main function - Estimate PI using Leibniz series and variants.
    """

    # Get input values and set variables
    parser = argparse.ArgumentParser(description="PI estimation - Leibniz series")
    parser.add_argument('mode', help="Method for PI estimation", type=str, choices=['LB','NLB', 'WEPS'])
    parser.add_argument('--order', help="Last considered term of the series", type=positiveint, default=20)
    parser.add_argument('--iteration', help="Number of iteration for the Shanks transformation (only for WEPS mode)",
        type=positiveint, default=1
    )

    args = parser.parse_args()

    mode = args.mode
    order = args.order
    iteration = args.iteration

    dict_execution = {
        "LB": {
            "method": "Leibniz series",
            "callable": leibniz,
            "kwargs": {
                "order": order
            }
        },
        "NLB": {
            "method": "Non-alternating Leibniz series",
            "callable": nonalternating_leibniz,
            "kwargs": {
                "order": order
            }
        },
        "WEPS": {
            "method": "Wynn's epsilon method",
            "callable": weps_leibniz,
            "kwargs": {
                "order": order,
                "iteration": iteration
            }
        }
    }

    # Print chosen parameters
    print("\n-------- PI estimation --------")
    print(f"Method: {dict_execution[mode]['method']}")
    print(f"Params: {dict_execution[mode]['kwargs']}")
    print("-------------------------------\n")

    # Execution
    res = dict_execution[mode]["callable"](**dict_execution[mode]["kwargs"])

    print(f"Result: {res:.12f}")


if __name__ == "__main__":
    main()