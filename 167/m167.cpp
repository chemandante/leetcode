#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> twoSum(vector<int>& numbers, int target)
	{
		vector<int>::iterator it1 = numbers.begin(), it2 = numbers.end() - 1;
		int idx1 = 1, idx2 = numbers.size(), nSum;

		while (it1 != it2)
		{
			nSum = *it1 + *it2;
			if (nSum == target) return { idx1, idx2 };
			else if (nSum < target) it1++, idx1++;
			else it2--, idx2--;
		}

		return { 0, 0 };
	}
};

int main()
{
	Solution x;
	vector<int> stockPrices = { 2,7,11,15 };
	//vector<string> res;

	auto res = x.twoSum(stockPrices, 13);
}
