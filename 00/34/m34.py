from typing import List


def searchLeftmost(nums: List[int], target: int) -> int:
    l, r = 0, len(nums) - 1

    while r - l > 1:
        m = (l + r) // 2
        if target <= nums[m]:
            r = m
        else:
            l = m + 1

    if nums[l] == target:
        return l
    if nums[r] == target:
        return r
    return -1


def searchRightmost(nums: List[int], startIdx: int, target: int) -> int:
    l, r = startIdx, len(nums) - 1

    while r - l > 1:
        m = (l + r) // 2
        if target >= nums[m]:
            l = m
        else:
            r = m - 1

    if nums[r] == target:
        return r
    if nums[l] == target:
        return l
    return -1


class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        if len(nums) == 0:
            return [-1, -1]

        left = searchLeftmost(nums, target)
        if left < 0:
            return [-1, -1]

        right = searchRightmost(nums, left, target)

        return [left, right]
