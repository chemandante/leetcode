#include <string>

using namespace std;

class Solution
{
public:
	string addBinary(string a, string b)
	{
		int idxa = a.size(), idxb = b.size(), d = 0;
		string s;
		
		// While next char are not 
		while (idxa || idxb)
		{
			if (idxa) d += a[--idxa] - '0';
			if (idxb) d += b[--idxb] - '0';
			s.push_back((d & 1) + '0');
			d >>= 1;
		}

		reverse(s.begin(), s.end());
		return s;
	}
};

int main()
{
	Solution x;

	printf("%s\n", x.addBinary("1011", "11").c_str());
}
