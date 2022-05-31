import math
from typing import List


class Solution:
    def replaceNonCoprimes(self, nums: List[int]) -> List[int]:
        idx = 0
        idxEnd = len(nums) - 1
        while idx < idxEnd:
            x1 = nums[idx]
            x2 = nums[idx + 1]
            gcd = math.gcd(x1, x2)
            if gcd != 1:
                nums[idx] = x1 * x2 // gcd
                del nums[idx + 1]
                idxEnd -= 1
                idx = idx - 1 if idx > 0 else idx
            else:
                idx += 1

        return nums

# x = Solution()
#
# data = [6,4,3,2,7,6,2]
# print(x.replaceNonCoprimes(data))
# #exit(0)
# data = [287,41,49,287,899,23,23,20677,5,825]
# print(x.replaceNonCoprimes(data))
