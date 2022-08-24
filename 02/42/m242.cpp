// Solved:
// (E) Valid Anagram
// https://leetcode.com/problems/valid-anagram/

#include <string>

using namespace std;

class Solution
{
public:
	bool isAnagram(string s, string t)
	{
		uint16_t cChar[26];

		memset(cChar, 0, sizeof(cChar));

		for (char ch : s) cChar[ch - 'a']++;
		for (char ch : t) cChar[ch - 'a']--;

		for (int i = 0; i < 26; ++i) if (cChar[i]) return false;

		return true;
	}
};


int main()
{
	//Solution x;

	//res = x.singleNumber(a);
	//printf("%d, %d\n", res[0], res[1]);
}
