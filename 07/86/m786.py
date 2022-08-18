import heapq
from typing import List


class Solution:
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        idxNum = 0  # Numerator index
        idxDen = len(arr) - 1  # Denominator index
        fracIdx = (idxNum, idxDen)
        # Priority queue is a list uf tuples: (fraction, numerator index, denominator index)
        fraqQue = [(arr[fracIdx[0]] / arr[fracIdx[1]], fracIdx[0], fracIdx[1])]
        # Set of fractions contains tuples: (numerator index, denominator index)
        fracSet = set([fracIdx])
        while k > 0 and idxNum < idxDen and fraqQue:
            _, idxNum, idxDen = heapq.heappop(fraqQue)
            if idxDen - idxNum > 1:
                fracIdx = (idxNum + 1, idxDen)
                if fracIdx not in fracSet:
                    heapq.heappush(fraqQue, (arr[fracIdx[0]] / arr[fracIdx[1]], fracIdx[0], fracIdx[1]))
                    fracSet.add(fracIdx)
                fracIdx = (idxNum, idxDen - 1)
                if fracIdx not in fracSet:
                    heapq.heappush(fraqQue, (arr[fracIdx[0]] / arr[fracIdx[1]], fracIdx[0], fracIdx[1]))
                    fracSet.add(fracIdx)
            k -= 1

        return [arr[idxNum], arr[idxDen]]


x = Solution()

nums = [1, 2, 3, 5, 7]
for i in range(1, len(nums) * (len(nums) - 1) // 2 + 1):
    res = x.kthSmallestPrimeFraction(nums, i)
    print(f"{res[0]}/{res[1]}")
