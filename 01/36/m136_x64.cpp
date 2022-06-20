#include <vector>

using namespace std;

#define countof(x)		(sizeof(x)/sizeof(x[0]))

class Solution
{
public:
	int singleNumber(vector<int>& nums)
	{
		unsigned int	u = 0;

		// Checking every num
		for (auto num : nums) u ^= (unsigned int)num;

		return (int)u;
	}
};


int main()
{
	Solution x;
	vector<int> a = { -30000, -29000, 28001, -30000, -29000 };

	printf("%d\n", x.singleNumber(a));
}
