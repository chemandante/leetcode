// Solved
// Helper: `Swift` queue using single-linked list

public class SLListNode<T> {
	fileprivate var value: T
	fileprivate var next: SLListNode?

	public init(_ value: T) {
		self.value = value
	}
}

public class SLQueue<T> {
	private var head: SLListNode<T>?
	private var tail: SLListNode<T>?
	
	public func push(_ element: T) {
		if !isEmpty() {
			tail?.next = SLListNode<T>(element)
			tail = tail?.next
		} else {
			tail = SLListNode<T>(element)
			head = tail
		}
	}
	
	public func pop() -> T? {
		if !isEmpty() {
			let ans = head?.value
			head = head?.next
			if head == nil {
				tail = nil
			}
			return ans
		}
		return nil
	}
	
	public func isEmpty() -> Bool {
		return head == nil
	}
}


class Solution {
	func maxAreaOfIsland(_ grid: [[Int]]) -> Int {
		let que = SLQueue<(Int, Int)>()
		let xMax = grid.count - 1, yMax = grid[0].count - 1
		var g = grid
		var maxArea = 0
		
		for x in 0...xMax {
			for y in 0...yMax {
				if g[x][y] == 1 {
					var area = 0
					
					que.push((x, y))
					while !que.isEmpty() {
						if let (cx, cy) = que.pop() {
							if g[cx][cy] == 1 {
								g[cx][cy] = 0
								if cx > 0 && g[cx - 1][cy] == 1 { que.push((cx - 1, cy)) }
								if cy > 0 && g[cx][cy - 1] == 1 { que.push((cx, cy - 1)) }
								if cx < xMax && g[cx + 1][cy] == 1 { que.push((cx + 1, cy)) }
								if cy < yMax && g[cx][cy + 1] == 1 { que.push((cx, cy + 1)) }
								area += 1
							}
						}
					}
					
					if area > maxArea { maxArea = area }
				}
			}
		}
		
		return maxArea
	}
}


var x = Solution()
let grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]

print(x.maxAreaOfIsland(grid))
