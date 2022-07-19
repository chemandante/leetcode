#include <vector>

using namespace std;

class Solution
{
private:
	void _generateNextRow(vector<int>& newRow, vector<int>& prevRow)
	{
		int nSize = prevRow.size();

		newRow.resize(nSize + 1);
		newRow[0] = newRow[nSize] = 1;

		for (int i = 1; i < nSize; ++i) newRow[i] = prevRow[i - 1] + prevRow[i];
	}

public:
	vector<vector<int>> generate(int numRows)
	{
		vector<vector<int>> res;

		res.push_back({ 1 });

		for (int i = 1; i < numRows; ++i)
		{
			res.push_back({});
			_generateNextRow(res[i], res[i - 1]);
		}

		return res;
	}
};

int main()
{
	Solution x;

	x.generate(7);

	return 0;
}
