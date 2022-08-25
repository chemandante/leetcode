# Solved:
# (M) Search in Rotated Sorted Array
# https://leetcode.com/problems/search-in-rotated-sorted-array/

from typing import List


class Solution:
    def __init__(self):
        self.cnt = None

    def _getIdx(self, idx):
        idx += self.lag
        return idx if idx < self.cnt else idx - self.cnt

    def _findLag(self, nums: List[int]):
        l, r = 1, self.cnt - 1
        n = nums[0]
        while r - l > 1:
            m = (l + r) >> 1
            if nums[m] < n:
                r = m
            else:
                l = m + 1
        if nums[l] < n:
            self.lag = l
        elif nums[r] < n:
            self.lag = r
        else:
            self.lag = 0

    def search(self, nums: List[int], target: int) -> int:
        self.cnt = len(nums)
        # Obvious case, array of one element
        if self.cnt == 1:
            return 0 if nums[0] == target else -1

        self._findLag(nums)

        l, r = 0, self.cnt - 1
        while l < r:
            m = (l + r) >> 1
            x = nums[self._getIdx(m)]
            if target < x:
                r = m - 1
            elif target > x:
                l = m + 1
            else:
                return self._getIdx(m)
        x = self._getIdx(l)
        return x if nums[x] == target else -1


x = Solution()
print(x.search([4, 5, 6, 7, 0, 1, 2], 4))
print(x.search([1], 1))
