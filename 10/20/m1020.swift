// Solved:
// (M) Number of Enclaves
// https://leetcode.com/problems/number-of-enclaves/

class Solution {
	typealias Coord = (x: Int, y: Int)
	
	private func _processEnclave(_ grid: inout [[Int]], _ x: Int, _ y: Int) -> Int {
		let xmax = grid.count - 1, ymax = grid[0].count - 1
		var tile: [Coord] = [(x, y)]
		var nEnclave = 0
		
		grid[x][y] = 0
		while !tile.isEmpty {
			let c = tile.removeLast()
			// If the tile is on bound, this is not an enclave
			if c.x == 0 || c.y == 0 || c.x == xmax || c.y == ymax { nEnclave = -1 }
			if nEnclave >= 0 { nEnclave += 1 }
			if c.x > 0 && grid[c.x - 1][c.y] == 1 { grid[c.x - 1][c.y] = 0; tile.append((c.x - 1, c.y)) }
			if c.y > 0 && grid[c.x][c.y - 1] == 1 { grid[c.x][c.y - 1] = 0; tile.append((c.x, c.y - 1)) }
			if c.x < xmax && grid[c.x + 1][c.y] == 1 { grid[c.x + 1][c.y] = 0; tile.append((c.x + 1, c.y)) }
			if c.y < ymax && grid[c.x][c.y + 1] == 1 { grid[c.x][c.y + 1] = 0; tile.append((c.x, c.y + 1)) }
		}
		
		return nEnclave > 0 ? nEnclave : 0
	}
	
	func numEnclaves(_ grid: [[Int]]) -> Int {
		var g = grid
		var res = 0
		
		// Obvious case - no inner tiles at all
		if g.count <= 2 || g[0].count <= 2 { return 0 }
		
		for i in 1..<g.count - 1 {
			for j in 1..<g[0].count - 1 {
				if g[i][j] == 1 {
					res += _processEnclave(&g, i, j)
				}
			}
		}
		
		return res
	}
}

func _main() {
	let x = Solution()
	// Must be 3
	print(x.numEnclaves([[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]))
	// Must be 27
	print(x.numEnclaves([[0,0,0,1,1,1,0,1,1,1,1,1,0,0,0],[1,1,1,1,0,0,0,1,1,0,0,0,1,1,1],[1,1,1,0,0,1,0,1,1,1,0,0,0,1,1],[1,1,0,1,0,1,1,0,0,0,1,1,0,1,0],[1,1,1,1,0,0,0,1,1,1,0,0,0,1,1],[1,0,1,1,0,0,1,1,1,1,1,1,0,0,0],[0,1,0,0,1,1,1,1,0,0,1,1,1,0,0],[0,0,1,0,0,0,0,1,1,0,0,1,0,0,0],[1,0,1,0,0,1,0,0,0,0,0,0,1,0,1],[1,1,1,0,1,0,1,0,1,1,1,0,0,1,0]]))
}
