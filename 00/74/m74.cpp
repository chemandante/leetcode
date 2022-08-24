// Solved

#include <vector>

using namespace std;

class Solution
{
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int cols = matrix[0].size();
		int l, m, r, row, x;

		l = 0, r = matrix.size() * cols - 1;

		while (l <= r)
		{
			m = (l + r) >> 1;
			row = m / cols;
			x = matrix[row][m - row * cols];
			if (x == target) return true;
			if (target < x) r = m - 1;
			else l = m + 1;
		}

		return false;
	}
};

int main()
{
	Solution x;
	vector<vector<int>> matrix = { {1, 3} };

	auto res = x.searchMatrix(matrix, 3);

	return 0;
}
