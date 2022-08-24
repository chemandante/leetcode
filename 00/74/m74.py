# Solved:
# (M) Search a 2D Matrix
# https://leetcode.com/problems/search-a-2d-matrix/

from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        # Because "first integer of each row is greater than the last integer of the previous row"
        # we can simply flatten the index, i.e., making 2D-index one-dimensional
        # For 2D index [i, j] corresponding 1-D index will be idx = i * M + j,
        # where `M` is the number of columns in matrix, `i` row number, `j` column number
        # To solve the problem we will use binary search in 1D-indexed vector
        M, N = len(matrix[0]), len(matrix)
        l, r = 0, N * M - 1
        while l < r:
            m = (l + r) >> 1
            i = m // M
            j = m - i * M
            if matrix[i][j] == target:
                return True
            if target < matrix[i][j]:
                r = m - 1
            else:
                l = m + 1

        i = l // M
        j = l - i * M
        return matrix[i][j] == target
