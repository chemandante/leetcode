// Solved:
// (M) Find Minimum in Rotated Sorted Array
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

class Solution {
	func _findLag(_ nums: [Int]) -> Int {
		var l = 1, r = nums.count - 1
		let n = nums[0]
		
		while r - l > 1 {
			let m = (l + r) >> 1
			if nums[m] < n { r = m }
			else { l = m + 1 }
		}
		
		if nums[l] < n { return l }
		if nums[r] < n { return r }
		return 0
	}

	func findMin(_ nums: [Int]) -> Int {
		// Obvious case
		if nums.count == 1 { return nums[0] }
		// In other case find rotation lag
		let idx = _findLag(nums)
		return nums[idx]
	}
}
