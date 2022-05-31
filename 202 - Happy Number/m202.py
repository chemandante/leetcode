def _nextNumber(num: int) -> int:
    res = 0
    while num != 0:
        q, r = divmod(num, 10)
        res += r * r
        num = q
    return res


class Solution:

    def isHappy(self, n: int) -> bool:
        nums = {n}

        while n != 1:
            n = _nextNumber(n)
            if n in nums:
                return False
            nums.add(n)

        return True


x = Solution()

n = 23495739879283742
print(x.isHappy(n))
