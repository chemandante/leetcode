from typing import List


def _countNegatives(nums: List[int]) -> int:
    """
    Count negative numbers in sorted non-increasing list
    :param nums: list of integers
    :return: Count of negatives
    """
    # First we do a binary search of index of first negative `idx`,
    # then result well be (len(nums) - idx)
    cnt = len(nums)
    l, r = 0, cnt - 1
    while r - l > 1:
        m = (l + r) >> 1
        if nums[m] < 0:
            r = m
        else:
            l = m + 1
    if nums[l] < 0:
        return cnt - l
    if nums[r] < 0:
        return cnt - r
    return 0


class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        # At first, count negatives in first row
        cols = len(grid[0])
        res = _countNegatives(grid[0])
        j = cols - res - 1  # Index of last positive (can be -1 if there are no positives)
        # Iterate through all the other rows
        for nums in grid[1:]:
            while j >= 0 and nums[j] < 0:
                j -= 1
            res += cols - j - 1

        return res


x = Solution()
print(x.countNegatives([[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]))
