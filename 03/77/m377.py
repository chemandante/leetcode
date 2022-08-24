# Solved:
# (M) Combination Sum IV
# https://leetcode.com/problems/combination-sum-iv/

from typing import List


class Solution:
    def __init__(self):
        self.trgs = {}

    def _combinationSum4(self, nums: List[int], target: int) -> int:
        # If combination count already calculated for specific target
        if target in self.trgs:
            return self.trgs[target]
        # Obvious answer
        if target == 0:
            return 1
        # Iterating through all nums
        res = 0
        for num in nums:
            trg = target - num
            if trg == 0:
                res += 1
            if trg <= 0:
                break

            res += self._combinationSum4(nums, trg)

        self.trgs[target] = res
        return res

    def combinationSum4(self, nums: List[int], target: int) -> int:
        nums.sort()
        return self._combinationSum4(nums, target)


x = Solution()

nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240,
        250, 260, 270, 280, 290, 300,
        310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520,
        530, 540, 550, 560, 570,
        580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790,
        800, 810, 820, 830, 840, 850,
        860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 111]
target = 999

print(x.combinationSum4([1, 2, 3], 32))  # Must be 181997601
x.__init__()
print(x.combinationSum4(nums, target))  # Must be 1
