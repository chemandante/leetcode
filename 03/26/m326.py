class Solution:
    def isPowerOfThree(self, n: int) -> bool:
        # All power of three will divide maximal value of 3**19 that fits into 32-bit signed integer
        # Under the terms of the problem n <= 2**31 - 1
        if n <= 0:
            return False
        return 3**19 % n == 0


x = Solution()
print(x.isPowerOfThree(3))
print(x.isPowerOfThree(6))
print(x.isPowerOfThree(27))
