from typing import List


def _binSearch(nums: List[int], target: int) -> int:
    l, r = 0, len(nums) - 1
    while l < r:
        m = (l + r) // 2
        if target < nums[m]:
            r = m - 1
        elif target > nums[m]:
            l = m + 1
        else:
            return m

    return l if nums[l] == target else -1


class Solution:
    def checkIfExist(self, arr: List[int]) -> bool:
        arr.sort()
        for i, num in enumerate(arr):
            # If `num` is even, so it can be double of some other integer
            if num & 1 == 0:
                idx = _binSearch(arr, num >> 1)
                if idx >= 0 and idx != i:
                    return True
        return False


x = Solution()
assert x.checkIfExist([10, 2, 5, 3])
assert x.checkIfExist([7, 1, 14, 11])
assert not x.checkIfExist([3, 1, 7, 11])
assert x.checkIfExist([-10, 12, -20, -8, 15])
assert not x.checkIfExist([-2, 0, 10, -19, 4, 6, -8])
assert x.checkIfExist([0, 0])
