// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution
{
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode *p1 = l1, *p2 = l2, *pRes, *p, *pp = nullptr;
		int n;

		p = pRes = new ListNode();
		n = 0;

		while (p1 || p2)
		{
			if (p1) n += p1->val;
			if (p2) n += p2->val;

			p->val = (n > 9) ? (n - 10) : n;
			p->next = new ListNode();
			pp = p;
			p = p->next;
			n = (n > 9) ? 1 : 0;	// n contains carry
			if (p1) p1 = p1->next;
			if (p2) p2 = p2->next;
		}

		if (n > 0)
		{
			p->val = n;
		}
		else
		{
			p = pp;
			delete p->next;
			p->next = nullptr;
		}

		return pRes;
	}
};
