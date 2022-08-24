# Solved:
# (E) The K Weakest Rows in a Matrix
# https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/

from typing import List


def _getSoldiersCnt(row: List[int]) -> int:
    l, r = 0, len(row) - 1
    while r - l > 1:
        m = (l + r) >> 1
        if row[m] == 1:
            l = m
        else:
            r = m - 1
    if row[r] == 1:
        return r + 1
    if row[l] == 1:
        return l + 1
    return l


class Solution:
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        rows = {}
        idx = 0
        for row in mat:
            s = _getSoldiersCnt(row)
            if s in rows:
                rows[s].append(idx)
            else:
                rows[s] = [idx]
            idx += 1

        res = []
        for key, val in sorted(rows.items()):
            res.extend(val[0:k])
            k -= len(val)
            if k <= 0:
                break

        return res


x = Solution()
assert (x.kWeakestRows([[1, 1, 0, 0, 0], [1, 1, 1, 1, 0], [1, 0, 0, 0, 0], [1, 1, 0, 0, 0], [1, 1, 1, 1, 1]], 4) ==
        [2, 0, 3, 1])
assert (x.kWeakestRows([[1, 0, 0, 0], [1, 1, 1, 1], [1, 0, 0, 0], [1, 0, 0, 0]], 2) ==
        [0, 2])
assert(x.kWeakestRows([[1, 1], [1, 0], [1, 0], [1, 1], [0, 0], [1, 1]], 1) ==
       [4])
