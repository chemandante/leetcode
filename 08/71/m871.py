# Solved:
# (H) Minimum Number of Refueling Stops
# https://leetcode.com/problems/minimum-number-of-refueling-stops/

import heapq
from typing import List


class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        gas = []
        pos = res = 0
        tank = startFuel
        stations.append([target, 0])

        for location, fuel in stations:
            tank -= location - pos
            pos = location
            # If we can reach target using `tank` of fuel
            while gas and tank < 0:
                tank += -heapq.heappop(gas)
                res += 1
            if tank < 0: return -1
            # Keep gas station for now
            heapq.heappush(gas, -fuel)

        return res


x = Solution()
assert(x.minRefuelStops(100, 50, [[25, 50], [50, 25]]) == 1)
assert(x.minRefuelStops(100, 50, [[25, 30]]) == -1)
assert(x.minRefuelStops(100, 1, [[10, 100]]) == -1)
assert(x.minRefuelStops(100, 10, [[10, 60], [20, 30], [30, 30], [60, 40]]) == 2)

print(x.minRefuelStops(1000000000, 145267354, [[37587325, 32582779], [69935023, 140552490], [93414893, 87231000],
                                               [131692003, 999647], [219236253, 88160351], [290784304, 197848074],
                                               [306832014, 42375906], [308679439, 103294771], [313537374, 118370067],
                                               [366333604, 140518104], [422832806, 26574965], [472153186, 192178796],
                                               [477665743, 51433599], [518936980, 167337915], [532385582, 104311933],
                                               [608558000, 134986710], [699545847, 25291289], [714014580, 79661007],
                                               [815948878, 58336600], [824112394, 35271150], [827702356, 9780441],
                                               [873534862, 67209486], [897404362, 146737554], [921374616, 3654954],
                                               [974668629, 122229665]]))

print(x.minRefuelStops(1000000000, 145267354, [[5510987, 84329695], [10682248, 76273791], [56227783, 136858069],
                                               [91710087, 18854476], [111148380, 127134059], [165982642, 122930004],
                                               [184216180, 124802819], [217578071, 7123113], [233719001, 95862544],
                                               [339631786, 7676497], [349762649, 136128214], [403119403, 21487501],
                                               [423890164, 61095325], [424072629, 50415446], [572994480, 13561367],
                                               [609623597, 69207102], [662818314, 84432133], [678679727, 20403175],
                                               [682325369, 14288077], [702137485, 6426204], [716318901, 47662322],
                                               [738137702, 129579140], [761962118, 23765733], [820353983, 70497719],
                                               [895811889, 75533360]]))

print()
