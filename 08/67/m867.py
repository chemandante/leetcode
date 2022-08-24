# Solved:
# (E) Transpose Matrix
# https://leetcode.com/problems/transpose-matrix/

from typing import List


class Solution:
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:
        res = []

        for x in matrix[0]:
            res.append([x])

        for line in matrix[1:]:
            idx = 0
            for x in line:
                res[idx].append(x)
                idx += 1

        return res


x = Solution()

matrix = [[1,2,3],[4,5,6],[7,8,9]]
print(x.transpose(matrix))
