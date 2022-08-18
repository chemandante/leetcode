class Solution:
    def mySqrt(self, x: int) -> int:
        bit = 1 << 15
        res = 0
        while bit > 0:
            r = res + bit
            if r * r <= x:
                res += bit
            bit >>= 1
        return res


x = Solution()
for i in range(0, 10):
    print(i, x.mySqrt(i))
