// Solved:
// (M) Binary Tree Pruning
// https://leetcode.com/problems/binary-tree-pruning/
// Helper: Building TreeNode’s tree from array

// Definition for a binary tree node.
public class TreeNode {
	public var val: Int
	public var left: TreeNode?
	public var right: TreeNode?
	public init() { self.val = 0; self.left = nil; self.right = nil; }
	public init(_ val: Int) { self.val = val; self.left = nil; self.right = nil; }
	public init(_ val: Int, _ left: TreeNode?, _ right: TreeNode?) {
		self.val = val
		self.left = left
		self.right = right
	}
	public init(_ array: [Int?]) { val = array[0]!; _addNode(array, 0) }
	
	private func _addNode(_ array: [Int?], _ idxNode: Int) {
		for i in 1...2 {
			let idx = 2 * idxNode + i

			if idx < array.count && array[idx] != nil {
				let newNode = TreeNode(array[idx]!)
				newNode._addNode(array, idx)
				
				if i == 1 { left = newNode }
				else	  { right = newNode }
			}
		}
	}
}

class Solution {
	func _pruneNode(_ node: TreeNode) -> Bool {
		var bPrune = node.val == 0
		
		if let n = node.left {
			if _pruneNode(n) { node.left = nil }
			else { bPrune = false }
		}
		if let n = node.right {
			if _pruneNode(n) { node.right = nil }
			else { bPrune = false }
		}
		
		return bPrune
	}
	
	func pruneTree(_ root: TreeNode?) -> TreeNode? {
		if let node = root {
			if _pruneNode(node) { return nil }
		}
		return root
	}
}

var x = Solution()
let tree = TreeNode([1,nil,0,nil, nil, 0,1])
let trep = x.pruneTree(tree)
