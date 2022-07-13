#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution
{
public:
	void traverseNode(TreeNode* node, int level, vector<vector<int>>& result)
	{
		if (level >= result.size()) result.push_back({});
		result[level].push_back(node->val);
		if (node->left) traverseNode(node->left, level + 1, result);
		if (node->right) traverseNode(node->right, level + 1, result);
	}

	vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> res;

		if (root) traverseNode(root, 0, res);

		return res;
	}
};


int main()
{
	Solution x;
	TreeNode n15(15);
	TreeNode n7(7);
	TreeNode n9(9);
	TreeNode n20(20, &n15, &n7);
	TreeNode root(3, &n9, &n20);

	vector<vector<int>> res = x.levelOrder(&root);

	return 0;
}
