# Solved:
# (E) Find Smallest Letter Greater Than Target
# https://leetcode.com/problems/find-smallest-letter-greater-than-target/

from typing import List


class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        l = 0
        r = len(letters) - 1

        while r - l > 1:
            m = (l + r) // 2
            if target >= letters[m]:
                l = m
            else:
                r = m - 1

        if letters[l] > target:
            return letters[l]
        if letters[r] > target:
            return letters[r]

        return letters[0 if r + 1 == len(letters) else r + 1]


x = Solution()
# print(x.nextGreatestLetter(letters=["c", "f", "j"], target="a"))
# print(x.nextGreatestLetter(letters=["c", "f", "j"], target="c"))
# print(x.nextGreatestLetter(letters=["c", "f", "j"], target="d"))
for char in "abcdefghijk":
    print(char, x.nextGreatestLetter(letters=["a", "b", "c", "e", "f", "j"], target=char))
