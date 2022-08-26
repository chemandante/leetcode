#include <algorithm>
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
		vector<int>		aGCD(14, 0);  // Maximal GCD that nums[idx] has with any other num in nums
		int nLen = nums.size();
		int i, j, iScore, res;

		// Creating list of all possible pairs and their GCD's
		for (i = 1; i < nLen; ++i)
		{
			for (j = 0; j < i; ++j)
			{
				int gcd = calcGCD(nums[i], nums[j]);
				if (gcd > aGCD[i]) aGCD[i] = gcd;
				if (gcd > aGCD[j]) aGCD[j] = gcd;
			}
		}

		sort(aGCD.begin(), aGCD.end(), greater<int>());

//		qsort(aGCD, sizeof(aGCD) / sizeof(aGCD[0]), sizeof(aGCD[0], );

		//listGCD.sort(cmp);

		//for (iScore = nLen >> 1, res = 0; iScore; iScore--)
		//{
		//	gcd = *listGCD.begin();
		//	printf("%d,  ", gcd.gcd);
		//	res += iScore * gcd.gcd;

		//	for (auto it = listGCD.begin(); it != listGCD.end();)
		//	{
		//		if ((*it).a == gcd.a || (*it).b == gcd.b || (*it).b == gcd.a || (*it).a == gcd.b)
		//		{
		//			it = listGCD.erase(it);
		//		}
		//		else ++it;
		//	}
		//}

		return res;
	}
};

int main()
{
	Solution x;
	vector<int> nums = { 109497,983516,698308,409009,310455,528595,524079,18036,341150,641864,913962,421869,943382,295019 };

	printf("%d\n", x.maxScore(nums));
}

//      0    1    2    3    4    5    6    7    8    9   10   11   12   13
// 0 -
// 1 - 19
// 2 -  1    4
// 3 -  1    1    1
// 4 -  3    1    1    1
// 5 -  1    1    1    1    5
// 6 -  3    1    1    1    9    1
// 7 -  3    4    4    1    9    1    9
// 8 -  1    2    2    1    5    5    1    2
// 9 -  1    4    4    1    1    1    1    4    2
//10 -  3    2    2    1    3    1    3    6    2    2
//11 -  3    1    1    1    3    1    3    3    1    1   21
//12 -  1    2    2    1    1    1    1    2    2    2    2    1
//13 -  1    1    1    1    1    1    1    1    1    1   47    1    1