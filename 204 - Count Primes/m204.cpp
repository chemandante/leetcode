#include <cmath>

#define countof(n)     (sizeof(n)/sizeof(n[0]))

const int cnPrimeCount[] = { 0, 0, 1, 2, 2, 3 };

class Solution 
{
//private:


public:
	int countPrimes(int n)
	{
		int Cp, M, P, cNums, k, kMax, phi, r, nSqrt, coprimes_count;
		int* coprimes;

		// Decrementing M, so we will count primes up to N including N itself
		if (n > 0) n -= 1;
		// Quick answer for small N
		if (n < countof(cnPrimeCount)) return cnPrimeCount[n];

		// We will use principle of "Sieve of Eratosthenes" to count primes
		// We also assume that all 2's and 3's multiples already excluded from the Sieve,
		// so we count all numbers in form of 6 * k + 1 and 6 * k + 5 as prime candidates.
		// And we prepare to exclude composites that are 5's multiples
		//
		// At each step we take next prime Pj and try to count all numbers in form of Pj * k,
		// where 1 < k <= floor(N / Pj) and k co - prime to modulus M = P1 * P2*...*P(j - 1)
		// (modulus is the product of all primes which multiples already excluded)

		nSqrt = int(sqrt(n)) + 1;
		M = 2 * 3;			// Initial modulus equals to 2 * 3 because we start 2's and 3's excluded
		phi = 2;			// Euler's function (totient) of M, i.e. Phi(M)
		coprimes = new int[2];
		coprimes[0] = 1;	coprimes[1] = 5;		// Adding numbers co-prime to modulus M
		P = 5;		// Our next prime Pj will always be the second number in co - primes list

		// Initial count of all prime candidates. *2 means 2 co-primes (1 and 5) per each M numbers
		// +2 means we add "2" and "3" as primes; -1 means we remove "1"
		Cp = (n / M) * 2 + 2 - 1;
		r = n % M;	// Taking in mind the reminder of division N by M
		if (r == 5)		 Cp += 2;	// Adding two last prime candidates 6 * k + 1 and 6 * k + 5
		else if (r >= 1) Cp += 1;	// Adding last prime candidate 6 * k + 1

		while (P * P <= n)
		{
			kMax = n / P;  // Max value of k, so Pj * k <= N
			// Now we should count all k's such that 1 < k <= kMax and (k, M) = 1, i.e. k is co-prime to M
			cNums = (kMax / M) * phi;  // At first, we count all full inclusions of co-primes list
			k = kMax % M;  // Then, we take care of the remainder, to count co-primes element-wise
		
			for (int i = 0; i < phi; ++i)
			{
				if (coprimes[i] <= k) cNums++;
				else break;
			}

			// Deduce cNums composite numbers except for "1"
			Cp -= (cNums - 1);

			// When there will be no more full inclusions, we don't need to build expensive co-primes list,
			// so we will andavce to next stage - reducing remaining co-primes list
			if (kMax / M == 0)
			{
				// If there are more than 2 elements in co-primes list, we go to reduce stage of algorythm
				coprimes_count = phi;
				_reduceCoprimesList(&coprimes, coprimes_count, n);
				if (coprimes_count > 1) P = coprimes[1];
				else P = nSqrt;	// Skip reduce part of algorythm (P * P will always be greater than N)

				break;
			}
		
			// Well done for this step, preparing for next one(taking new prime, creating new co-primes list)
			_buildNextCoprimesList(&coprimes, M, phi);
			coprimes_count = phi;
			P = coprimes[1];	// Next prime will always lay in second cell ("1" always occupies first cell)
		}

        // Second stage. When we reach modulus M such, that n / Pj < M, we need no more expanding list, only reduce.
		while (P * P <= n)
		{
			Cp -= (coprimes_count - 1);
			// When there is more than 2 elements in the list, we need to reduce it
			if (coprimes_count > 2)
			{
				_reduceCoprimesList(&coprimes, coprimes_count, n);
				if (coprimes_count > 1) P = coprimes[1];
				else P = nSqrt;	// Skip reduce part of algorythm (P * P will always be greater than N)
			}
			else break;
		}

		delete[] coprimes;

		return Cp;
    }

private:
	// Building next co-primes list using previous one, updating modulus and totient values
	void _buildNextCoprimesList(int** coprimes, int &M, int &phi)
	{
		int i, idxNew, j, k, n, P, nPhi;
		int* old_coprimes = *coprimes;
		int* new_coprimes;
		
		P = old_coprimes[1];
		nPhi = phi * (P - 1);	// New Euler's function for new modulus
		new_coprimes = new int[nPhi];

		for (i = idxNew = k = 0; i < P; ++i, k += M)
		{
			for (j = 0; j < phi; ++j)
			{
				n = k + old_coprimes[j];
				if (n % P) new_coprimes[idxNew++] = n;
			}
		}

		M *= P;			// New modulus
		phi = nPhi;
		*coprimes = new_coprimes;
		delete[] old_coprimes;
	}

	// Reduce list of co-primes so there must not exceed our N
	void _reduceCoprimesList(int** coprimes, int &coprimes_count, int N)
	{
		int idxNew, idxOld, P, kMax, x;
		int* old_coprimes = *coprimes;
		int* new_coprimes = new int[coprimes_count];

		new_coprimes[0] = 1;

		P = old_coprimes[1];
		kMax = N / old_coprimes[2];  // Using after-next prime to determine kMax

		for (idxNew = idxOld = 0; idxOld < coprimes_count; ++idxOld)
		{
			x = old_coprimes[idxOld];
			if (x > kMax) break;
			if (x % P) new_coprimes[idxNew++] = x;
		}

		coprimes_count = idxNew;
		*coprimes = new_coprimes;
		delete[] old_coprimes;
	}
};




#include <stdio.h>
#include <ctime>

int main()
{
	Solution x;
	int n = 500000000;

	clock_t start = clock();
	printf("\n%d = %d\n", n, x.countPrimes(n));
	printf("%d, %d", clock() - start, CLOCKS_PER_SEC);
}
