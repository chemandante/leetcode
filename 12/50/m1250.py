# Solved:
# (H) Check If It Is a Good Array
# https://leetcode.com/problems/check-if-it-is-a-good-array/

import math
from typing import List


class Solution:
    def isGoodArray(self, nums: List[int]) -> bool:
        n = nums[0]
        for x in nums[1:]:
            n = math.gcd(n, x)
            if n == 1:
                return True
        return True if n == 1 else False


x = Solution()

data = [6,10,15]
print(x.isGoodArray(data))
# #exit(0)
# data = [287,41,49,287,899,23,23,20677,5,825]
# print(x.replaceNonCoprimes(data))
