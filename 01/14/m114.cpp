// Solved:
// (M) Flatten Binary Tree to Linked List
// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
	TreeNode* preOrderTraverse(TreeNode* node)
	{
		TreeNode* pLeft = nullptr, * pRight = nullptr;

		if (node->left)
			pLeft = preOrderTraverse(node->left);
		if (node->right)
			pRight = preOrderTraverse(node->right);

		if (node->left)
		{
			if (node->right) // If there are both branches
			{
				pLeft->right = node->right; // Couple right branch to last leaf in left branch
				node->right = node->left;
				node->left = nullptr;
				return pRight;
			}
			else // If there is only left branch
			{
				node->right = node->left;
				node->left = nullptr;
				return pLeft;
			}
		}
		else
		{
			// If there is only right branch
			if (node->right) return pRight;
			else return node; // If this node is the leaf
		}
	}

public:
	void flatten(TreeNode* root)
	{
		if (root) preOrderTraverse(root);
	}
};


int main()
{
	//Solution x;

	//res = x.singleNumber(a);
	//printf("%d, %d\n", res[0], res[1]);
}
