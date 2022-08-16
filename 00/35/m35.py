from typing import List


class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        # We should find leftmost 'target' value in the list of nums
        l = 0
        r = len(nums) - 1
        while r - l > 1:
            m = (l + r) // 2
            if target <= nums[m]:
                r = m
            else:
                l = m + 1
        if nums[r] < target:
            return r + 1
        elif nums[l] < target:
            return l + 1
        else:
            return l


x = Solution()

nums = [1]

for i in range(0, 11):
    print(f"{i} -> {x.searchInsert(nums, i)}")
