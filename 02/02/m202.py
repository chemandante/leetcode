# Solved:
# (E) Happy Number
# https://leetcode.com/problems/happy-number/

def _nextNumber(num: int) -> int:
    res = 0
    while num != 0:
        q, r = divmod(num, 10)
        res += r * r
        num = q
    return res


class Solution:
    def isHappy(self, n: int) -> bool:
        tortoise = n
        hare = n

        while hare != 1:
            tortoise = _nextNumber(tortoise)
            hare = _nextNumber(_nextNumber(hare))
            if hare == tortoise and hare != 1:
                return False

        return True


x = Solution()

n = 2
print(x.isHappy(n))
