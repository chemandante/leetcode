# Solved:
# (M) Concatenation of Consecutive Binary Numbers
# https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/

class Solution:
    def concatenatedBinary(self, n: int) -> int:
        res = 1
        shift = 1
        modulo = 10**9 + 7

        for i in range(2, n + 1):
            # If `i` is exact power of 2 increase `shift` by 1
            if i & (i - 1) == 0:
                shift += 1
            res = ((res << shift) + i) % modulo

        return res


x = Solution()
print(x.concatenatedBinary(1))  # 1
print(x.concatenatedBinary(3))  # 27
print(x.concatenatedBinary(12))  # 505379714
