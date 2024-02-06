// Solved:
// (H) Number of Beautiful Partitions
// https://leetcode.com/problems/number-of-beautiful-partitions

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

//
// Key idea:
//
// 1. Preprocessing of the input string
// We need to find all places where we can divide original string. Than we'll count lengths of those partitions
// 
// Ex., we have: 23542185131 | Lets substitute prime digit with 'P' and all others with '.':
//               PPP.P..P.P. | Possible partition places are combinations of '.P' (marked with '^')
//                   ^  ^ ^  | and parts are:
//               AAAABBBCCDD | so array of lengths `m_len` will be { 4, 3, 2, 2 }
// It should be taken in mind, that leftmost and rightmost partitions can not be less than `minLength`,
// so for example above, for minLength == 3 last '.P' can be ignored, so `m_len` will be { 4, 3, 4 }
//

class Solution
{
private:
	int* m_pRes;	// Prt to array of intermediate results
	uint16_t *m_pLen; // Ptr to array of partition lengths between all possible divisions
	int	m_cLen; // Size of m_pLen

	void preprocessString(string& s, int minLength)
	{
		const uint8_t aPrime[9] = { 0, 1, 1, 0, 1, 0, 1, 0, 0 }; // Is the digit prime
		uint16_t aLen[500];	// Because max len of string is 1000 and len of separator is 2 ('.P')
		int i, j, n, sumn;
		uint8_t isPrimePrev, isPrime;

		// First digit must be prime, the last - non-prime
		if (!aPrime[s.front() - 0x31] || aPrime[s.back() - 0x31]) return;

		isPrimePrev = aPrime[s[minLength - 1] - 0x31];
		
		for (i = sumn = 0, j = n = minLength; j <= s.length() - minLength; ++j, ++n)
		{
			isPrime = aPrime[s[j] - 0x31];
			// When sequense '.P' found (see key idea)
			if (isPrime && !isPrimePrev)
			{
				//printf("Mark! %d %d\n", j, n);
				aLen[i++] = n;
				sumn += n;
				n = 0;
			}
			
			isPrimePrev = isPrime;
		}

		// At least one mark found
		if (i)
		{
			size_t l;
			// Store last partition len
			aLen[i++] = s.length() - sumn;
			// Copy from stack to m_pLen
			l = (size_t)i * sizeof(uint16_t);
			m_pLen = (uint16_t*)malloc(l);
			memcpy(m_pLen, aLen, l);
			m_cLen = i;
		}
	}

	int countPartitions(int startIdx, int k, int minLength)
	{
		int i, l, res;

		// Seek in intermediate results table
		if (m_pRes[k * m_cLen + startIdx] >= 0) return m_pRes[k * m_cLen + startIdx];

		// If there are less possible divisions than needed, return 0 -- no way
		if (m_cLen - startIdx < k)
		{
			res = 0;
			goto exit;
		}

		if (k == 1) // Check if it is possible to have last partition not less than minLength
		{
			for (res = 0, i = startIdx; i < m_cLen; ++i)
			{
				res += m_pLen[i];
				if (res >= minLength)
				{
					res = 1;
					goto exit;
				}
			}

			res = 0;
			goto exit;
		}

		// Taking some partitions first to be not less than minLength
		for (l = 0, i = startIdx; i < m_cLen; ++i)
		{
			l += m_pLen[i];
			if (l >= minLength) break;
		}

		// If there are no more parts remaining, return 0
		if (i == m_cLen - 1)
		{
			res = 0;
			goto exit;
		}

		for (res = 0 /* i remains after previous loop */; i < m_cLen - 1; ++i)
		{
			res += countPartitions(i + 1, k - 1, minLength);
			res %= 1000000007;
		}
	
	exit:
		m_pRes[k * m_cLen + startIdx] = res;
		return res;
	}

public:
	Solution() { m_pLen = nullptr; m_pRes = nullptr; m_cLen = 0; }
	~Solution()	{ if (m_pLen) free(m_pLen); if (m_pRes) free(m_pRes); }

	int beautifulPartitions(string s, int k, int minLength)
	{
		int res, r, firstPartLen;

		preprocessString(s, minLength);
		// When no delimiters found at all or if possible partitions count less than 'k'
		if (m_cLen < k) return 0;
		// Check if there is impossible to partition more than in one way
		if (s.length() < k * minLength) return 1;
		// Simpliest way - just one partition (possible if str len no less than minLength)
		if (k == 1) return s.length() >= minLength ? 1 : 0;

		// Prepare intermediate result
		m_pRes = (int*)malloc(((size_t)k + 1) * m_cLen * sizeof(int));
		for (int i = 0; i < (k + 1) * m_cLen; ++i) m_pRes[i] = -1;

		// Let's start
		res = 0, firstPartLen = 0;

		for (int i = 0; i < m_cLen - 1; ++i)
		{
			firstPartLen += m_pLen[i];

			r = countPartitions(i + 1, k - 1, minLength);
			if (r == 0) break;
			res = (res + r) % 1000000007;
			//printf("%d: Result = %d\n", i, res);
		}

		return res;
	}
};

struct STestData
{
	string s;
	int k;
	int minLength;
	int res;
};

const vector<STestData> aTest = {
	{ "23542185131", 3, 2, 3 },
	{ "23542185131", 3, 3, 1 },
	{ "783938233588472343879134266968", 4, 6, 4 },
	{ "223648464314487128147519835837653132856158771373244725574964238668643532397448279818319174", 22, 3, 0 },
	{ "7753639519183359148598823162755335682921461647796985255166979917649578972791819356618496239"
	  "687361868933775339936875893219782348459522657159781118588765368954599285197845124455559747963186111993765269", 24, 2, 616385996 },
	{ "22", 1, 1, 0 }
};

int main()
{
	Solution *px;
	int i = 1, res;

	for (auto &test: aTest)
	{
		px = new Solution();
		res = px->beautifulPartitions(test.s, test.k, test.minLength);
		if (res != test.res)
		{
			printf("Test %d: ERROR: Result = %d, but expexted %d\n", i, res, test.res);
		}
		else printf("Test %d: OK!\n", i);

		delete px;
		i++;
	}

	//auto res = 
	//printf("\nRes:\n%d\n", res);

	return 0;
}
