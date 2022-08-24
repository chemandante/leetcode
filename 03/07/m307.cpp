// Solved:
// (M) Range Sum Query - Mutable
// https://leetcode.com/problems/range-sum-query-mutable/

#include <vector>

using namespace std;

class NumArray
{
private:
	int m_nLevelCount;
	vector<uint16_t> m_aCount;
	vector<int*> m_aPtr;
	int* m_pData;

	/**
	 * Calculate ceil(log2(u)).
	 * 
	 * \param u - number
	 * \return ceil(log2(u))
	 */
	uint8_t calcCeilLog2(uint16_t u)
	{
		int i, n;
		uint16_t bit;

		if (!u) return 0;

		for (i = 8, n = 0; i; i >>= 1)
		{
			bit = 1 << (n + i);
			if (u > bit) n += i;
		}

		return n + 1;
	}

	int sum(int nLevel, int left, int right)
	{
		int s = 0;

		if (left > right) return 0;
		else if (left == right) return m_aPtr[nLevel][left];

		// If left index is odd, we should put this particular element in sum
		if (left & 1) s += m_aPtr[nLevel][left];
		left = (left + 1) >> 1;
		// If left index is odd, we should put this particular element in sum
		if (!(right & 1)) s += m_aPtr[nLevel][right];
		right = (right - 1) >> 1;

		return s + sum(nLevel + 1, left, right);
	}

public:
	NumArray(vector<int>& nums)
	{
		int nNums = nums.size(), i, j, k, nTotal;
		int* pData, *pDataPrev;
		
		m_nLevelCount = calcCeilLog2(nNums) + 1;
		m_aCount.resize(m_nLevelCount);
		m_aPtr.resize(m_nLevelCount);
		// Calculating count at each tree level
		for (i = nTotal = 0; i < m_nLevelCount; ++i)
		{
			m_aCount[i] = nNums;	nTotal += nNums;
			nNums = (nNums + 1) >> 1;
		}
		// Allocating memory for all levels
		m_pData = (int*)malloc(nTotal * sizeof(int));
		// Filling 0-th level, numbers itself
		m_aPtr[0] = pData = m_pData;
		for (j = 0; j < m_aCount[0]; ++j) pData[j] = nums[j];
		// Filling other levels with partial sums
		for (i = 1, nTotal = m_aCount[0]; i < m_nLevelCount; ++i)
		{
			pDataPrev = pData;
			pData += m_aCount[i - 1];
			m_aPtr[i] = pData;
			// Filling sums of two elements
			for (j = k = 0; j < m_aCount[i - 1] >> 1; ++j, k += 2)
			{
				pData[j] = pDataPrev[k] + pDataPrev[k + 1];
			}
			// Filling last element is is if there was odd numbers in previous level
			if (m_aCount[i - 1] & 1) pData[j] = pDataPrev[k];
		}
	}

	~NumArray()
	{
		free(m_pData);
	}

	void update(int index, int val)
	{
		int delta = val - m_aPtr[0][index];
		
		for (int i = 0; i < m_nLevelCount; ++i)
		{
			m_aPtr[i][index] += delta;
			index >>= 1;
		}
	}

	int sumRange(int left, int right)
	{
		return sum(0, left, right);
	}
};


int main()
{
	vector<int> nums = { 1, 2, 3, 4, 5,6 ,7 ,8 ,9 };
	NumArray x(nums);

	x.update(2, 8);
	printf("%d\n", x.sumRange(1, 5));
	//for (int i = 0; i < 14; i += 1)
	//{
	//	//printf("%d = %d\n", i, x.calcCeilLog2(i));
	//}

	return 0;
}
