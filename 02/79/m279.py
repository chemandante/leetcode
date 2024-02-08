# Solved:
# (M) Perfect Squares
# https://leetcode.com/problems/perfect-squares
# FACT: Simple factorization

from collections import defaultdict
from math import isqrt


def _factorize(n: int) -> dict:
    res = defaultdict(int)
    # Iterate through some small primes
    firstPrimes = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41)
    for d in firstPrimes:
        while n % d == 0:
            res[d] += 1
            n //= d
        if n == 1:
            return res
    # Iterate through all other divisors of the form 6*k +/- 1 (primes can only be of this form)
    d = firstPrimes[-1]
    dd = 2
    dMax = int(sqrt(n))
    while d <= dMax and n > 1:
        if n % d == 0:
            res[d] += 1
            n //= d
        else:
            d += dd  # d increases by 4, 2, 4, 2 and so on to make divisor in form of 6k +/- 1
            dd ^= 6  # dd flips between 4 and 2
    if n > 1:
        res[n] = 1

    return res


class Solution:
    def numSquares(self, n: int) -> int:
        # If n is already a perfect square
        sqrtn = isqrt(n)
        if sqrtn * sqrtn == n:
            return 1
        # Use Fermat-Euler's theorem on sums of two squares:
        # Number N will only be expressed as sum of two squares if and only if there are
        # no primes P such as P = 3 mod 4 in odd exponent in decomposition of N
        # So, we need to factorize C and check exponents of all primes in form of p = 4k + 3
        factors = _factorize(n)
        sumsq2 = True
        for k, v in factors.items():
            if k & 3 == 3 and v & 1 == 1:
                sumsq2 = False
        if sumsq2:
            return 2
        # If case that we can't represent `n` as sum of 2 squares,
        # we'll use Legendre's three-square theorem:
        # Natural number `n` can be represented as the sum of three squares of integers
        # if and only if `n` IS NOT of the form of [4^a * (8*b + 7)] for nonnegative integers a and b
        sumsq3 = True
        if factors[2] & 1 == 0: # Even power of 2, i.e. in form of 4^a * x
            if (n / 2**factors[2]) % 8 == 7:
                sumsq3 = False
        # Then use Lagrange's four-square theorem:
        # All natural numbers can be represented as the sum of at most 4 squares
        return 3 if sumsq3 else 4


x = Solution()
tests = [(12, 3), (13, 2), (11, 3)]
i = 1
for test in tests:
    res = x.numSquares(test[0])
    print(f"Test {i}: ", end="")
    if res == test[1]:
        print(f"OK!")
    else:
        print(f"Error! Result = {res} but {test[1]} expected")
    i += 1
