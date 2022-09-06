# Solved:
# (E) Flood Fill
# https://leetcode.com/problems/flood-fill/

from collections import deque
from typing import List


class Solution:
    def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
        que = deque([(sr, sc)])
        xmax, ymax = len(image) - 1, len(image[0]) - 1
        c = image[sr][sc]
        # No need to fill in obvious case: filling by the same color
        if c == color:
            return image

        while que:
            x, y = que.popleft()
            if x > 0 and image[x - 1][y] == c:
                que.append((x - 1, y))
            if y > 0 and image[x][y - 1] == c:
                que.append((x, y - 1))
            if x < xmax and image[x + 1][y] == c:
                que.append((x + 1, y))
            if y < ymax and image[x][y + 1] == c:
                que.append((x, y + 1))
            image[x][y] = color

        return image


x = Solution()
print(x.floodFill([[1, 1, 1], [1, 1, 0], [1, 0, 1]], sr=1, sc=1, color=2))
