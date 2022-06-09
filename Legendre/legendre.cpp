#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> genLegendreSequence(int p)
	{
		vector<int> res(p);
		vector<int>::iterator it = res.begin();
		// Initializing all elements with -1
		while (it != res.end()) *it++ = -1;
		// Itarating through all numbers from 0 to (p - 1) / 2 inclusive and set elements
		// with index (i*i mod p) to 1
		for (int i = 0; i <= p >> 1; ++i) res[i * i % p] = 1;

		return res;
	}
};


int main()
{
	Solution x;
	vector<int> res;
	
	res = x.genLegendreSequence(41);
	for (int i = 0; i < res.size(); ++i) printf("%d, ", res[i]);
}
