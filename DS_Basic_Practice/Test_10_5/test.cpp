#define _CRT_SECURE_NO_WARNINGS 1

//����


#include<iostream>
using namespace std;
#include<vector>
#include<deque>
//25. K ��һ�鷭ת����


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//
////��һ��ģ�⣬k��k���ķ�ת
//class Solution {
//public:
//	ListNode* reverseKGroup(ListNode* head, int k) {
//		if (!head || k == 1)
//			return head;
//
//		ListNode* dummy = new ListNode(0, head);//ѽ�ڵ�
//		ListNode* prev = dummy, * cur = dummy;//prevָ���ϸ�k���ȵ������δ�ڵ�
//		while (cur) {
//			ListNode* tmp = cur->next;//tmp��¼ԭk������������׽ڵ�
//			int n = k;
//			//�ҵ�k���������β�ڵ�
//			while (n--) {
//				
//				cur = cur->next;
//				if (!cur)
//					return dummy->next;
//			}
//			//����һ����������������
//			prev->next = cur;
//
//			
//			//beforeΪ��ǰ�ڵ��ǰһ���ڵ㣬��ʼ��Ϊ��һ��K����������׽ڵ㣬nextΪcur�ڵ��дһ���ڵ�
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
////��
//class Solution {
//public:
//    // ��תһ�����������ҷ����µ�ͷ��β
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
//            // �鿴ʣ�ಿ�ֳ����Ƿ���ڵ��� k
//            for (int i = 0; i < k; ++i) {
//                tail = tail->next;
//                if (!tail) {
//                    return hair->next;
//                }
//            }
//            ListNode* nex = tail->next;
//            // ������ C++17 ��д����Ҳ����д��
//            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
//            // head = result.first;
//            // tail = result.second;
//            tie(head, tail) = myReverse(head, tail);
//            // �����������½ӻ�ԭ����
//            pre->next = head;
//            tail->next = nex;
//            pre = tail;
//            head = tail->next;
//        }
//
//        return hair->next;
//    }
//};


//143. ��������

//��һ������ӳ��,��ÿ���ڵ�ĵ�ַ���浽������ٱ�������next��ָ��
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


//�������뷨һ���ƣ���������˫�˶���
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

//���������Ž�
//����Ŀ������Ϊ��ԭ��������˺ͷ�ת����Ұ�˺ϲ���Ľ����
//��Ϊ��������ԭ����԰�֣��ٽ��Ҳ�������ת������ٺϲ�
class Solution {
public:
	void reorderList(ListNode* head) {
		if (head == nullptr) {
			return;
		}
		ListNode* mid = middleNode(head);//�м�ڵ�
		ListNode* l1 = head;
		ListNode* l2 = mid->next;
		mid->next = nullptr;//l1��β
		l2 = reverseList(l2);//l2��ת
		mergeList(l1, l2);//l1 ��l2 �ϲ�
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