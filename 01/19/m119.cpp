// Solved:
// (E) Pascal's Triangle II
// https://leetcode.com/problems/pascals-triangle-ii/

#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> getRow(int rowIndex)
	{
		vector<int> res;
		int i, num, den;
		int64_t n;

		res.resize(rowIndex + 1);
		// First and last values
		res[0] = n = 1; res[rowIndex] = 1;
		// First half
		for (i = 1, num = rowIndex, den = 1; i <= rowIndex >> 1; ++i, --num, ++den) res[i] = n = n * num / den;
		// Last half - just copy mirrored first half (take in mind even or odd row)
		num = (rowIndex & 1) ? i - 1 : i - 2;
		for (; i < rowIndex; ++i, --num) res[i] = res[num];

		return res;
	}
};

int main()
{
	Solution x;

	x.getRow(8);

	return 0;
}
