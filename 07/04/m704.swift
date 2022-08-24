// Solved

class Solution {
	func search(_ nums: [Int], _ target: Int) -> Int {
		var l = 0, r = nums.count - 1
		
		while l < r {
			let m = (l + r) >> 1
			if nums[m] == target { return m }
			if target < nums[m] {
				r = m - 1
			}
			else {
				l = m + 1
			}
		}
		
		return nums[l] == target ? l : -1
	}
}
