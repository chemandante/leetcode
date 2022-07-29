from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next_node=None):
        self.val = val
        self.next = next_node

    def __repr__(self):
        if self.next:
            return f"{self.val} -> {self.next.val}"
        else:
            return f"{self.val}."


class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head:
            return None

        pPrev = head
        pCurr = head.next

        while pCurr:
            pNext = pCurr.next
            pCurr.next = pPrev
            pPrev = pCurr
            pCurr = pNext

        head.next = None
        return pPrev


x = Solution()

l5 = ListNode(5)
l4 = ListNode(4, l5)
l3 = ListNode(3, l4)
l2 = ListNode(2, l3)
l1 = ListNode(1, l2)

lr = x.reverseList(l1)

print(1)
