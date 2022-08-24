// Solved:
// (M) Gray Code
// https://leetcode.com/problems/gray-code/

#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> grayCode(int n)
	{
		vector<int> res;
		for (int i = 0; i < (1 << n); ++i) res.push_back(i ^ (i >> 1));
		return res;
	}
};

int main()
{
	Solution x;

	auto res = x.grayCode(4);
}
