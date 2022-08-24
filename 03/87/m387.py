# Solved:
# (E) First Unique Character in a String
# https://leetcode.com/problems/first-unique-character-in-a-string/

class Solution:
    def firstUniqChar(self, s: str) -> int:
        arr = [0] * 26
        i = 1
        for char in s:
            idx = ord(char) - 97
            if arr[idx] == 0:
                arr[idx] = i
            elif arr[idx] > 0:
                arr[idx] = -1
            i += 1

        iMin = i + 1
        for n in arr:
            if 0 < n < iMin:
                iMin = n

        return iMin - 1 if iMin < len(s) + 1 else -1


x = Solution()

print(x.firstUniqChar("z"))
