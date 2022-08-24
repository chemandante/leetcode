# Solved:
# (M) Sum of Square Numbers
# https://leetcode.com/problems/sum-of-square-numbers/

import math
from collections import defaultdict
from random import randint


def _factorize(n: int) -> dict:
    res = defaultdict(int)
    # Iterate through soma small primes
    firstPrimes = (2, 3, 5, 7, 11, 13, 17)
    for d in firstPrimes:
        while n % d == 0:
            res[d] += 1
            n //= d
        if n == 1:
            return res
    # Iterate through all other divisors of the form 6*k +/- 1 (primes can only be of this form)
    d = 19
    dd = 4
    dMax = int(math.sqrt(n))
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
    def judgeSquareSum(self, c: int) -> bool:
        # Solution uses Fermat-Euler's theorem on sums of two squares:
        # Number C will only be expressed as sum of two squares if and only if the are
        # no primes P such as P = 3 mod 4 in odd exponent in decomposition of C
        # So, we need to factorize C and check exponents of all primes in form of p = 4k + 3

        # Obvious cases
        if c <= 2:
            return True

        factors = _factorize(c)
        for k, v in factors.items():
            if k % 4 == 3 and v % 2 == 1:
                return False

        return True


x = Solution()
for i in range(0, 200):
    n = randint(1, 2**31)
    print(n, x.judgeSquareSum(n))
