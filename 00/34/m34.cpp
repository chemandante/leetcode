// Solved:
// (M) Find First and Last Position of Element in Sorted Array
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include <vector>

using namespace std;

class Solution
{
private:
	int searchLeftmost(vector<int>& nums, int target)
	{
		int l, m, r;

		l = 0, r = nums.size() - 1;

		while (r - l > 1)
		{
			m = (l + r) >> 1;
			if (target <= nums[m]) r = m;
			else l = m + 1;
		}

		if (nums[l] == target) return l;
		if (nums[r] == target) return r;
		return -1;
	}

	int searchRightmost(vector<int>& nums, int startIdx, int target)
	{
		int l, m, r;

		l = startIdx, r = nums.size() - 1;

		while (r - l > 1)
		{
			m = (l + r) >> 1;
			if (target >= nums[m]) l = m;
			else r = m - 1;
		}

		if (nums[r] == target) return r;
		if (nums[l] == target) return l;
		return -1;
	}


public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		int l, r;

		if (nums.size() == 0) return { -1, -1 };

		l = searchLeftmost(nums, target);
		if (l < 0) return { -1, -1 };
		r = searchRightmost(nums, l, target);
		return { l, r };
	}
};

int main()
{
	Solution x;
	vector<int> nums = { 1 };

	auto res = x.searchRange(nums, 1);

	return 0;
}
