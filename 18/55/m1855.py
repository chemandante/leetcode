# Solved:
# (M) Maximum Distance Between a Pair of Values
# https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/

from typing import List


class Solution:
    def _searchRightmost(self, nums: List[int], startIdx: int, target: int) -> int:
        l, r = startIdx, len(nums) - 1
        while r - l > 1:
            m = (l + r) >> 1
            if nums[m] >= target:
                l = m
            else:
                r = m - 1

        if nums[r] >= target:
            return r
        if l < r and nums[l] >= target:
            return l
        return -1

    def maxDistance(self, nums1: List[int], nums2: List[int]) -> int:
        dMax = 0
        for idx, n in enumerate(nums1):
            d = self._searchRightmost(nums2, idx + dMax, n) - idx
            if d >= 0:
                dMax = d if d > dMax else dMax

        return dMax


x = Solution()
print(x.maxDistance([55, 30, 5, 4, 2], [100, 20, 10, 10, 5]))
print(x.maxDistance([2], [3]))
print(x.maxDistance([9819, 9508, 7398, 7347, 6337, 5756, 5493, 5446, 5123, 3215, 1597, 774, 368, 313],
                    [9933, 9813, 9770, 9697, 9514, 9490, 9441, 9439, 8939, 8754, 8665, 8560]))
