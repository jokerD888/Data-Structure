#define _CRT_SECURE_NO_WARNINGS 1

//链表

#include<iostream>
using namespace std;

//24. 两两交换链表中的节点

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};


//法一：迭代，设置哑节点，prev为上一对的最后一个结点，cur为此对的第一个结点，随后两两进行交换，交换完毕后更新prev和cur，交换下一对
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

//法二：递归

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


//707. 设计链表
//单链表
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

	//此步易出错
	void deleteAtIndex(int index) {
		if (index < 0 || index >= head->val)
			return;
		int n = index;			//不可像前面的操作一样，直接对index--，因为后续还要用到index的初值，要用另一个变量
		ListNode* cur = head;
		while (n--) {
			cur = cur->next;
		}
		ListNode* tmp = cur->next;
		cur->next = cur->next->next;
		delete tmp;
		head->val--;		//这里结点的数量已经-1了，下一步就不是index==head->val-1了
		//如果尾删,tail指针就野指针了，需要重新更新tail
		if (index == head->val)
			tail = cur;
	}
private:
	ListNode* head;
	ListNode* tail;
};


//双链表

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

//上面的操作中，找到要修改的位置这个操作要频繁使用，不妨把此操作封装为一函数,提高复用性
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
	//返回要找位置的上一个节点的指针
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

//哨兵头节点不必非要用上，也可以单独用一个变量来存储链表长度，甚至不妨头插尾巴都用addAtIndex来完成，但这样的话，
//对于单链表尾插的时间复杂度不再是O（1）而变为了O(N)，尾插效率降低，所以对于头插可以使用addAtIndex来完成，但尾插最好还是单独实现用tial指针较好
//对于双链表，多了一个prev指针，尾插同样需要单独考虑，所以尾插不妨也单独实现，对于双链表的addAtIndex来说，由于prev的存在，链表可以双向访问
//所以对于addAtindex来说，还可以进一步优化为时间复杂度为min(index,size-index)，size为链表长度
//如

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
	//返回要找位置的上一个节点的指针
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