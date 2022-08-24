// Solved:
// (H) Permutation Sequence
// https://leetcode.com/problems/permutation-sequence/

#include <stdlib.h>
#include <string>

using namespace std;

class Solution
{
private:
	void swapAndShift(char* psz, int k)
	{
		char temp = psz[k];
		while (k--) psz[k + 1] = psz[k];
		psz[0] = temp;
	}

public:
	string getPermutation(int n, int k)
	{
		// Factorials from 2! to (nMax-1)! (nMax = 9)
		const int anDenominator[] = { 2, 6, 24, 120, 720, 5040, 40320 };
		char	szResult[] = "123456789";	// Item to use in permutations
		int		i, ii, idx;
		div_t	d;

		k--;	// From 1-indexed to 0-indexed

		for (i = 0, idx = n - 2 - 1; i < n - 2; ++i, --idx)
		{
			d = div(k, anDenominator[idx]);
			swapAndShift(szResult + i, d.quot);
			k = d.rem;
		}

		if (k) swapAndShift(szResult + i, 1);
		szResult[n] = 0;

		return szResult;
	}
};

int main()
{
	Solution x;

	for (int i = 1; i <= 24; ++i)
		printf("%d - %s\n", i, x.getPermutation(4, i).c_str());
}
