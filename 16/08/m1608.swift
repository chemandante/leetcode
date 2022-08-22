class Solution {
	func _findX(_ nums: [Int], _ l: Int, _ r: Int) -> Int {
		if l >= r {
			return nums[l] >= nums.count - l ? l : -1
		}
		
		let m = (l + r) >> 1
		if nums[m] >= nums.count - m {
			let r = _findX(nums, l, m - 1)
			return r >= 0 ? r : m
		}
		else {
			return _findX(nums, m + 1, r)
		}
	}
	
	func specialArray(_ nums: [Int]) -> Int {
		let n = nums.sorted()
		let i = _findX(n, 0, n.count - 1)
		let x = n.count - i
		if i < 0 { return i }
		if i == 0 { return x }
		return n[i - 1] < x ? x : -1
	}
}

var x = Solution()
print(x.specialArray([3, 5]))
print(x.specialArray([0, 0]))
assert(x.specialArray([1,0,0,6,4,9]) == 3)
assert(x.specialArray([0,5,0,1,8,3,0,1]) == 3)
assert(x.specialArray([2, 0, 6, 0, 0, 7, 7, 0]) == 3)
