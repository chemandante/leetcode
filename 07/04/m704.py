# Solved:
# (E) Binary Search
# https://leetcode.com/problems/binary-search/
# BINS: Simple search

from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) - 1

        while l < r:
            m = (l + r) // 2
            x = nums[m]
            if target < x:
                r = m - 1
            elif target > x:
                l = m + 1
            else:
                return m

        return l if nums[l] == target else -1


x = Solution()
print(x.search([5], 5))
