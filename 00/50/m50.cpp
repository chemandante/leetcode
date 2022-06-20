class Solution
{
public:
	double myPow(double x, int n)
	{
		bool bNeg = n < 0;
		bool bMin = n == 0x80000000;
		double res = 1;

		if (bMin) n >>= 1;
		if (bNeg) n = -n;
		// Now n is positive

		for (unsigned int u = 1 << 30; u; u >>= 1)
		{
			res *= res;
			if (n & u) res *= x;
		}

		if (bMin) res *= res;
		if (bNeg) res = 1 / res;

		return res;
	}
};

int main()
{
	Solution x;
	vector<int> a = { 0,1,0,1,0,1,99 };

	printf("%d\n", x.singleNumber(a));
}
