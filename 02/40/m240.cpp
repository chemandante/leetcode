// Solved:
// (M) Search a 2D Matrix II
// https://leetcode.com/problems/search-a-2d-matrix-ii/

#include <vector>

using namespace std;

class Solution
{
private:
	bool searchInRow(vector<int>& row, int target)
	{
		int l, m, r, x;

		l = 0, r = row.size() - 1;

		while (l <= r)
		{
			m = (l + r) >> 1;
			x = row[m];
			if (x == target) return true;
			if (target < x) r = m - 1;
			else l = m + 1;
		}

		return false;
	}

	bool searchInColumn(vector<vector<int>>& matrix, int column, int target)
	{
		int l, m, r, x;

		l = 0, r = matrix.size() - 1;

		while (l <= r)
		{
			m = (l + r) >> 1;
			x = matrix[m][column];
			if (x == target) return true;
			if (target < x) r = m - 1;
			else l = m + 1;
		}

		return false;
	}

public:
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int r = matrix.size();
		int c = matrix[0].size();
		int i, j, x;

		// Use binary search for flattened matrix (when one dimension more than 4 times bigger than other)
		if (r < 4 * c && c < 4 * r)
		{
			i = r - 1, j = 0;
			// Search by diagonal from left bottom, going one cell up if target is less than current cell or
			// one cell right if the target is greater
			while (i >= 0 && j < c)
			{
				x = matrix[i][j];
				if (x == target) return true;
				if (target < x) --i;
				else ++j;
			}
		}
		else if (r > c)
		{
			for (i = 0; i < c; ++i)
				if (searchInColumn(matrix, i, target)) return true;
		}
		else
		{
			for (i = 0; i < r; ++i)
				if (searchInRow(matrix[i], target)) return true;
		}
		
		return false;
	}
};

int main()
{
	Solution x;
	vector<vector<int>> matrix = { {1, 1} };

	auto res = x.searchMatrix(matrix, 2);

	return 0;
}
