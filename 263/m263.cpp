#include <cmath>

#define countof(n)     (sizeof(n)/sizeof(n[0]))

class Solution
{
public:
	int isUgly(int n)
	{
		if (n <= 0) return false;

		// Dividing by 2 until odd number
		while ((n & 1) == 0) n >>= 1;
		// Dividing by 3 while this is possible
		n = _divideBy(n, 3);
		// Dividing by 5 while this is possible
		n = _divideBy(n, 5);

		return (n == 1) ? true : false;
	}

private:
	// Divide n by divisor while this is possible (remainder == 0), return quotient
	int _divideBy(int n, int divisor)
	{
		div_t d = div(n, divisor);

		while (!d.rem)
		{
			n = d.quot;
			d = div(n, divisor);
		}

		return n;
	}
};




#include <stdio.h>
#include <ctime>

int main()
{
	Solution x;
	int n = 333000000;

	clock_t start = clock();
	for (int i = -10; i <= 10; ++i)
	{
		printf("%d = %d\n", i, x.isUgly(i));
	}
	printf("%d, %d", clock() - start, CLOCKS_PER_SEC);
}
