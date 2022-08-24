// Solved:
// (M) Kth Largest Element in an Array
// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include <vector>

using namespace std;

#define MIN_VALUE		-10000
#define MAX_VALUE		10000
#define TOTAL_VALUES	(MAX_VALUE - MIN_VALUE + 1)

class Solution
{
public:
	int findKthLargest(vector<int>& nums, int k)
	{
		uint16_t a[TOTAL_VALUES];	// Array contains count of 'nums' for each possible nums[i] value
		int	idx;

		memset(a, 0, sizeof(a));
		// Counting all input nums. Because -10000 <= nums[i] <= 10000, we need to correct index.
		for (auto num : nums) a[num - MIN_VALUE]++;
		// Now we iterate through an array to find needed result
		idx = TOTAL_VALUES;
		while (k > 0) k -= a[--idx];

		return idx + MIN_VALUE;
	}
};


int main()
{
	Solution x;
	vector<int> nums = { 3,2,3,1,2,4,5,5,6 };

	for (int i = 1; i <= nums.size(); ++i)
	{
		printf("%d. %d\n", i, x.findKthLargest(nums, i));
	}
}
