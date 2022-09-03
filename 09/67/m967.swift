// Solved:
// (M) Numbers With Same Consecutive Differences
// https://leetcode.com/problems/numbers-with-same-consecutive-differences/

class Solution {
	var res: [Int] = []
	
	func _checkNum(_ num: Int, _ lastDigit: Int, _ digits: Int, _ k: Int) {
		var x: Int
		
		if digits == 0 {
			self.res.append(num)
			return
		}
		
		x = lastDigit - k
		if x >= 0 && x <= 9 {
			_checkNum(num * 10 + x, x, digits - 1, k)
		}

		if k != 0 {
			x = lastDigit + k
			if x >= 0 && x <= 9 {
				_checkNum(num * 10 + x, x, digits - 1, k)
			}
		}
	}
	
	func numsSameConsecDiff(_ n: Int, _ k: Int) -> [Int] {
		res = []
		
		for i in 1...9 {
			_checkNum(i, i, n - 1, k)
		}
		
		return res
	}
}

var x = Solution()
print(x.numsSameConsecDiff(3, 7))
print(x.numsSameConsecDiff(2, 1))
print(x.numsSameConsecDiff(2, 0))
