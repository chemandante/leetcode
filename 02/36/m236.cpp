#include <stack>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//struct StackElem
//{
//	TreeNode* node;
//	int		  idx;
//};
//
//class Solution
//{
//public:
//	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
//	{
//		queue<StackElem> que;
//		StackElem		 node;
//		int idxP, idxQ;
//
//		que.push({ root, 0 });
//
//		while (!que.empty())
//		{
//			node = que.front();	que.pop();
//
//			if (node.node == p) idxP = node.idx;
//			else if (node.node == q) idxQ = node.idx;
//
//			if (node.node->left) que.push({ node.node->left, 2 * node.idx + 1 });
//			if (node.node->right) que.push({ node.node->right, 2 * node.idx + 2 });
//		}
//
//		while (idxP != idxQ)
//		{
//			if (idxP > idxQ) idxP = (idxP - 1) >> 1;
//			else			 idxQ = (idxQ - 1) >> 1;
//		}
//
//		return aNodes[idxP];
//	}
//};
class Solution
{
private:
	stack<TreeNode*>	m_stack, m_stackP, m_stackQ;

	bool preOrderTraverse(TreeNode* node, TreeNode* p, TreeNode* q)
	{
		m_stack.push(node);

		if (node == p) m_stackP = m_stack;
		if (node == q) m_stackQ = m_stack;

		if (!m_stackP.empty() && !m_stackQ.empty()) return true;

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
		preOrderTraverse(root, p, q);

		int n = m_stackP.size() - m_stackQ.size();
		if (n > 0) for (int i = 0; i < n; ++i) m_stackP.pop();
		else	   for (int i = 0; i < -n; ++i) m_stackQ.pop();

		while (m_stackP.top() != m_stackQ.top())
		{
			m_stackP.pop();	m_stackQ.pop();
		}

		return m_stackP.top();
	}
};


int main()
{
	Solution x;

	//res = x.singleNumber(a);
	//printf("%d, %d\n", res[0], res[1]);
}
