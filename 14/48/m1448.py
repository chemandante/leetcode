# Solved:
# (M) Count Good Nodes in Binary Tree
# https://leetcode.com/problems/count-good-nodes-in-binary-tree/

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def _checkNode(self, node: TreeNode, nMax: int) -> int:
        n = 1 if node.val >= nMax else 0
        nMax = max(node.val, nMax)

        if node.left:
            n += self._checkNode(node.left, nMax)
        if node.right:
            n += self._checkNode(node.right, nMax)
        return n

    def goodNodes(self, root: TreeNode) -> int:
        return self._checkNode(root, -10000)
