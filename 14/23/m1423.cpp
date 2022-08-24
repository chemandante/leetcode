// Solved:
// (M) Maximum Points You Can Obtain from Cards
// https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

#include <vector>

using namespace std;

class Solution
{
public:
	int maxScore(vector<int>& cardPoints, int k)
	{
		int i, j, nSum, nSumMax;
		// At first sum all left k numbers
		for (i = nSum = 0; i < k; ++i) nSum += cardPoints[i];

		nSumMax = nSum;

		for (i = k - 1, j = cardPoints.size() - 1; i >= 0; --i, --j)
		{
			nSum += cardPoints[j] - cardPoints[i];
			if (nSum > nSumMax) nSumMax = nSum;
		}

		return nSumMax;
	}
};
