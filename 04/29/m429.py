# Solved:
# (M) N-ary Tree Level Order Traversal
# https://leetcode.com/problems/n-ary-tree-level-order-traversal/

from typing import List


# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children


class Solution:
    def __init__(self):
        self.res = None

    def _processNode(self, node: 'Node', level: int):
        if level < len(self.res):
            self.res[level].append(node.val)
        else:
            self.res.append([node.val])

        for child in node.children:
            self._processNode(child, level + 1)

    def levelOrder(self, root: 'Node') -> List[List[int]]:
        self.res = []
        self._processNode(root, 0)

        return self.res



