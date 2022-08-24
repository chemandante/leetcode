// Solved:
// (M) Find and Replace Pattern
// https://leetcode.com/problems/find-and-replace-pattern/

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	vector<string> findAndReplacePattern(vector<string>& words, string pattern)
	{
		vector<string> res;
		int  nPatternSize = pattern.size(), idxP, idxW;
		char aSubstP[26], aSubstW[26]; // Forward and reverse bijection table
		char chP, chW;
		bool bAdd;

		// For every word
		for (auto& word : words)
		{
			// Zeroing substitute tables
			memset(aSubstP, 0, sizeof(aSubstP));
			memset(aSubstW, 0, sizeof(aSubstW));
			bAdd = true;

			// For every character in word
			for (int i = 0; i < nPatternSize; ++i)
			{
				chP = pattern[i],	idxP = chP - 'a';
				chW = word[i],		idxW = chW - 'a';

				// Check (and fill if needed) forward bijection table
				if (aSubstP[idxP])
				{
					if (aSubstP[idxP] != chW) bAdd = false;
				}
				else aSubstP[idxP] = chW;

				// Check (and fill if needed) reverse bijection table
				if (aSubstW[idxW])
				{
					if (aSubstW[idxW] != chP) bAdd = false;
				}
				else aSubstW[idxW] = chP;
			}
			// Add word to result only if there were no errors durin bijection check
			if (bAdd) res.push_back(word);
		}

		return res;
	}
};

