// Solved:
// (E) Running Sum of 1d Array
// https://leetcode.com/problems/running-sum-of-1d-array/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize)
{
	int  i, sum;
	int* pOut;

	pOut = malloc(numsSize * sizeof(int));
	*returnSize = numsSize;
	
	for (i = sum = 0; i < numsSize; ++i)
	{
		sum += nums[i];
		pOut[i] = sum;
	}

	return pOut;
}
