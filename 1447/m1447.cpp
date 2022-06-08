#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>

using namespace std;

int calcGCD(int a, int b)
{
	int n;

	while (b)
	{
		n = a % b;
		a = b;
		b = n;
	}

	return a;
}

class Solution
{
public:
	vector<string> simplifiedFractions(int n)
	{
		vector<string> res;
		char sz[8];

		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j < i; ++j)
			{
				if (calcGCD(i, j) == 1)
				{
					sprintf(sz, "%d/%d", j, i);
					res.push_back(sz);
				}
			}
		}

		return res;
	}
};

int main()
{
	Solution x;
	vector<string> res;

	res = x.simplifiedFractions(5);
}
