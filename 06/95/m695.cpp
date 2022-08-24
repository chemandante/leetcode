// Solved:
// (M) Max Area of Island
// https://leetcode.com/problems/max-area-of-island/

#include <queue>
#include <vector>

using namespace std;

class Solution
{
public:
	int maxAreaOfIsland(vector<vector<int>>& grid)
	{
		queue<uint16_t> que;
		int	nMax = 0, cRows = grid.size(), cCols = grid[0].size();
		int i, j, curr, ci, cj, n;

		for (i = 0; i < cRows; ++i)
		{
			for (j = 0; j < cCols; ++j)
			{
				if (grid[i][j])
				{
					n = 0;
					que.push((i << 8) + j);
					while (!que.empty())
					{
						curr = que.front(); que.pop();
						ci = curr >> 8;	cj = curr & 0xFF;
						if (grid[ci][cj])
						{
							n++;
							if (ci > 0) que.push(((ci - 1) << 8) + cj);		// Upper
							if (ci < cRows - 1) que.push(((ci + 1) << 8) + cj);// Lower
							if (cj > 0) que.push((ci << 8) + cj - 1);			// Left
							if (cj < cCols - 1) que.push((ci << 8) + cj + 1);	// Right
							grid[ci][cj] = 0;
						}
					}

					if (n > nMax) nMax = n;
				}
			}
		}

		return nMax;
	}
};

