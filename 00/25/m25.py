# Solved:
# (H) Reverse Nodes in k-Group
# https://leetcode.com/problems/reverse-nodes-in-k-group/

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
        """
        Reverses first 'count' number of elements in the single-linked list
        Ex., Reverse first 4 elements of the list 1->2->3->4->5 returns 4->3->2->1->5
        :param head: points to head of single-linked list
        :param count: number of elements to reverse
        :return: new head
        """
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

    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        # Quite obvious case
        if k == 1:
            return head

        p = head
        cnt = k
        res = head
        grp_head = head  # Saving head of the group
        grp_tail = None  # We don't new the tail of the group yet
        while p or cnt == 0:
            # Lets reverse group
            if cnt == 0:
                pp = self.reverseList(grp_head, k)
                if res == head:  # Save new (reversed) head of the group only once a result
                    res = pp
                if grp_tail:  # Linking tail of previous group to new reversed group head
                    grp_tail.next = pp
                grp_tail = grp_head  # Tail of new group will be the head of previous
                grp_head = p
                cnt = k  # Resetting the counter

            cnt -= 1
            if p:
                p = p.next
        return res


x = Solution()

# l5 = ListNode(5)
l4 = ListNode(4)
l3 = ListNode(3, l4)
l2 = ListNode(2, l3)
l1 = ListNode(1, l2)

lr = x.reverseKGroup(l1, 2)

print(lr)
