// Solved

#include <stdio.h>

class Solution
{
public:
	int mySqrt(int x)
	{
		unsigned int i, k, n, r, res;

		if (x <= 1) return x;

		// Determining position of leftmost (LSB) '1' bit
		for (i = 30, n = 1 << 30; n; --i, n >>= 1) if (x & n) break;
		// Here i contains value such that 2^i <= n < 2^(i+1)

		k = i & 1;	 // If i is even, than results are in form of b:10xxx...xxx, else (i is odd) in form of b:1xxxx...xxx
		i >>= 1;	 // m is the max power of 2 in the result (non-zero MSB in other words)
		res = 1 << i; // res will tend to result

		for (n = k ? (res >> 1) : (res >> 2); n; n >>= 1)
		{
			r = res + n;
			if (r * r <= x) res = r;
		}

		return res;
	}
};


int main()
{
	Solution x;
	int i, n[] = { 4, 8, 15, 16, 31, 2147395599 };
	volatile int r;

	for (i = 0; i < sizeof(n) / sizeof(n[0]); ++i)
	{
		printf("%d - %d\n", n[i], x.mySqrt(n[i]));
	}

	for (i = 0; i < (1 << 30); i += 3)
	{
		r = x.mySqrt(i);
	}
}
