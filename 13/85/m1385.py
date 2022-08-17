from typing import List


class Solution:
    def _findLeftmost(self, nums: List[int], target: int) -> int:
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

    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:
        arr2.sort()
        res = 0
        for n in arr1:
            idx = self._findLeftmost(arr2, n - d)
            if idx == len(arr2):
                res += 1
            elif arr2[idx] > n + d:
                res += 1
        return res


x = Solution()
print(x.findTheDistanceValue(arr1=[4, 5, 8], arr2=[10, 9, 1, 8], d=2))
