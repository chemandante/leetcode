class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # Number of unique paths equals to the number of combinations "S choose Q" where S is total number of moves
        # S = m + n - 2 and Q is moves in one direction (say down), Q = m - 1
        # So here we will calculate binomial coefficient "(m + n - 2) choose (m - 1)"
        if m > n:
            m, n = n, m
        # Hee always n >= m
        c = 1  # Result
        u = n  # Numerator
        v = 1  # Denominator
        while v < m:
            c = c * u // v
            u += 1
            v += 1
        return c


x = Solution()
print(x.uniquePaths(4, 4))
