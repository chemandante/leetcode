# Solved:
# (H) Vertical Order Traversal of a Binary Tree
# https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
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
        node_idx += 1
        if node_idx < len(array) and array[node_idx]:
            self.right = TreeNode(array[node_idx])
            self.right._addNode(array, node_idx)


class Solution:
    def __init__(self):
        self.lst = None

    def _traverseNode(self, node: TreeNode, row: int, col: int):
        self.lst.append((col, row, node.val))
        if node.left:
            self._traverseNode(node.left, row + 1, col - 1)
        if node.right:
            self._traverseNode(node.right, row + 1, col + 1)

    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        res = []
        self.lst = []
        self._traverseNode(root, 0, 0)
        self.lst.sort()

        colPrev = self.lst[0][0]
        li = []
        for d in self.lst:
            if d[0] == colPrev:
                li.append(d[2])
            else:
                res.append(li)
                li = [d[2]]
                colPrev = d[0]

        res.append(li)
        return res


x = Solution()

root = TreeNode(array=[3, 9, 20, None, None, 15, 7])
print(x.verticalTraversal(root))

root = TreeNode(array=[1, 2, 3, 4, 5, 6, 7])
print(x.verticalTraversal(root))
