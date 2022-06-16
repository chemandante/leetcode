#include <stdio.h>
#include <stdlib.h>

#define INT_MAX		((1u << 31) - 1)

class Solution
{
public:
	int reverse(int x)
	{
		div_t	d;
		int		n = 0;
		bool	bNeg = x < 0;

		if (bNeg)
		{
			if (x == 0x80000000) return 0;	// Reverse of -2^31 in not in range [-2^31 ... 2^31 - 1]
			else x = -x;
		}

		while (x)
		{
			d = div(x, 10);
			// Integer overflow occurs, return 0
			if (n > (INT_MAX - d.rem) / 10) return 0;

			n = 10 * n + d.rem;
			x = d.quot;
		}

		return bNeg ? -n : n;
	}
};

int main()
{
	Solution x;
	int a[] = { 1, 4, -5, 32362751, 1999999999, (1u << 31) - 1, 1u << 31 };

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		printf("%d - %d\n", a[i], x.reverse(a[i]));
	}

	return 0;
}
