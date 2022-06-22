#include <list>
#include <vector>

using namespace std;

struct sGCD
{
	uint32_t	gcd;
	uint8_t		a, b;
};

bool cmp(const sGCD& a, const sGCD& b)
{
	return a.gcd > b.gcd;
}

int calcGCD(int a, int b)
{
	int n;

	while (b)
	{
		n = a % b;	a = b;	b = n;
	}

	return a;
}

class Solution
{
public:
	int maxScore(vector<int>& nums)
	{
		list<sGCD>	listGCD;
		sGCD		gcd;
		int nLen = nums.size();
		int i, j, iScore, res;

		// Creating list of all possible pairs and their GCD's
		for (i = 0; i < nLen - 1; ++i)
			for (j = i + 1; j < nLen; ++j)
			{
				gcd.gcd = calcGCD(nums[i], nums[j]);
				gcd.a = i;
				gcd.b = j;

				listGCD.push_back(gcd);
			}

		listGCD.sort(cmp);

		for (iScore = nLen >> 1, res = 0; iScore; iScore--)
		{
			gcd = *listGCD.begin();
			
			res += iScore * gcd.gcd;

			for (auto it = listGCD.begin(); it != listGCD.end();)
			{
				if ((*it).a == gcd.a || (*it).b == gcd.b || (*it).b == gcd.a || (*it).a == gcd.b)
				{
					it = listGCD.erase(it);
				}
				else ++it;
			}
		}

		return res;
	}
};

int main()
{
	Solution x;
	vector<int> nums = { 109497,983516,698308,409009,310455,528595,524079,18036,341150,641864,913962,421869,943382,295019 };

	printf("%d\n", x.maxScore(nums));
}
