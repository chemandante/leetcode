# Solved:
# (E) Roman to Integer
# https://leetcode.com/problems/roman-to-integer/

class Solution:
    def romanToInt(self, s: str) -> int:
        digits = {'M': 1000, 'D': 500, 'C': 100, 'L': 50, 'X': 10, 'V': 5, 'I': 1}
        res = 0
        prevD = digits[s[0]]

        for ch in s[1:]:
            newD = digits[ch]
            if prevD:
                if prevD >= newD:
                    res += prevD
                else:
                    res += newD - prevD
                    prevD = None
                    continue

            prevD = newD

        if prevD:
            res += prevD

        return res


x = Solution()

print(x.romanToInt("X"))  # 10
print(x.romanToInt("IX"))  # 9
print(x.romanToInt("MCMLIII"))  # 1953
print(x.romanToInt("MCMLXXVIII"))  # 1978
print(x.romanToInt("MCDXCII"))  # 1492
print(x.romanToInt("MMXXII"))  # 2022
