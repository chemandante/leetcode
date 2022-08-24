# Solved:
# (E) Unique Morse Code Words
# https://leetcode.com/problems/unique-morse-code-words/

from typing import List


class Solution:
    def uniqueMorseRepresentations(self, words: List[str]) -> int:
        morse = [".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.",
                 "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."]
        ws = set()
        for word in words:
            s = ""
            for char in word:
                s += morse[ord(char) - 97]
            ws.add(s)

        return len(ws)


x = Solution()
print(x.uniqueMorseRepresentations(["g"]))
