# The guess API is already defined for you.
# @param num, your guess
# @return -1 if num is higher than the picked number
#          1 if num is lower than the picked number
#          otherwise return 0
pick = 2

def guess(num: int) -> int:
    if num > pick:
        return -1
    elif num < pick:
        return 1
    return 0


class Solution:
    def guessNumber(self, n: int) -> int:
        l = 1
        r = n

        while l < r:
            m = (l + r) // 2
            a = guess(m)

            if a < 0:  # Our guess is higher
                r = m - 1
            elif a > 0:  # Our guess is lower
                l = m + 1
            else:
                return m

        return l


x = Solution()

print(x.guessNumber(13330))
