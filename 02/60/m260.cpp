// Solved:
// (M) Single Number III
// https://leetcode.com/problems/single-number-iii/

#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> singleNumber(vector<int>& nums)
	{
		int r = 0, r2 = 0, mask;

		// Let R1 and R2 are answer. After XOR'ing  all nums we get R = R1 ^ R2
		for (auto x : nums) r ^= x;
		// Now 'r' contains R1 ^ R2; r != 0 because R1 != R2
		// Lets find any '1' bit in binary representation of 'r' and XOR all nums
		// that hhave this bit set. Only R1 OR R2 will contain that bit set, only
		// R1 or R2 will be XOR'ed in second pass.
		if (r == INT32_MIN) mask = r;
		else mask = (r & (r - 1)) ^ r; // Now 'mask' contains less significant '1' bit
		// Second pass (XOR only nums that contains masked bit)
		for (auto x : nums) if (x & mask) r2 ^= x;
		// Now 'r2' contains R1 or R2 part of answer, so (r ^ r2) will contain other part
		return { r ^ r2, r2 };
	}
};


int main()
{
	Solution x;
	vector<int> a = { -30000, -29000, 28001, -30000, -3290, -29000 };
	vector<int> res;

	res = x.singleNumber(a);
	printf("%d, %d\n", res[0], res[1]);
}
