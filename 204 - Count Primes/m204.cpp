#include <list>

#define countof(n)     (sizeof(n)/sizeof(n[0]))

typedef std::list<int> NUM_LIST;
typedef NUM_LIST::iterator	NUM_LIST_IT;

const int cnPrimeCount[] = { 0, 0, 1, 2, 2, 3 };

class Solution 
{
//private:


public:
	int countPrimes(int n)
	{
		int Cp, M, P, cNums, k, kMax, phi, r, nSqrt;

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
		NUM_LIST* coprimes = new NUM_LIST();
		coprimes->push_back(1);		coprimes->push_back(5);		// Adding numbers co-prime to modulus M

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
		
			for (NUM_LIST_IT it = coprimes->begin(); it != coprimes->end(); ++it)
			{
				if (*it <= k) cNums++;
				else break;
			}

			// Deduce cNums composite numbers except for "1"
			Cp -= (cNums - 1);

			// When there will be no more full inclusions, we don't need to build expensive co-primes list,
			// so we will andavce to next stage - reducing remaining co-primes list
			if (kMax / M == 0)
			{
				// If there are more than 2 elements in co-primes list, we go to reduce stage of algorythm
				if (coprimes->size() > 2)
				{
					_reduceCoprimesList(&coprimes, n);
					if (coprimes->size() > 1) P = *(++coprimes->begin());
					else P = nSqrt;	// Skip reduce part of algorythm (P * P will always be greater than N)
				}
				else
				{
					P = nSqrt;  // Skip reduce part of algorythm (P * P will always be greater than N)
				}

				break;
			}
		
			// Well done for this step, preparing for next one(taking new prime, creating new co-primes list)
			_buildNextCoprimesList(&coprimes, M, phi);
			P = *(++coprimes->begin());
		}

        // Second stage. When we reach modulus M such, that n / Pj < M, we need no more expanding list, only reduce.
		while (P * P <= n)
		{
			k = coprimes->size();
			Cp -= (k - 1);
			// When there is more than 2 elements in the list, we need to reduce it
			if (k > 2)
			{
				_reduceCoprimesList(&coprimes, n);
				if (coprimes->size() > 1) P = *(++coprimes->begin());
				else P = nSqrt;	// Skip reduce part of algorythm (P * P will always be greater than N)
			}
			else break;
		}

		return Cp;
    }

private:
	// Building next co-primes list using previous one, updating modulus and totient values
	void _buildNextCoprimesList(NUM_LIST** coprimes, int &M, int &phi)
	{
		int i, k, n, P;
		NUM_LIST* old_coprimes = *coprimes;
		NUM_LIST* new_coprimes = new NUM_LIST();

		P = *(++old_coprimes->begin());

		for (i = k = 0; i < P; ++i, k += M)
		{
			for (NUM_LIST_IT it = old_coprimes->begin(); it != old_coprimes->end(); ++it)
			{
				n = k + *it;
				if (n % P) new_coprimes->push_back(n);
			}
		}

		M *= P;			// New modulus
		phi *= (P - 1);	// New Euler's function for new modulus
		*coprimes = new_coprimes;
		delete old_coprimes;
	}

	// Reduce list of co-primes so there must not exceed our N
	void _reduceCoprimesList(NUM_LIST** coprimes, int N)
	{
		int P, kMax, x;
		NUM_LIST* old_coprimes = *coprimes;
		NUM_LIST* new_coprimes = new NUM_LIST();

		new_coprimes->push_back(1);

		NUM_LIST_IT it = old_coprimes->begin();
		
		P = *(++it);
		kMax = N / *(++it);  // Using after-next prime to determine kMax

		for (; it != old_coprimes->end(); ++it)
		{
			x = *it;
			if (x > kMax) break;
			if (x % P) new_coprimes->push_back(x);
		}

		*coprimes = new_coprimes;
		delete old_coprimes;
	}
};




#include <stdio.h>
#include <ctime>

int main()
{
	Solution x;
	int n = 3;

	clock_t start = clock();
	printf("\n%d = %d\n", n, x.countPrimes(n));
	printf("%d, %d", clock() - start, CLOCKS_PER_SEC);
}
