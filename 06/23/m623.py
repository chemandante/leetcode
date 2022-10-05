# Solved:
# (M) Add One Row to Tree
# https://leetcode.com/problems/add-one-row-to-tree/
# Helper: Building TreeNode's tree from array

from typing import List, Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None, array=None):
        if array:
            self.val = array[0]
            self._addNode(array, 0)
        else:
            self.val = val
            self.left = left
            self.right = right

    def _addNode(self, array: List[int], node_idx: int):
        node_idx = 2 * node_idx + 1
        if node_idx < len(array) and array[node_idx]:
            self.left = TreeNode(array[node_idx])
            self.left._addNode(array, node_idx)
        else:
            self.left = None
        node_idx += 1
        if node_idx < len(array) and array[node_idx]:
            self.right = TreeNode(array[node_idx])
            self.right._addNode(array, node_idx)
        else:
            self.right = None


class Solution:
    def _processNode(self, node: TreeNode, val: int, depth: int, currDepth: int):
        if depth == currDepth:
            Lnode = TreeNode(val, left=node.left)
            Rnode = TreeNode(val, right=node.right)
            node.left = Lnode
            node.right = Rnode
        else:
            if node.left:
                self._processNode(node.left, val, depth, currDepth + 1)
            if node.right:
                self._processNode(node.right, val, depth, currDepth + 1)

    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        if root:
            if depth > 1:
                self._processNode(root, val, depth - 1, 1)
                return root
            else:
                node = TreeNode(val, left=root)
                return node

        return None


x = Solution()
tr = TreeNode(array=[4, 2, None, 3, 1])
xx = x.addOneRow(tr, 1, 3)
print(x)
