class Solution {
	func _calcSum(_ n: Int) -> Int {
		// If n is even (this check used to avoid overflow)
		if n & 1 == 0 {
			return (n >> 1) * (n + 1)
		} else {
			return ((n + 1) >> 1) * n
		}
	}
	
	func arrangeCoins(_ n: Int) -> Int {
		var l = 1, r = 65535  // Minimal and maximal possible values for result
		
		while r - l > 1 {
			let m = (l + r) >> 1
			let c = _calcSum(m)
			
			if n < c {
				r = m - 1
			} else {
				l = m
			}
		}

		if _calcSum(r) <= n {
			return r
		}
		
		return l
	}
}
