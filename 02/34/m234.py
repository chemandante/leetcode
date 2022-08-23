from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

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
        :return: tuple: (new head, remaining list)
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
        return pPrev, pCurr

    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        # At first, we should count elements in list
        cnt, p = 0, head
        while p:
            cnt += 1
            p = p.next
        # Obvious case
        if cnt == 1:
            return True
        # Now reverse first floor(cnt / 2) elements
        p1, p2 = self.reverseList(head, cnt // 2)
        # If cnt is odd, there is one middle element in list, skip it
        if cnt & 1:
            p2 = p2.next
        # Comparing lists
        while p2:
            if p1.val != p2.val:
                return False
            p1 = p1.next
            p2 = p2.next
        return True


x = Solution()
l5 = ListNode(5)
l4 = ListNode(4, l5)
l3 = ListNode(6, l4)
l2 = ListNode(5)
l1 = ListNode(5, l2)

print(x.isPalindrome(l1))
