#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	int minDeletions(string s)
	{
		vector<int> v(26, 0);
		int d, i, n;

		for (i = 0; i < s.size(); ++i) v[s[i] - 'a']++;

		sort(v.begin(), v.end(), greater<int>());

		for (i = 1, n = 0; i < v.size() && v[i]; ++i)
		{
			if (v[i] >= v[i - 1])
			{
				d = v[i] - v[i - 1] + 1;
				if (d > v[i]) d = v[i];
				n += d;
				v[i] = v[i - 1] - 1;
			}
		}

		return n;
	}
};


int main()
{
	Solution x;
	string s = "bbcebab";

	printf("%d\n", x.minDeletions(s));
}
