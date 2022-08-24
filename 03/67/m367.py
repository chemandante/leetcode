# Solved:
# (E) Valid Perfect Square
# https://leetcode.com/problems/valid-perfect-square/

class Solution:
    def isPerfectSquare(self, num: int) -> bool:
        # Second LSB in full square can't be '1', because <full square> = 0 or 1 mod 4
        if num & 0x2 != 0:
            return False
        # Binary search approach
        bit_pos = 16
        res = 0
        while bit_pos >= 0:
            x = 1 << bit_pos
            sq = (res + x) ** 2
            if sq == num:
                return True
            if sq < num:
                res += x
            bit_pos -= 1

        return False


x = Solution()
print(x.isPerfectSquare(121))
