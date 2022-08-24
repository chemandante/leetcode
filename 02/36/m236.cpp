// Solved:
// (M) Lowest Common Ancestor of a Binary Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

#include <stack>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
private:
	stack<TreeNode*>	m_stack, m_stackSaved;
	bool		m_bFound;

	bool preOrderTraverse(TreeNode* node, TreeNode* p, TreeNode* q)
	{
		m_stack.push(node);

		if (node == p || node == q)
		{
			// If one node was found already (P or Q)
			if (m_bFound) return true;
			m_stackSaved = m_stack, m_bFound = true;
		}

		if (node->left)
			if (preOrderTraverse(node->left, p, q)) return true;
		if (node->right)
			if (preOrderTraverse(node->right, p, q)) return true;

		m_stack.pop();

		return false;
	}

public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		m_bFound = false;

		preOrderTraverse(root, p, q);

		int n = m_stack.size() - m_stackSaved.size();
		if (n > 0) for (int i = 0; i < n; ++i) m_stack.pop();
		else	   for (int i = 0; i < -n; ++i) m_stackSaved.pop();

		while (m_stack.top() != m_stackSaved.top())
		{
			m_stack.pop();	m_stackSaved.pop();
		}

		return m_stack.top();
	}
};


int main()
{
	Solution x;

	//res = x.singleNumber(a);
	//printf("%d, %d\n", res[0], res[1]);
}
