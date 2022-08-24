// Solved:
// (E) Intersection of Two Arrays II
// https://leetcode.com/problems/intersection-of-two-arrays-ii/

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
private:
	int _searchLeftmost(vector<int>* pNums, int leftIdx, int target)
	{
		int l, m, r;

		l = leftIdx, r = pNums->size() - 1;

		while (r - l > 1)
		{
			m = (l + r) >> 1;
			if (target <= (*pNums)[m]) r = m;
			else l = m + 1;
		}

		if ((*pNums)[l] == target) return l;
		if ((*pNums)[r] == target) return r;
		return -1;
	}

public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int>* p1, * p2; // p1 points will to smaller array
		vector<int> res;
		int leftIdx = 0;

		if (nums1.size() < nums2.size()) p1 = &nums1, p2 = &nums2, res.reserve(nums2.size());
		else p1 = &nums2, p2 = &nums1, res.reserve(nums1.size());

		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		
		leftIdx = 0;
		for (int n : *p1)
		{
			int idx = _searchLeftmost(p2, leftIdx, n);
			if (idx >= 0)
			{
				res.push_back(n);
				leftIdx = idx + 1;
				if (leftIdx >= p2->size()) break;
			}
		}

		return res;
	}
};


int main()
{
	Solution x;

	vector<int> nums1 = { 2, 2 };
	vector<int> nums2 = { 1, 2, 2, 1 };
	x.intersect(nums1, nums2);

	nums1 = { 21, 47, 80, 4, 3, 24, 87, 12, 22, 11, 48, 6, 89, 80, 74, 71, 74, 55, 58, 56, 4, 98, 40, 66, 49, 53, 62, 27, 3, 66,
		78, 24, 48, 69, 88, 12, 80, 63, 98, 65, 46, 35, 72, 5, 64, 72, 7, 29, 37, 3, 2, 75, 44, 93, 79, 78, 13, 39, 85, 26, 15, 41,
		87, 47, 29, 93, 41, 74, 6, 48, 17, 89, 27, 61, 2, 68, 99, 57, 45, 73, 25, 33, 38, 32, 58 };

	nums2 = { 1, 39, 6, 81, 85, 10, 38, 22, 0, 89, 57, 93, 58, 69, 65, 80, 84, 24, 27, 54, 37, 36, 26, 88, 2, 7, 24, 36, 51, 5, 74,
		57, 45, 56, 55, 67, 25, 33, 78, 49, 16, 79, 74, 80, 36, 27, 89, 49, 64, 73, 96, 60, 92, 31, 98, 72, 22, 31, 0, 93, 70, 87,
		80, 66, 75, 69, 81, 52, 94, 90, 51, 90, 74, 36, 58, 38, 50, 9, 64, 55, 4, 21, 49, 60, 65, 47, 67, 8, 38, 83 };
	vector<int> res = x.intersect(nums1, nums2);

	return 0;
}
