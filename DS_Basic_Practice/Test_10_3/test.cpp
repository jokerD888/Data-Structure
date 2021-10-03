#define _CRT_SECURE_NO_WARNINGS 1

//����

#include<iostream>
using namespace std;

//24. �������������еĽڵ�

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};


//��һ�������������ƽڵ㣬prevΪ��һ�Ե����һ����㣬curΪ�˶Եĵ�һ����㣬����������н�����������Ϻ����prev��cur��������һ��
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next)
			return head;

		ListNode* dummy = new ListNode(0, head);
		ListNode* prev = dummy, *cur = head;
		while (cur && cur->next) {
			prev->next = cur->next;
			ListNode* second = cur->next->next;
			cur->next->next = cur;
			cur->next = second;

			prev = cur;
			cur = cur->next;

		}
		return dummy->next;

	}
};

//�������ݹ�

class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		ListNode* newHead = head->next;
		head->next = swapPairs(newHead->next);
		newHead->next = head;
		return newHead;
	}
};


//707. �������
//������
class MyLinkedList {
public:
	struct ListNode
	{
		int val;
		struct ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};
	MyLinkedList() {
		tail=head = new ListNode(0, nullptr);	
	}

	int get(int index) {
		if (index < 0 || index >= head->val)
			return -1;
		ListNode* cur = head->next;
		while (index--) {
			cur = cur->next;
		}
		return cur->val;
	}

	void addAtHead(int val) {
		head->next = new ListNode(val, head->next);
		head->val++;
		if (tail == head) 
			tail = head->next;
		
	}

	void addAtTail(int val) {
		tail->next = new ListNode(val);
		tail = tail->next;
		head->val++;
	}

	void addAtIndex(int index, int val) {
		if (index > head->val)
			return;
		if (index == head->val)
			return addAtTail(val);
		if (index < 0)
			return addAtHead(val);

		ListNode* cur=head;
		while (index--) {
			cur = cur->next;
		}
		cur->next = new ListNode(val, cur->next);
		head->val++;
	}

	//�˲��׳���
	void deleteAtIndex(int index) {
		if (index < 0 || index >= head->val)
			return;
		int n = index;			//������ǰ��Ĳ���һ����ֱ�Ӷ�index--����Ϊ������Ҫ�õ�index�ĳ�ֵ��Ҫ����һ������
		ListNode* cur = head;
		while (n--) {
			cur = cur->next;
		}
		ListNode* tmp = cur->next;
		cur->next = cur->next->next;
		delete tmp;
		head->val--;		//������������Ѿ�-1�ˣ���һ���Ͳ���index==head->val-1��
		//���βɾ,tailָ���Ұָ���ˣ���Ҫ���¸���tail
		if (index == head->val)
			tail = cur;
	}
private:
	ListNode* head;
	ListNode* tail;
};


//˫����

class MyLinkedList {
public:
	struct ListNode{
		int val;
		ListNode* next;
		ListNode* prev;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr),prev(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next), prev(nullptr) {}
		ListNode(int x, ListNode* next,ListNode* prev) : val(x), next(next),prev(prev) {}

	};
	MyLinkedList() {
		head = tail = new ListNode(0);
	}

	int get(int index) {
		if (index < 0 || index >= head->val)
			return -1;
		ListNode* cur = head->next;
		while (index--) {
			cur = cur->next;
		}
		return cur->val;

	}

	void addAtHead(int val) {
		head->next = new ListNode(val, head->next, head);
		head->val++;
		if (head == tail)
			tail = head->next;
		else
			head->next->next->prev = head->next;
	}

	void addAtTail(int val) {
		tail->next = new ListNode(val, nullptr, tail);
		tail = tail->next;
		head->val++;
		
	}

	void addAtIndex(int index, int val) {
		if (index > head->val)
			return;
		if (index < 0)
			return addAtHead(val);
		if (index == head->val)
			return addAtTail(val);

		ListNode* cur = head;
		while (index--) {
			cur = cur->next;
		}
		cur->next = new ListNode(val, cur->next, cur);
		cur = cur->next;
		cur->next->prev = cur;

		head->val++;

	}

	void deleteAtIndex(int index) {
		if (index < 0 || index >= head->val)
			return;
		int n = index;
		ListNode* cur = head;
		while (index--) {
			cur = cur->next;
		}
		ListNode* del = cur->next;
		cur->next = cur->next->next;
		if (n == head->val-1) {
			tail = cur;
		} else {
			cur->next->prev = cur;
		}
		delete del;
		head->val--;
		
	}
private:
	ListNode* head;
	ListNode* tail;
};

//����Ĳ����У��ҵ�Ҫ�޸ĵ�λ���������ҪƵ��ʹ�ã������Ѵ˲�����װΪһ����,��߸�����
class MyLinkedList {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode* prev;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next), prev(nullptr) {}
		ListNode(int x, ListNode* next, ListNode* prev) : val(x), next(next), prev(prev) {}

	};
	//����Ҫ��λ�õ���һ���ڵ��ָ��
	MyLinkedList() {
		head = tail = new ListNode(0);
	}

	ListNode* findPos(int index) {
		ListNode* cur = head;
		while (index--)
			cur = cur->next;
		return cur;
	}
	int get(int index) {
		if (index < 0 || index >= head->val)
			return -1;

		return findPos(index)->next->val;

	}

	void addAtHead(int val) {
		head->next = new ListNode(val, head->next, head);
		head->val++;
		if (head == tail)
			tail = head->next;
		else
			head->next->next->prev = head->next;
	}

	void addAtTail(int val) {
		tail->next = new ListNode(val, nullptr, tail);
		tail = tail->next;
		head->val++;

	}

	void addAtIndex(int index, int val) {
		if (index > head->val)
			return;
		if (index < 0)
			return addAtHead(val);
		if (index == head->val)
			return addAtTail(val);

		ListNode* cur = findPos(index);
		cur->next = new ListNode(val, cur->next, cur);
		cur = cur->next;
		cur->next->prev = cur;

		head->val++;

	}

	void deleteAtIndex(int index) {
		if (index < 0 || index >= head->val)
			return;
		int n = index;
		ListNode* cur = findPos(index);
		ListNode* del = cur->next;
		cur->next = cur->next->next;
		if (n == head->val - 1) {
			tail = cur;
		} else {
			cur->next->prev = cur;
		}
		delete del;
		head->val--;

	}
private:
	ListNode* head;
	ListNode* tail;
};

//�ڱ�ͷ�ڵ㲻�ط�Ҫ���ϣ�Ҳ���Ե�����һ���������洢�����ȣ���������ͷ��β�Ͷ���addAtIndex����ɣ��������Ļ���
//���ڵ�����β���ʱ�临�ӶȲ�����O��1������Ϊ��O(N)��β��Ч�ʽ��ͣ����Զ���ͷ�����ʹ��addAtIndex����ɣ���β����û��ǵ���ʵ����tialָ��Ϻ�
//����˫��������һ��prevָ�룬β��ͬ����Ҫ�������ǣ�����β�岻��Ҳ����ʵ�֣�����˫�����addAtIndex��˵������prev�Ĵ��ڣ��������˫�����
//���Զ���addAtindex��˵�������Խ�һ���Ż�Ϊʱ�临�Ӷ�Ϊmin(index,size-index)��sizeΪ������
//��

class MyLinkedList {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode* prev;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next), prev(nullptr) {}
		ListNode(int x, ListNode* next, ListNode* prev) : val(x), next(next), prev(prev) {}

	};
	//����Ҫ��λ�õ���һ���ڵ��ָ��
	MyLinkedList() {
		head = tail = new ListNode(0);
	}

	ListNode* findPos(int index, bool flag = false) {
		ListNode* cur;
		if (flag) {
			cur = tail;
			while (index--)
				cur = cur->prev;
		} else {
			cur = head;
			while (index--)
				cur = cur->next;
		}
		return cur;
	}
	int get(int index) {
		if (index < 0 || index >= head->val)
			return -1;

		return findPos(index)->next->val;

	}

	void addAtHead(int val) {
		head->next = new ListNode(val, head->next, head);
		head->val++;
		if (head == tail)
			tail = head->next;
		else 
			head->next->next->prev = head->next;
		
	}

	void addAtTail(int val) {
		tail->next = new ListNode(val, nullptr, tail);
		tail = tail->next;
		head->val++;

	}

	void addAtIndex(int index, int val) {
		if (index > head->val)
			return;
		if (index < 0)
			return addAtHead(val);
		if (index == head->val)
			return addAtTail(val);
		ListNode* cur;
		if (index < head->val - index) {
			cur = findPos(index);
		} else {
			cur = findPos(head->val - index, true);
		}

		cur->next = new ListNode(val, cur->next, cur);
		cur = cur->next;
		cur->next->prev = cur;

		head->val++;

	}

	void deleteAtIndex(int index) {
		if (index < 0 || index >= head->val)
			return;
		int n = index;
		ListNode* cur = findPos(index);
		ListNode* del = cur->next;
		cur->next = cur->next->next;
		if (n == head->val - 1) {
			tail = cur;
		} else {
			cur->next->prev = cur;
		}
		delete del;
		head->val--;

	}
private:
	ListNode* head;
	ListNode* tail;
};




/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

int main(void) {

	MyLinkedList list;
	list.addAtHead(1);
	list.addAtTail(3);
	list.addAtIndex(1, 2);
	cout << list.get(1);
	list.deleteAtIndex(1);
	cout << list.get(1);
	list.addAtHead(1);
	list.addAtTail(3);
	list.addAtIndex(1, 2);
	cout << list.get(1);



	list.addAtHead(2);
	list.addAtHead(1);

	list.addAtIndex(3, 0);
	list.deleteAtIndex(2);
	list.addAtHead(6);
	list.addAtTail(4);
	

	list.deleteAtIndex(5);
	list.addAtTail(4);


	return 0;
}