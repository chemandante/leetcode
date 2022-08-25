// Solved:
// (H) Kth Smallest Number in Multiplication Table
// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/

class Solution {
	/// Function returns count of numbers in multiplication table that are less then or equal to `x`
	/// - Parameters:
	///   - m: size of multiplication table, m <= n
	///   - n: size of multiplication table, n >= m
	///   - x: number `x`
	/// - Returns: Count of numbers less than or equal to `x`
	func _howManyNumbers(_ m: Int, _ n: Int, _ x: Int) -> Int {
		var res = x < n ? x : n
		for i in 2...m {
			let y = x / i
			res += y < n ? y : n
		}
		return res
	}
	
	func findKthNumber(_ m: Int, _ n: Int, _ k: Int) -> Int {
		var a: Int, b: Int
		// a and b are size of multiplication table, where always a <= b
		if m < n { a = m; b = n	}
		else	 { a = n; b = m }
		// Obvious case for table 1 x n
		if a == 1 { return k }
		// Using binary search to find minimum value v(x) such that v(x) >= k
		var l = 1, r = m * n
		while r - l > 1 {
			let x = (l + r) >> 1
			let v = _howManyNumbers(a, b, x)
			if v >= k { r = x }
			else { l = x + 1 }
		}
		
		if _howManyNumbers(a, b, l) >= k { return l }
		else { return r }
	}
}
