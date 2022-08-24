# Solved:
# (M) Reduce Array Size to The Half
# https://leetcode.com/problems/reduce-array-size-to-the-half/

from collections import Counter
from typing import List


class Solution:
    def minSetSize(self, arr: List[int]) -> int:
        s = Counter(arr)
        s = list(s.values())
        s.sort(reverse=True)
        size = len(arr)
        trg_size = size // 2
        i = 0
        while size > trg_size:
            size -= s[i]
            i += 1

        return i


x = Solution()
print(x.minSetSize([3, 3, 3, 3, 5, 5, 5, 7, 2, 2]))
