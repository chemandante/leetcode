#include <vector>

using namespace std;

class Solution
{
public:
	int singleNumber(vector<int>& nums)
	{
		int	i, nBitCnt[32], n;
		unsigned int u;

		memset(nBitCnt, 0, sizeof(nBitCnt));

		// Checking every num
		for (auto num : nums)
		{
			for (i = 0, n = num; i < 32; ++i, n >>= 1) if (n & 1) ++nBitCnt[i];
		}

		for (i = n = 0, u = 1; i < 32; ++i, u <<= 1)
		{
			if (nBitCnt[i] % 3) n |= u;
		}

		return n;
	}
};


int main()
{
	Solution x;
	vector<int> a = { 0,1,0,1,0,1,99 };

	printf("%d\n", x.singleNumber(a));
}
