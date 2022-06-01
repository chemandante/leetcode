import math

from typing import List

class Solution:
    def countPairs(self, nums: List[int], k: int) -> int:
        """
        Key idea to solve this problem is:
        N1 * N2 is divisible by K if and only if GCD(N1,K) * GCD(N2,K) is divisible by K
        So we will group all input numbers by value of GCD(number, k) and count them (using dictionary in Python).
        We do not need to keep the exact input value, just GCD(N,K) and count of numbers with such GCD.
        Then we iterate through this dictionary and try to determine when product of GCD's are divisible by K.
        When we found such pair of GCD's we count number of possible combinations in two different ways.
        One for N1 != N2 (product of number count C(N1) * C(N2), then divide by 2, because N1 * N2 = N2 * N1)
        Another for N1 == N2 - in this case we calculate number of combinations from C(N1) by 2.
        """
        gcd = {}
        res_d = 0   #
        res_s = 0
        # Grouping input numbers by GCD(n,K) value and count them
        for n in nums:
            g = math.gcd(n, k)
            gcd[g] = gcd.get(g, 0) + 1
        # Calculating combinations
        for n1, c1 in gcd.items():
            kr = k // n1
            for n2, c2 in gcd.items():
                if n2 % kr == 0:
                    if n1 == n2:
                        res_s += c1 * (c1 - 1) // 2  # Number of combinations from c1 by 2
                    else:
                        res_d += c1 * c2

        return res_d // 2 + res_s


x = Solution()
nums = [1,2,3,4,5]
k = 2

print(x.countPairs(nums, k))
# print(f"List length = {len(data.data)}")
# print(x.countPairs(data.data, data.k))
