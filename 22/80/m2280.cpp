// Solved:
// (M) Minimum Lines to Represent a Line Chart
// https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/
// GCD:

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <stdint.h>

using namespace std;

int calcGCD(int a, int b)
{
	int n;

	if (b == 0) return 1;

	while (b)
	{
		n = a % b;
		a = b;
		b = n;
	}

	return a;
}

void simplify(int& a, int& b)
{
	int gcd = calcGCD(a, b);
	if (gcd < 0) gcd = -gcd;
	a /= gcd;
	b /= gcd;
}

class Solution
{
public:
	int minimumLines(vector<vector<int>>& stockPrices)
	{
		vector<vector<int>>::iterator	it, itp;
		int a, b, ap, bp, nCnt;
		
		sort(stockPrices.begin(), stockPrices.end());

		// If there is two points, there will be 1 line. For 1 point, there will be no line.
		if (stockPrices.size() <= 2) return stockPrices.size() - 1;

		ap = stockPrices[1][0] - stockPrices[0][0];
		bp = stockPrices[1][1] - stockPrices[0][1];
		simplify(ap, bp);
		nCnt = 1;

		itp = stockPrices.begin() + 1;
		it = itp + 1;

		while (it != stockPrices.end())
		{
			a = (*it)[0] - (*itp)[0];
			b = (*it)[1] - (*itp)[1];
			simplify(a, b);

			if (a != ap || b != bp) nCnt++;

			ap = a; bp = b;
			itp = it++;
		}

		return nCnt;
	}
};

int main()
{
	Solution x;
	vector<vector<int>> stockPrices = { {2, 6}, {1, 7}, {3, 5}, {4, 4}, {5, 4}, {6, 3}, {7, 2}, {8, 1} };
	//vector<string> res;

	int res = x.minimumLines(stockPrices);
}
