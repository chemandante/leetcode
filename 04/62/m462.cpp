#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
	int minMoves2(vector<int>& nums)
	{
		int i, m, middle, n, res;

		middle = nums.size() >> 1;
		// At first we sort the array
		nth_element(nums.begin(), nums.begin() + middle, nums.end());
		// Find median
		m = nums[middle];
		// Calculating 'moves'
		for (i = res = 0; i < nums.size(); ++i)
		{
			n = nums[i] - m;
			if (n > 0) res += n;
			else	   res -= n;
		}

		return res;
	}
};


int main()
{
	Solution x;
	vector<int> nums = { 1, 10, 2, 9 };

	printf("%d\n", x.minMoves2(nums));
}
