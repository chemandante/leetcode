# Solved:
# (M) Number of Closed Islands
# https://leetcode.com/problems/number-of-closed-islands/

from collections import deque
from typing import List


class Solution:
    def _processIsland(self, grid: List[List[str]], x: int, y: int) -> bool:
        xmax, ymax = len(grid) - 1, len(grid[0]) - 1
        que = deque([(x, y)])
        grid[x][y] = 1
        isClosed = True
        while que:
            x, y = que.popleft()
            if x == 0 or y == 0 or x == xmax or y == ymax:
                isClosed = False
            if x > 0 and grid[x - 1][y] == 0:
                grid[x - 1][y] = 1
                que.append((x - 1, y))
            if y > 0 and grid[x][y - 1] == 0:
                que.append((x, y - 1))
                grid[x][y - 1] = 1
            if x < xmax and grid[x + 1][y] == 0:
                que.append((x + 1, y))
                grid[x + 1][y] = 1
            if y < ymax and grid[x][y + 1] == 0:
                que.append((x, y + 1))
                grid[x][y + 1] = 1
        return isClosed

    def closedIsland(self, grid: List[List[int]]) -> int:
        res = 0
        for x, row in enumerate(grid[1:-1], start=1):
            for y in range(1, len(row) - 1):
                if grid[x][y] == 0:
                    if self._processIsland(grid, x, y):
                        res += 1

        return res


x = Solution()
print(x.closedIsland(
    [[1, 1, 1, 1, 1, 1, 1, 0], [1, 0, 0, 0, 0, 1, 1, 0], [1, 0, 1, 0, 1, 1, 1, 0], [1, 0, 0, 0, 0, 1, 0, 1],
     [1, 1, 1, 1, 1, 1, 1, 0]]))
