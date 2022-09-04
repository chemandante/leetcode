// Solved:
// (H) Count of Smaller Numbers After Self
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// BIT: Tree for counting numbers less than X

#include <stdio.h>
#include <stdlib.h>

#define MIN_VALUE	-10000
#define MAX_VALUE	10000
#define VALUE_RANGE (MAX_VALUE - MIN_VALUE + 1)

void _countItem(int* tree, int item) {
	item++;
	while (item && item < VALUE_RANGE + 1) {
		tree[item]++;
		item += item & (-item);
	}
}

int _getSum(int* tree, int item) {
	int res = 0;
	while (item) {
		res += tree[item];
		item -= item & (-item);
	}
	return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize) {
	int* res, * tree;
	int i, n;
	
	res = (int*)malloc(numsSize * sizeof(int));
	tree = (int*)calloc(VALUE_RANGE + 1, sizeof(int)); // For -10^4 <= num <= 10^4 plus dumb cell for index 0
	
	// Iterating through array backwards
	for (i = numsSize - 1; i >= 0; --i)	{
		n = nums[i] - MIN_VALUE; // From range to 0-based index
		res[i] = _getSum(tree, n);
		_countItem(tree, n);
	}
	
	*returnSize = numsSize;
	free(tree);
	return res;
}


int main(int argc, const char * argv[]) {
	int nums[] = {5, 2, 6, 1};
	int ret;
	
	countSmaller(nums, 4, &ret);
	
	return 0;
}
