// Solved:
// (E) Prime Arrangements
// https://leetcode.com/problems/prime-arrangements/

#include <stdint.h>
#include <stdio.h>

// Primes arrangements from 1 to N calculates as:
// Res = C! * (N-C)!, where C - number of primes less than or equal to N

const int c_nPrimes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
const unsigned int c_nModulus = 1000000007;

class Solution
{
private:
	uint64_t factorialModulo(unsigned int n)
	{
		uint64_t t = 1;
		for (int i = 2; i <= n; ++i) t = t * i % c_nModulus;
		return t;
	}

public:
	int numPrimeArrangements(int n)
	{
		int cPrimes;

		for (cPrimes = 0; (cPrimes < sizeof(c_nPrimes) / sizeof(c_nPrimes[0])) && (c_nPrimes[cPrimes] <= n); ++cPrimes);

		return factorialModulo(cPrimes) * factorialModulo(n - cPrimes) % c_nModulus;
	}
};


int main()
{
	Solution x;

//	printf("%d\n", x.numPrimeArrangements(5));
//	printf("%d\n", x.numPrimeArrangements(17));
	printf("%d\n", x.numPrimeArrangements(100));
}
