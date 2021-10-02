#define _CRT_SECURE_NO_WARNINGS 1

//����

#include<iostream>
using namespace std;
#include<list>
#include<unordered_set>
//2. �������


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
//
//// ��һ�� 
//class Solution {
//public:
//	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//		ListNode* head = nullptr, * cur = nullptr;
//		int add = 0;
//		while (l1 && l2) {
//			int sum = l1->val + l2->val + add;
//			if (!head) {
//				head = cur = new ListNode(sum % 10);
//			} else {
//				cur->next = new ListNode(sum % 10);
//				cur = cur->next;
//			}
//			add = sum / 10;
//			l1 = l1->next;
//			l2 = l2->next;
//
//		}
//		ListNode* tmp = l1 ? l1 : l2;
//		while (tmp) {
//			int sum = add + tmp->val;
//			cur->next = new ListNode(sum % 10);
//			add = sum / 10;
//			cur = cur->next;
//			tmp = tmp->next;
//		}
//		if (add) {
//			cur->next = new ListNode(add);
//		}
//		return head;
//	}
//};
//
////����������
//class Solution {
//public:
//	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//		ListNode* head = nullptr, * tail = nullptr;
//		int carry = 0;
//		while (l1 || l2) {
//			int n1 = l1 ? l1->val : 0;
//			int n2 = l2 ? l2->val : 0;
//			int sum = n1 + n2 + carry;
//			if (!head) {
//				head = tail = new ListNode(sum % 10);
//			} else {
//				tail->next = new ListNode(sum % 10);
//				tail = tail->next;
//			}
//			carry = sum / 10;
//			if (l1) {
//				l1 = l1->next;
//			}
//			if (l2) {
//				l2 = l2->next;
//			}
//		}
//		if (carry > 0) {
//			tail->next = new ListNode(carry);
//		}
//		return head;
//	}
//};
//


//142. �������� II


//��һ����ָ��һ������������ָ��һ�������������л�������ָ������ָ������������ָ���߹��ĳ�������ָ���������
//��ʱ����ָ���ͷ��ʼһ����һ������ָ��Ҳһ����һ��������ָ������ʱ��Ϊ�������
class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		if (!head) {
			return nullptr;
		}
		ListNode* res, * fast, * slow;
		res = fast = slow = head;

		do {
			if (fast->next)
				fast = fast->next->next;
			else
				return nullptr;
			slow = slow->next;
		} while (fast && slow != fast);

		if (!fast) {
			return nullptr;
		}

		while (res != slow) {
			res = res->next;
			slow = slow->next;
		}

		return res;

	}
};

//����: struct ListNode* slow, * fast;
class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		struct ListNode* slow, * fast;
		slow = fast = head;
		while (fast && fast->next)
		{

			slow = slow->next;
			fast = fast->next->next;

			if (fast == slow)
				break;
		}

		if (fast == NULL || fast->next == NULL)
			return NULL;

		struct ListNode* meet = fast;
		while (head != meet)
		{
			head = head->next;
			meet = meet->next;
		}
		return meet;
	}
};

//��������ϣ��
//���Ǳ��������е�ÿ���ڵ㣬��������¼������һ�������˴�ǰ�������Ľڵ㣬�Ϳ����ж������д��ڻ���������ϣ����Ժܷ����ʵ�֡�

class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		unordered_set<ListNode*> visited;
		while (head != nullptr) {
			if (visited.count(head)) {
				return head;
			}
			visited.insert(head);
			head = head->next;
		}
		return nullptr;
	}
};


//160. �ཻ����


//��һ����ϣ����
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		unordered_set<ListNode*> visited;
		while (headA) {
			visited.insert(headA);
			headA = headA->next;
		}
		while (headB) {
			if (visited.count(headB)) {
				return headB;
			}
			headB = headB->next;
		}
		return nullptr;

	}
};

//������������������ڵ����Ĳ�ֵ
//�˷���˵������ʱ��ռ������ڷ�һ
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		int numA = 0, numB = 0;
		ListNode* ahead = headA, * bhead = headB;
		while (headA)
		{
			numA++;
			headA = headA->next;
		}
		while (headB) {
			numB++;
			headB = headB->next;
		}
		headA = ahead, headB = bhead;
		if (numA > numB) {
			int n = numA - numB;
			while (n--) {
				headA = headA->next;
			}
		} else {
			int n = numB - numA;
			while (n--) {
				headB = headB->next;
			}
		}

		while (headA && headB) {
			if (headA == headB)
				return headA;
			headA = headA->next;
			headB = headB->next;
		}

		return nullptr;
	}
};


//������˫ָ��
//�˷�6�����������ཻ����pAָ���ߵ�ͷ�󣬻�ָ��B�����ͷ����ʱ��pBָ��ʣ�µĽڵ���==B����ڵ���-A��������
//��pBָ���ߵ�ͷ��ָ��A�����ͷ����ʱ��ָ����ָ����ĳ�����ͬ��Ҳ��ֻ��Ҫ����ͬ������߼���������
//�������ཻ�������������������ͬ����ͬ������������ѭ����������pA=pB=nullptr��������η���pA����
//���˸о������Ԫ������õ��൱����
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		if (headA == nullptr || headB == nullptr) {
			return nullptr;
		}
		ListNode* pA = headA, * pB = headB;
		while (pA != pB) {
			pA = pA == nullptr ? headB : pA->next;
			pB = pB == nullptr ? headA : pB->next;
		}
		return pA;
	}
};


//82. ɾ�����������е��ظ�Ԫ�� II

//��һ:����ԭ�������޸ģ�ֱ���½��������Ѳ��ظ�����������
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {

		ListNode* prev = nullptr, * cur = head, * ans = nullptr, * tail = nullptr;
		while (cur) {
			while (cur && cur->next && cur->val == cur->next->val) {
				int num = cur->val;
				while (cur && cur->val == num) {
					cur = cur->next;
				}
			}
			if (!ans) {
				ans = cur;
				tail = cur;
			} else {
				tail->next = cur;
				tail = tail->next;
			}
			if (cur)
				cur = cur->next;

		}

		return ans;

	}
};


//��������ԭ������ɾ��,ɾ��ԭ���ظ���㣬��ֹ���ڴ�й¶
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* prev = nullptr, * cur = head;
		while (cur) {
			while (cur && cur->next && cur->val == cur->next->val) {
				int num = cur->val;
				//ȥ���ظ�Ԫ��
				while (cur && cur->val == num) {
					ListNode* del = cur;
					cur = cur->next;
					delete del;
				}
			}
			if (cur) {
				if (!prev) {
					head = cur;
					prev = cur;
				} else {
					prev->next = cur;
					prev = prev->next;
				}

				cur = cur->next;

			}
		}
		if (prev)
			prev->next = nullptr;

		return head;
	}
};

//��
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode* prev = nullptr;
		ListNode* cur = head;
		ListNode* next = head->next;

		while (next)
		{
			if (cur->val != next->val) {
				prev = cur;
				cur = next;
				next = next->next;
			} else {
				while (next && cur->val == next->val) {
					next = next->next;
				}

				if (prev) {
					prev->next = next;
				} else {
					head = next;
				}

				//�����ͷ��ظ����
				while (cur != next) {
					ListNode* del = cur;
					cur = cur->next;
					delete del;
				}
				if (next)
					next = next->next;
			}

		}
		return head;
	}
};

//�ٽ⣬�˷�ʹ�����ƽڵ㣬���������ͷ������������ܶ��ˣ����༶next���´���ɶ��Խ��ͣ����װ��߼���죬Ҳû���������ͷţ���Ȼ���ⲻӰ�죩
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head) {
			return head;
		}

		ListNode* dummy = new ListNode(0, head);

		ListNode* cur = dummy;
		while (cur->next && cur->next->next) {
			if (cur->next->val == cur->next->next->val) {
				int x = cur->next->val;
				while (cur->next && cur->next->val == x) {
					cur->next = cur->next->next;
				}
			} else {
				cur = cur->next;
			}
		}

		return dummy->next;
	}
};

