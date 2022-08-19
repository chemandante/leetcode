bad = 4


def isBadVersion(version: int) -> bool:
    return version >= bad


class Solution:
    def firstBadVersion(self, n: int) -> int:
        l, r = 1, n

        while r - l > 1:
            m = (l + r) // 2
            if isBadVersion(m):
                r = m
            else:
                l = m + 1

        if isBadVersion(l):
            return l
        return r


x = Solution()
print(x.firstBadVersion(5))
