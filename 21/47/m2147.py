# Solved:
# (H) Number of Ways to Divide a Long Corridor
# https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/

import math

from typing import List


class Solution:
    def numberOfWays(self, corridor: str) -> int:
        """
        All we need - count all plants in the gap between pairs of seats `gap[i]`
        Then the result is the product of all (gap[i] + 1).
        There is no need to make an array of gaps - do all the job in one pass
        Odd or zero number of seats makes the division impossible, so we return 0 in that case.
        """
        res = 1  # Result
        total_seats = 0  # Total seats, need for final check
        seats, gap = 0, 0  # Current seat and gap counters
        # We do everything in one pass, iterating char-by-char
        for c in corridor:
            if c == 'S':
                total_seats += 1
                if seats == 2:  # If we found another seat after pair, mind the gap
                    res = (res * (gap + 1)) % 1000000007
                    seats, gap = 1, 0
                else:
                    seats += 1  # Count seats till a pair will be found
            else:
                if seats == 2:  # Count plants after last seat in pair
                    gap += 1

        # Final check for the case where it's impossible to divide corridor
        if total_seats == 0 or total_seats % 2 == 1:
            res = 0

        return res
