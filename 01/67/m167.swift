// Solved

class Solution {
	func twoSum(_ numbers: [Int], _ target: Int) -> [Int] {
		var l = 0, r = numbers.count - 1
		
		while l < r {
			let s = numbers[l] + numbers[r]
			if s == target {
				return [l + 1, r + 1]
			}
			if s < target {
				l += 1
			}
			else {
				r -= 1
			}
		}
		
		return [-1]
	}
}
