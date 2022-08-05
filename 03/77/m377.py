from typing import List


class Solution:
    def __init__(self):
        self.nums = []
        self.gcds = []
        self.decomp = {}

    def _calcGCD(self, a: int, b: int):
        while b:
            n = a % b
            a, b = b, n
        return a

    def _calcBinomial(self, m: int, n: int) -> int:
        if 2 * m > n:
            m = n - m
        nn = n - m + 1
        a = 1
        for i in range(1, m + 1):
            a = a * nn // i
            nn += 1
        return a

    def _calcCombinations(self, numsCount: int, target: int) -> dict:
        # print(f"Finding for {target} with list ", self.nums[0:numsCount])

        res = {}
        if numsCount == 1:
            if target % self.nums[0] == 0:
                res[target // self.nums[0]] = 1
            return res

        if target % self.gcds[numsCount - 1]:
            return res

        step = self.nums[numsCount - 1]

        nMax = target // step
        for i in range(0, nMax + 1):
            remTarget = target - i * step
            if remTarget:
                resi = self._calcCombinations(numsCount - 1, remTarget)
                for terms, permutations in resi.items():
                    n = res.get(terms + i, 0)
                    res[terms + i] = n + self._calcBinomial(i, terms + i) * permutations
            else:
                res[i] = res.get(i, 0) + 1
        return res

    def combinationSum4(self, nums: List[int], target: int) -> int:
        self.nums = sorted(nums)
        gcd = self.nums[0]
        self.gcds.append(gcd)
        for n in self.nums[1:]:
            gcd = self._calcGCD(gcd, n)
            self.gcds.append(gcd)

        res = self._calcCombinations(len(nums), target)

        return sum(res.values())


x = Solution()

nums = [10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,
        310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,
        580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,
        860,870,880,890,900,910,920,930,940,950,960,970,980,990,111]
target = 999
print(x.combinationSum4(nums, target))
