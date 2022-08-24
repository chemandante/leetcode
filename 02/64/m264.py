# Solved:
# (M) Ugly Number II
# https://leetcode.com/problems/ugly-number-ii/

class Solution:
    ulist: list

    def __init__(self):
        self.ulist = []

    def _buildUglyList(self, nMax: int):
        k5 = 1
        while k5 <= nMax:
            k3 = k5
            while k3 <= nMax:
                k2 = k3
                while k2 <= nMax:
                    self.ulist.append(k2)
                    k2 *= 2
                k3 *= 3
            k5 *= 5

    def nthUglyNumber(self, n: int) -> int:
        self._buildUglyList(2**31 - 1)
        self.ulist.sort()
        return self.ulist[n - 1]


x = Solution()
print(x.nthUglyNumber(10))
