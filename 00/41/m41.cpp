#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
	int firstMissingPositive(vector<int>& nums)
	{
		vector<int>::iterator it = nums.begin();
		unordered_set<int> s;
		unordered_set<int>::iterator si;
		int m, n = 1;

		while (it != nums.end())
		{
			m = *it++;
			if (m == n)
			{
				while ((si = s.find(++n)) != s.end()) s.erase(si);
			}
			else if (m > n) s.insert(m);
		}

		return n;
	}
};


int main()
{
	Solution x;
	vector<int> data;
	
	srand(445);
	for (int i = 0; i < 5000000; ++i) data.push_back((rand() << 7) ^ rand());

	printf("%d\n", x.firstMissingPositive(data));
}
