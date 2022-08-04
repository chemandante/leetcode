
int calcGCD(int a, int b)
{
	int n;
	while (b)
	{
		n = a % b;  a = b;  b = n;
	}
	return a;
}

class Solution
{
public:
	int mirrorReflection(int p, int q)
	{
		int gcd = calcGCD(p, q);
		int m = p / gcd;
		int n = q / gcd;
		
		if (m & 1) return (n & 1) ? 1 : 0;
		else return (n & 1) ? 2 : -1;
	}
};


