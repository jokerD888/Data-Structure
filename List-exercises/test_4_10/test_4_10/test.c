#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//138. ���ƴ����ָ�������
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
//	//1.������㵽Դ�ڵ��
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
//	//2.����������random
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
//	//3.��
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
//		//��
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

//147. ��������в�������
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
//		//��cur����sortHead�����У�����������
//		//ͷ��
//		if (cur->val <= sortHead->val)
//		{
//			cur->next = sortHead;
//			sortHead = cur; 
//		}
//		else
//		{
//			//�м����
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
//			//β��
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

//83. ɾ�����������е��ظ�Ԫ��
 //typedef struct ListNode Node;
 //struct ListNode* deleteDuplicates(struct ListNode* head) 
 //{
	// if (head == NULL || head->next == NULL)
	//	 return head;
	// Node* cur = head;
	// Node* next = head->next;

	// while (next)
	// {
	//	//��ͬ
	//	 if (cur->val != next->val)
	//	 {
	//		 cur = next;
	//		 next = next->next;
	//	 }
	//	 else
	//	 {
	//		 //��ͬ
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


 //82. ɾ�����������е��ظ�Ԫ�� II

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
			 

			 //�ͷ�
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