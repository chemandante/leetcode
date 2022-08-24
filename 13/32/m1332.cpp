// Solved:
// (E) Remove Palindromic Subsequences
// https://leetcode.com/problems/remove-palindromic-subsequences/

#include <string>

using namespace std;

class Solution
{
public:
	int removePalindromeSub(string s)
	{
		char *p1, *p2;

		p1 = (char*)s.c_str();
		p2 = p1 + s.size() - 1;

		// All we need to do - check if the string is a palindrome itself, then return 1
		// If trere is not - return 2, because all 'a's and all 'b's are palindromes
		while (p2 - p1 > 1)
		{
			if (*p1 != *p2) return 2;
			p1++, p2--;
		}

		return 1;

	}
};


int main()
{
	Solution x;
	string s;// "baababbabbabaabab";

	s = "ababa";
	printf("%s - %d\n", s.c_str(), x.removePalindromeSub(s));
	s = "abb";
	printf("%s - %d\n", s.c_str(), x.removePalindromeSub(s));
	s = "baabb";
	printf("%s - %d\n", s.c_str(), x.removePalindromeSub(s));
}
