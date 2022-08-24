// Solved:
// (M) Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <string>

using namespace std;

class Solution
{
public:
	int lengthOfLongestSubstring(string s)
	{
		string::iterator it = s.begin(), its = it;
		char ach[128], ch;
		int  res = 0, n = 0;

		memset(ach, 0, sizeof(ach));

		while (it != s.end())
		{
			ch = *it;
			// If char is in array, break the sequence
			if (ach[ch])
			{
				// Store max(n)
				if (n > res) res = n;
				// Clear array (only those chars used in sequence)
				while (its != it) ach[*its++] = 0;
				// Return back to char same as 'ch'
				while (*(--it) != ch);
				// Start new sequence
				its = it + 1;
				n = 0;
			}
			else
			{
				ach[ch] = 1;
				n++;
			}

			it++;
		}

		if (n > res) res = n;

		return res;
	}
};


int main()
{
	Solution x;
	string s = "dvdf";

	printf("%d\n", x.lengthOfLongestSubstring(s));
}
