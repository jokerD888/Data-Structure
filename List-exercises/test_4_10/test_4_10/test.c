#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//138. 复制带随机指针的链表
//#include<stdio.h>
//struct Node {
//	int val;
//	struct Node* next;
//	struct Node* random;
//	
//};
//
//typedef struct Node Node;
//struct Node* copyRandomList(struct Node* head) 
//{
//	if (head == NULL)
//		return NULL; 
//	//1.拷贝结点到源节点后方
//	Node* cur = head;
//	while (cur)
//	{
//		Node* copy = (Node*)malloc(sizeof(Node));
//		copy->next = NULL;
//		copy->random = NULL;
//		copy->val = cur->val;
//
//		copy->next = cur->next;
//		cur->next = copy;
//
//		cur = copy->next;
//
//	}
//
//	//2.处理拷贝结点的random
//	cur = head;
//	while (cur)
//	{
//		Node* copy = cur->next;
//		if (cur->random)
//			copy->random = cur->random->next;
//		else
//			copy->random = NULL;
//
//		cur = cur->next->next;
//	}
//
//	//3.拆
//	cur = head;
//	Node* copyhead = head->next;
//	while (cur)
//	{
//		
//	/*		Node* copy = cur->next; 
//			if (copy->next != NULL)
//			{
//				cur->next = copy->next;
//			
//				copy->next = cur->next->next;
//			}
//			else
//			{
//				copy->next = NULL;
//				cur->next = NULL;
//			}
//
//			cur = cur->next;*/
//		//或
//
//		Node* copy = cur->next;
//		Node* next = copy->next;
//
//		cur->next = next;
//		if (next)
//			copy->next = next->next;
//		else
//			copy->next = NULL;
//
//		cur = next;
//
//	}
//	return copyhead;
//}

//147. 对链表进行插入排序
#include<stdio.h>
 struct ListNode {
	int val;
	struct ListNode* next;
};
 //typedef struct ListNode Node;
//struct ListNode* insertionSortList(struct ListNode* head) 
//{
//	if (head == NULL || head->next == NULL)
//		return head;
//	Node* sortHead = head;
//	Node* cur = head->next;
//	sortHead->next = NULL;
//
//	while (cur)
//	{
//		Node* next = cur->next;
//
//		//把cur插入sortHead链表中，并保持有序
//		//头插
//		if (cur->val <= sortHead->val)
//		{
//			cur->next = sortHead;
//			sortHead = cur; 
//		}
//		else
//		{
//			//中间插入
//			Node* sortPrev = sortHead;
//			Node* sortCur = sortHead->next;
//			while (sortCur)
//			{
//				if (cur->val <= sortCur->val)
//				{
//					sortPrev->next = cur;
//					cur->next = sortCur;
//					break;
//				}
//				else
//				{
//					sortPrev = sortCur;
//					sortCur = sortCur->next;
//				}
//			}
//
//			//尾插
//			if (sortCur == NULL)
//			{
//				sortPrev->next = cur;
//				cur->next = NULL;
//			}
//		}
//		cur = next;
//	}
//	return sortHead;
//	
//}

//83. 删除排序链表中的重复元素
 //typedef struct ListNode Node;
 //struct ListNode* deleteDuplicates(struct ListNode* head) 
 //{
	// if (head == NULL || head->next == NULL)
	//	 return head;
	// Node* cur = head;
	// Node* next = head->next;

	// while (next)
	// {
	//	//不同
	//	 if (cur->val != next->val)
	//	 {
	//		 cur = next;
	//		 next = next->next;
	//	 }
	//	 else
	//	 {
	//		 //相同
	//		 if (next->next == NULL)
	//		 {
	//			 cur->next = NULL;
	//			 return head;;
	//		 }
	//		 next = next->next;
	//		 while (next)
	//		 {
	//			 
	//			 if (next->val != cur->val)
	//			 {
	//				 cur->next = next;
	//				 cur = cur->next;
	//				 next = next->next;
	//				 break;
	//			 }
	//			 next = next->next;
	//		 }
	//		 cur->next = next;

	//	 }
	// }
	// return head;
 //}


 //82. 删除排序链表中的重复元素 II

typedef struct ListNode Node;
 struct ListNode* deleteDuplicates(struct ListNode* head) 
 {
	 if (head == NULL || head->next==NULL)
		 return head;
	 Node* prev = NULL;
	 Node* cur = head;
	 Node* next = head->next;

	 while (next)
	 {
		 if (cur->val != next->val)
		 {
			 prev = cur;
			 cur = next;
			 next = next->next;
		  }
		 else
		 {

			 while (next && cur->val == next->val)
			 {
				 next = next->next;
			 }
			 
			 if (prev)
			 {
				prev->next = next;
			 }
			 else
			 {
				 head = next;
			 }
			 

			 //释放
			 while (cur != next)
			 {
				 Node* del = cur;
				 cur = cur->next;
				 free(del);
			 }
			 if (next)
				 next = next->next;
		 }

	 }
	 return head;
 }