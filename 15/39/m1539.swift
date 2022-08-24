// Solved:
// (E) Kth Missing Positive Number
// https://leetcode.com/problems/kth-missing-positive-number/

class Solution {
	func findKthPositive(_ arr: [Int], _ k: Int) -> Int {
		// Key idea: at position 'i' exactly 'arr[i] - i - 1' positive numbers are missing
		var l = 0, r = arr.count - 1  // Minimal and maximal possible values for result
		
		if k < arr[0]{
			return k
		}
		// Binary search for k - 1
		while r - l > 1 {
			let m = (l + r) >> 1
						
			if k - 1 >= arr[m] - m - 1 {
				l = m
			} else {
				r = m - 1
			}
		}

		// Return k - (arr[r] - r - 1) + arr[r] = k + r + 1
		if k > arr[r] - r - 1 {
			return k + r + 1
		}

		return k + l + 1
	}
}
