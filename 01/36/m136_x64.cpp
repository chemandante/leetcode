#include <vector>

using namespace std;

constexpr auto MIN_VALUE = -30000;
constexpr auto MAX_VALUE = 30000;
#define VALUES_COUNT	(MAX_VALUE - MIN_VALUE + 1)
#define countof(x)		(sizeof(x)/sizeof(x[0]))

class Solution
{
private:
	int getBitNum(uint64_t x)
	{
		int u = 32, n = 0;

		while (u)
		{
			if (x >> u)
			{
				x >>= u;
				n += u;
			}

			u >>= 1;
		}

		return n;
	}

public:
	int singleNumber(vector<int>& nums)
	{
		uint64_t u1[(VALUES_COUNT + 63) / 64];
		uint64_t u2[(countof(u1) + 63) / 64], u;
		int		 n;

		memset(u1, 0, sizeof(u1));
		memset(u2, 0, sizeof(u2));

		// Checking every num
		for (auto num : nums)
		{
			printf("%d - %d\n", num, getBitNum(num));

			n = num - MIN_VALUE;
			u1[n >> 6] ^= (1ull << (n & 0x3F));
			
			n >>= 6;
			if (u1[n])	u2[n >> 6] |= (1ull << (n & 0x3F));
			else		u2[n >> 6] &= ~(1ull << (n & 0x3F));
		}

		for (int i = 0; i < countof(u2); ++i)
		{
			if (u = u2[i])
			{
				i = (i << 6) + getBitNum(u);
				u = u1[i];
				return (i << 6) + getBitNum(u) + MIN_VALUE;
			}
		}

		return 0;
	}
};


int main()
{
	Solution x;
	vector<int> a = { -30000, -29000, 28001, -30000, -29000 };

	printf("%d\n", x.singleNumber(a));
}
