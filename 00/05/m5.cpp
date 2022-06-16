#include <string>

using namespace std;

class Solution
{
public:
	string longestPalindrome(string s)
	{
		string::iterator itb = s.begin(), ite = s.end();
		int nLen = s.length(), idxe = 1, ib, ie, nPLen, nPLenMax = 1, ibMax = 0;
		bool bOdd = false;

		// No need to continue search if we already find a bigger palindrome then we could find later
		while (nLen - idxe > (nPLenMax - 1) >> 1)
		{
			ie = idxe;
			ib = ie - (bOdd ? 2 : 1);

			nPLen = 0;

			while (s[ib] == s[ie])
			{
				nPLen = ie - ib + 1;

				if (--ib < 0 || ++ie >= nLen) break;
			}

			if (nPLen > nPLenMax)
			{
				nPLenMax = nPLen; ibMax = ib + 1;
			}

			if (!bOdd) idxe++;
			bOdd = !bOdd;
		}

		return s.substr(ibMax, nPLenMax);
	}
};

int main()
{
	Solution x;

	string aStr[] = { "a", "aa", "ab", "aaa", "aca", "aac", "acca", "acda", "babacabab" };

	for (int i = 0; i < sizeof(aStr) / sizeof(aStr[0]); ++i)
	{
		printf("%s - %s\n", aStr[i].c_str(), x.longestPalindrome(aStr[i]).c_str());
	}
}
