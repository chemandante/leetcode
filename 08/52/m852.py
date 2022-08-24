# Solved:
# (M) Peak Index in a Mountain Array
# https://leetcode.com/problems/peak-index-in-a-mountain-array/

from typing import List


class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        l = 1
        r = len(arr) - 2
        while r - l > 1:
            m = (l + r) // 2
            if arr[m] > arr[m + 1]:
                r = m
            else:
                l = m

        return l if arr[l] > arr[l + 1] else l + 1


x = Solution()
print(x.peakIndexInMountainArray([1, 10, 5, 3, 2, 1, 0]))
