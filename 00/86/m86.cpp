// Solved:
// (M) Partition List
// https://leetcode.com/problems/partition-list/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode* partition(ListNode* head, int x)
	{
		ListNode *pLesser = nullptr, *pOthers = nullptr;
		ListNode *pLesserCurr, *pOthersCurr;

		while (head)
		{
			if (head->val < x)
			{
				if (pLesser)
				{
					pLesserCurr->next = head;
					pLesserCurr = head;
				}
				else pLesserCurr = pLesser = head;
			}
			else
			{
				if (pOthers)
				{
					pOthersCurr->next = head;
					pOthersCurr = head;
				}
				else pOthersCurr = pOthers = head;
			}

			head = head->next;
		}

		if (pLesser)
		{
			pLesserCurr->next = pOthers;
			if (pOthers) pOthersCurr->next = nullptr;
			return pLesser;
		}
		else return pOthers;
	}
};


int main()
{
	Solution x;
	int a[] = { 1, 1 };
	ListNode* pCurr, *pPrev = nullptr;
	
	for (int i = sizeof(a) / sizeof(a[0]) - 1; i >= 0; --i)
	{
		pCurr = new ListNode(a[i], pPrev);
		pPrev = pCurr;
	}

	pPrev = x.partition(pCurr, 3);

	return 0;
}
