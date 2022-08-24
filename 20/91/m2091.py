# Solved:
# (M) Removing Minimum and Maximum From Array
# https://leetcode.com/problems/removing-minimum-and-maximum-from-array/

from typing import List


class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        # At first, we should find positions of maximum and minimum of the array
        # Let leftmost value (it doesn't matter, minimum or maximum) be 'A' and other 'B'
        # Let define positions from left and right: LA, LB, RA, RB as shown
        # |<------LA------->|<---------------RA-------------->|
        # |   |   |   |   | A |   |   |   |   |   |   |   |   |
        # |   |   |   |   |   |   | B |   |   |   |   |   |   |
        # |<-----------LB---------->|<-----------RB---------->|
        # Pay attention that LA + RA = LB + RB = N + 1 (N is the size of array)

        # For obvious cases
        if len(nums) <= 2:
            return len(nums)

        # Finding positions
        mx = nums[0]
        mn = nums[0]
        LA, LB = 0, 0
        for i in range(1, len(nums)):
            if nums[i] > mx:
                mx = nums[i]
                LA = i
            elif nums[i] < mn:
                mn = nums[i]
                LB = i
        # Swapping LA and LB if LA > LB
        if LA > LB:
            LA, LB = LB, LA
        # Take in mind that LA and LB starting from 1 (ex, for nums[4] LA will be equal to 5)
        LA += 1
        LB += 1
        RA, RB = len(nums) + 1 - LA, len(nums) + 1 - LB
        # There are only three cases for deletion:
        # 1. Delete only from the left: result = LB
        # 2. Delete only from the right: result = RA
        # 3. Delete both from left to 'A' and from right to 'B': result = LA + RB
        # Our goal is to find which result is smaller
        res = LB if LB < RA else RA
        res = LA + RB if LA + RB < res else res

        return res



x = Solution()

print(x.minimumDeletions([2,10,7,5,4,1,8,6]))
print(x.minimumDeletions([0,-4,19,1,8,-2,-3,5]))
