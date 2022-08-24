// Solved:
// (E) Maximum Units on a Truck
// https://leetcode.com/problems/maximum-units-on-a-truck/

#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
	int maximumUnits(vector<vector<int>>& boxTypes, int truckSize)
	{
		// Support array containing count of boxes for each box type (distinct units per box)
		// <index> = 1000 - <units_per_box>, in opposite: <units_per_box> = 1000 - <index>
		uint16_t aBoxes[1000] = {};
		vector<vector<int>>::iterator it;
		int i, n, nUnits, upb, nMaxBoxType = INT_MIN, nMinBoxType = INT_MAX;

		for (auto& box : boxTypes)
		{
			n = 1000 - box[1];
			if (n < nMinBoxType) nMinBoxType = n;
			if (n > nMaxBoxType) nMaxBoxType = n;
			aBoxes[n] += box[0];
		}

		for (nUnits = 0, i = nMinBoxType, upb = 1000 - i; i <= nMaxBoxType && truckSize > 0; ++i, --upb)
		{
			if (truckSize > aBoxes[i]) n = aBoxes[i];
			else n = truckSize;

			nUnits += n * upb;
			truckSize -= n;
		}

		return nUnits;
	}
};

class Solution_nonOpt
{
public:
	int maximumUnits(vector<vector<int>>& boxTypes, int truckSize)
	{
		vector<vector<int>>::iterator it;
		int n, nUnits, b1, b2;

		sort(boxTypes.begin(), boxTypes.end(),
			[](auto& a, auto& b) { return a[1] > b[1]; });

		nUnits = 0;
		it = boxTypes.begin();

		while (it != boxTypes.end() && truckSize > 0)
		{
			b1 = (*it)[0], b2 = (*it)[1];
			if (truckSize > b1) n = b1;
			else n = truckSize;

			nUnits += n * b2;
			truckSize -= n;
			++it;
		}

		return nUnits;
	}
};

int main()
{
	Solution x;
	vector<vector<int>> boxes = { {1, 3},{3, 1},{2, 2} };

	printf("%d\n", x.maximumUnits(boxes, 4));
}
