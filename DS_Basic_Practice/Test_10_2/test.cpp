#define _CRT_SECURE_NO_WARNINGS 1

//链表

#include<iostream>
using namespace std;
#include<list>
#include<unordered_set>
//2. 两数相加


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
//
//// 法一： 
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
////法二：类似
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


//142. 环形链表 II


//法一：快指针一次走两步，慢指针一次走两步，若有环，当快指针与慢指针相遇，即快指针走过的长度是慢指针的两倍，
//此时，答案指针从头开始一次走一步，慢指针也一次走一步，当两指针相遇时即为环的入口
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

//类似: struct ListNode* slow, * fast;
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

//法二：哈希表
//我们遍历链表中的每个节点，并将它记录下来；一旦遇到了此前遍历过的节点，就可以判定链表中存在环。借助哈希表可以很方便地实现。

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


//160. 相交链表


//法一：哈希集合
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

//法二：利用两条链表节点数的差值
//此法随说繁琐但时间空间略优于法一
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


//法三：双指针
//此法6，若两链表相交，若pA指针走到头后，会指向B链表的头，此时，pB指针剩下的节点数==B链表节点数-A链表结点数
//当pB指针走到头后，指向A链表的头，此时两指针所指链表的长度相同，也就只需要两者同步向后走即可相遇。
//若链表不相交，则跟上面的情况基本相同，不同的是两者跳出循环的条件是pA=pB=nullptr，无论如何返回pA即可
//个人感觉这个三元运算符用的相当巧妙
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


//82. 删除排序链表中的重复元素 II

//法一:不在原链表做修改，直接新建答案链表，把不重复的链接起来
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


//法二：在原链表做删除,删除原有重复结点，防止了内存泄露
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
				//去除重复元素
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

//或
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

				//集中释放重复结点
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

//官解，此法使用了哑节点，关于链表的头的情况就清晰很多了，但多级next导致代码可读性降低，容易把逻辑搞混，也没有做结点的释放（虽然做题不影响）
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

