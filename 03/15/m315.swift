// Solved

struct Global {
	static let minValue = -10000
	static let maxValue = 10000
	static let range = maxValue - minValue + 1
}

class Solution {
	var tree: [Int] = []
	
	func _countItem(_ item: Int) {
		var i = item + 1
		while (i > 0) && (i < Global.range + 1) {
			tree[i] += 1
			i += i & (-i)
		}
	}
	
	func _getSum(_ item: Int) -> Int {
		var res = 0, i = item
		while i > 0 {
			res += tree[i]
			i -= i & (-i)
		}
		return res
	}
	
	func countSmaller(_ nums: [Int]) -> [Int] {
		var res = Array(repeating: 0, count: nums.count)
		tree = Array(repeating: 0, count: Global.range + 1)
		
		for idx in stride(from: nums.count - 1, through: 0, by: -1) {
			let n = nums[idx] - Global.minValue
			res[idx] = _getSum(n)
			_countItem(n)
		}
		
		return res
	}
}


var x = Solution()
print(x.countSmaller([5, 2, 6, 1]))
