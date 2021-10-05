#define _CRT_SECURE_NO_WARNINGS 1

//链表


#include<iostream>
using namespace std;
#include<vector>
#include<deque>
//25. K 个一组翻转链表


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//
////法一：模拟，k个k个的反转
//class Solution {
//public:
//	ListNode* reverseKGroup(ListNode* head, int k) {
//		if (!head || k == 1)
//			return head;
//
//		ListNode* dummy = new ListNode(0, head);//呀节点
//		ListNode* prev = dummy, * cur = dummy;//prev指向上个k长度的链表的未节点
//		while (cur) {
//			ListNode* tmp = cur->next;//tmp记录原k个长度链表的首节点
//			int n = k;
//			//找到k长度链表的尾节点
//			while (n--) {
//				
//				cur = cur->next;
//				if (!cur)
//					return dummy->next;
//			}
//			//与上一个子链表链接起来
//			prev->next = cur;
//
//			
//			//before为当前节点的前一个节点，初始化为下一个K长度链表的首节点，next为cur节点的写一个节点
//			ListNode* before = cur->next, * next;
//			cur = tmp, n = k;
//			while (n--) {
//				next = cur->next;
//				cur->next = before;
//				before = cur;
//				cur = next;
//			}
//
//			cur = prev = tmp;
//
//		}
//
//		return dummy->next;
//	}
//};
//
////或
//class Solution {
//public:
//    // 翻转一个子链表，并且返回新的头与尾
//    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
//        ListNode* prev = tail->next;
//        ListNode* p = head;
//        while (prev != tail) {
//            ListNode* nex = p->next;
//            p->next = prev;
//            prev = p;
//            p = nex;
//        }
//        return { tail, head };
//    }
//
//    ListNode* reverseKGroup(ListNode* head, int k) {
//        ListNode* hair = new ListNode(0);
//        hair->next = head;
//        ListNode* pre = hair;
//
//        while (head) {
//            ListNode* tail = pre;
//            // 查看剩余部分长度是否大于等于 k
//            for (int i = 0; i < k; ++i) {
//                tail = tail->next;
//                if (!tail) {
//                    return hair->next;
//                }
//            }
//            ListNode* nex = tail->next;
//            // 这里是 C++17 的写法，也可以写成
//            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
//            // head = result.first;
//            // tail = result.second;
//            tie(head, tail) = myReverse(head, tail);
//            // 把子链表重新接回原链表
//            pre->next = head;
//            tail->next = nex;
//            pre = tail;
//            head = tail->next;
//        }
//
//        return hair->next;
//    }
//};


//143. 重排链表

//法一：数组映射,将每个节点的地址都存到数据里，再遍历更改next的指向
class Solution {
public:
	void reorderList(ListNode* head) {
		ListNode* cur = head;
		vector<ListNode*> node;
		while (cur) {
			node.push_back(cur);
			cur = cur->next;
		}

		int size = node.size();
		int left = 0, right = size - 1;
		//ListNode* dummy = new ListNode(0, head);
		cur = head;
		while (left < right) {
			node[left]->next = node[right];
			node[right--]->next = node[++left];
		}

		node[left]->next = nullptr;
	}
};


//法二：与法一类似，但换成了双端队列
class Solution {
public:
	void reorderList(ListNode* head) {
		if (!head || !head->next)
			return;

		ListNode* cur = head;
		deque<ListNode*> node;
		while (cur) {
			node.push_back(cur);
			cur = cur->next;
		}

		ListNode* before = nullptr;
		while (node.size()>1) {
			ListNode* prev = node.front();
			node.pop_front();
			ListNode* next = node.back();
			node.pop_back();
			if (before)
				before->next = prev;
			prev->next = next;
			before = next;
		}
		if (!node.empty()) {
			before->next = node.front();
			node.front()->next = nullptr;
		}
		else
			before->next = nullptr;

	}
};

//法二，最优解
//利用目标链表即为将原链表的左半端和反转后的右半端合并后的结果。
//分为三步，将原链表对半分，再将右部分链表反转，最后再合并
class Solution {
public:
	void reorderList(ListNode* head) {
		if (head == nullptr) {
			return;
		}
		ListNode* mid = middleNode(head);//中间节点
		ListNode* l1 = head;
		ListNode* l2 = mid->next;
		mid->next = nullptr;//l1封尾
		l2 = reverseList(l2);//l2反转
		mergeList(l1, l2);//l1 ，l2 合并
	}

	ListNode* middleNode(ListNode* head) {
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		ListNode* curr = head;
		while (curr != nullptr) {
			ListNode* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		return prev;
	}

	void mergeList(ListNode* l1, ListNode* l2) {
		ListNode* l1_tmp;
		ListNode* l2_tmp;
		while (l1 != nullptr && l2 != nullptr) {
			l1_tmp = l1->next;
			l2_tmp = l2->next;

			l1->next = l2;
			l1 = l1_tmp;

			l2->next = l1;
			l2 = l2_tmp;
		}
	}
};



int main(void) {

	ListNode a(1, new ListNode(2, new ListNode(3, new ListNode(4, nullptr))));
	Solution s;
	s.reorderList(&a);
	return 0;
}