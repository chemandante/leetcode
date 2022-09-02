// Solved:
// (E) Average of Levels in Binary Tree
// https://leetcode.com/problems/average-of-levels-in-binary-tree/
// Helper: Dynamic array

#include <stdlib.h>

typedef struct {
	int* aCnt;		// Count of elements (for average calculation)
	double* aSum;	// Sum of elements
	size_t used;
	size_t size;
} Array;

void initArray(Array* a, size_t initialSize) {
	a->aCnt = malloc(initialSize * sizeof(int));
	a->aSum = malloc(initialSize * sizeof(double));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(Array* a, int element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->aCnt = realloc(a->aCnt, a->size * sizeof(int));
		a->aSum = realloc(a->aSum, a->size * sizeof(double));
	}
	a->aCnt[a->used] = 1;
	a->aSum[a->used++] = element;
}

void freeArray(Array* a) {
	free(a->aCnt);
	free(a->aSum);
	a->aCnt = NULL; a->aSum = NULL;
	a->used = a->size = 0;
}

// Definition for a binary tree node.
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

void _countNode(Array* arr, struct TreeNode* node, int level)
{
	if (level == arr->used) {
		insertArray(arr, node->val);
	}
	else {
		arr->aCnt[level]++;
		arr->aSum[level] += node->val;
	}

	if (node->left) _countNode(arr, node->left, level + 1);
	if (node->right) _countNode(arr, node->right, level + 1);
}

 /**
  * Note: The returned array must be malloced, assume caller calls free().
  */
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
	Array	arr;
	size_t  i;

	initArray(&arr, 20);

	_countNode(&arr, root, 0);

	for (i = 0; i < arr.used; ++i) arr.aSum[i] /= arr.aCnt[i];

	free(arr.aCnt);

	*returnSize = arr.used;
	return arr.aSum;
}


int main()
{
	double* res;
	int		size;
	struct TreeNode t[5];

	t[0].val = 3;	t[0].left = &t[1];	t[0].right = &t[2];
	t[1].val = 9;	t[1].left = NULL;	t[1].right = NULL;
	t[2].val = 20;	t[2].left = &t[3];	t[2].right = &t[4];
	t[3].val = 15;	t[3].left = NULL;	t[3].right = NULL;
	t[4].val = 7;	t[4].left = NULL;	t[4].right = NULL;

	res = averageOfLevels(t, &size);

	return 0;
}
