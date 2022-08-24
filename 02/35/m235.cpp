// Solved:
// (E) Lowest Common Ancestor of a Binary Search Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 

class Solution
{
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		TreeNode* pCurr = root;
		int nPVal, nQVal, nCVal;
		
		if (p->val < q->val) nPVal = p->val, nQVal = q->val;
		else nPVal = q->val, nQVal = p->val;
		bool bLeft;

		while (pCurr)
		{
			nCVal = pCurr->val;

			if (nCVal == nPVal || nCVal == nQVal) return pCurr;

			bLeft = nPVal < nCVal;

			if (bLeft && (nQVal > nCVal)) return pCurr;
			else pCurr = bLeft ? pCurr->left : pCurr->right;
		}

		return root;
	}
};
