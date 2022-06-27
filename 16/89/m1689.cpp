#include <string>

using namespace std;

class Solution
{
public:
	int minPartitions(string n)
	{
		char chMax;
		const char * psz = n.c_str();
		int  i, nSize = n.size();

		for (i = 0, chMax = '0'; i < nSize; ++i) if (psz[i] > chMax) chMax = psz[i];

		return chMax - '0';
	}
};
