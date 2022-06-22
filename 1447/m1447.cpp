#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <stdint.h>

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


bool isPrime(int n)
{
	// Because 1 <= n <= 100, we need to check that n is divisible on primes p (2 <= p <= sqrt(n)) only
	const int8_t prime[] = { 2, 3, 5, 7 };

	for (int i = 0; i < sizeof(prime); ++i) if (n % prime[i] == 0) return false;

	return true;
}

class Solution
{
public:
	vector<string> simplifiedFractions(int n)
	{
		vector<string> res;
		char sz[8];
		bool bIsPrime;

		for (int i = 2; i <= n; ++i)
		{
			bIsPrime = isPrime(i);

			for (int j = 1; j < i; ++j)
			{
				// No need to calc GCD when 'i' is prime, all j's less than 'i' will be coprime to 'i'
				if (bIsPrime || calcGCD(i, j) == 1)
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

	res = x.simplifiedFractions(7);
}
