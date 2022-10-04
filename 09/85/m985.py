# Solved:
# (M) Sum of Even Numbers After Queries
# https://leetcode.com/problems/sum-of-even-numbers-after-queries/

from typing import List


class Solution:
    def sumEvenAfterQueries(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        res = [0] * len(queries)
        s = sum([n for n in nums if n % 2 == 0])

        for i, row in enumerate(queries):
            n = nums[row[1]]
            # If next number to be replaced was even, subtract its value from sum
            if n & 1 == 0:
                s -= n
            n += row[0]
            # If new value is even, add it to sum
            if n & 1 == 0:
                s += n

            nums[row[1]] = n
            res[i] = s

        return res


x = Solution()
print(x.sumEvenAfterQueries(nums=[1, 2, 3, 4], queries=[[1, 0], [-3, 1], [-4, 0], [2, 3]]))
print(x.sumEvenAfterQueries(nums=[1], queries=[[4, 0]]))
