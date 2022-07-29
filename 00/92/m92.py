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

    def __str__(self):
        s = f"{self.val}"
        p = self.next
        i = 1
        while p and i < 10:
            s += f" -> {p.val}"
            p = p.next
            i += 1
        if i == 10:
            s += " -> ..."
        else:
            s += "."
        return s


class Solution:
    def reverseList(self, head: Optional[ListNode], count: int) -> Optional[ListNode]:
        if not head:
            return None

        pPrev = head
        pCurr = head.next
        idx = 1

        while pCurr and idx != count:
            pNext = pCurr.next
            pCurr.next = pPrev
            pPrev = pCurr
            pCurr = pNext
            idx += 1

        head.next = pCurr
        return pPrev

    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        p = head
        pp = None
        i = 1
        while i < left:
            pp = p
            p = p.next
            i += 1
        res = self.reverseList(p, right - left + 1)
        if pp:
            pp.next = res
            return head

        return res


x = Solution()

l5 = ListNode(5)
l4 = ListNode(4, l5)
l3 = ListNode(3, l4)
l2 = ListNode(2, l3)
l1 = ListNode(1, l2)

lr = x.reverseBetween(l1, 3, 5)

print(lr)
