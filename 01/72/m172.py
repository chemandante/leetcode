class Solution:
    def trailingZeroes(self, n: int) -> int:
        # One trailing zero of n! means that n! is divisible by 10, i.e. by 5 and 2 simultaneously
        # `M` trailing zeroes means that n! is divisible by 5^M and 2^M simultaneously
        # So, we need to find exponent of prime 5 and 2 in factorization of n!
        # The minimum value of the exponent of 5 and 2 gives us the number of trailing zeros
        # According to Legendre's formula, exponent of prime factor `p` in the factorization of n! is:
        # vp(n!) = floor(n/p) + floor(n/p**2) + floor(n/p**3) + ...
        # It is obvious that exponent of 5 is less than exponent of 2, so we will calc only first one
        exp, np = 0, n // 5
        # Iterating through all floor(n/p**k) greater than 0 and accumulating the sum
        while np > 0:
            exp += np
            np //= 5
        return exp


x = Solution()
print(x.trailingZeroes(6))
