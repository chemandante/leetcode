// Solved:
// (E) Merge Sorted Array
// https://leetcode.com/problems/merge-sorted-array/

#include <vector>

using namespace std;

class Solution
{
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		int idxw, idxr1, idxr2;

		idxw = m + n - 1;
		idxr1 = m - 1;
		idxr2 = n - 1;

		while (idxw >= 0)
		{
			if (idxr2 < 0) break;

			if ((idxr1 >= 0) && (nums1[idxr1] > nums2[idxr2]))
			{
				nums1[idxw] = nums1[idxr1];
				idxr1--;
			}
			else
			{
				nums1[idxw] = nums2[idxr2];
				idxr2--;
			}

			idxw--;
		}
	}
};

//#define TEST_RESULT

int main()
{
	Solution x;
	vector<int> v1 = { 1,2,3,0,0,0 };
	vector<int> v2 = { 2, 5, 6 };

	x.merge(v1, 3, v2, 3);

	return 0;
}
