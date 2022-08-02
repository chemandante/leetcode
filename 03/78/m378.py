import heapq
from typing import List


class Solution:
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
        cnt = 0
        pq = []
        for row in matrix:
            if not pq or cnt < k or row[0] < -pq[0]:
                for el in row:
                    if cnt < k:
                        heapq.heappush(pq, -el)
                        cnt += 1
                    else:
                        if -el > pq[0]:
                            heapq.heappushpop(pq, -el)
                        else:
                            continue
        return -pq[0]


x = Solution()
print(x.kthSmallest([[1,5,9],[10,11,13],[12,13,15]], 8))
