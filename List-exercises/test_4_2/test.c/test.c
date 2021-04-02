#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//��ָ Offer 24. ��ת����
//����һ������������һ�������ͷ�ڵ㣬��ת�����������ת�������ͷ�ڵ㡣
//ʾ��:
//����: 1->2->3->4->5->NULL
//��� : 5->4->3->2->1->NULL
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode 
{
	int val;
	struct ListNode* next;
};

//struct ListNode* reverseList(struct ListNode* head) {
//	if (head == NULL || head->next == NULL)
//	{
//		return head;
//	}
//	struct ListNode* n1 = NULL;
//	struct ListNode* n2 = head;
//	struct ListNode* n3 = head->next;
//	while (n2 != NULL)
//	{
//		n3 = n2->next;
//		n2->next = n1;
//		n1 = n2;
//		n2 = n3;
//	}
//	return n1;
//
//}

//ͷ�巨
struct ListNode* reverseList(struct ListNode* head)
{
/*	if (head == NULL || head->next == NULL)
	{
		return head;
	}
	struct ListNode* newhead = NULL;
	struct ListNode* cur = head;
	struct ListNode* next = head->next;

	while (next)
	{
		cur->next = newhead;
		newhead = cur;

		cur = next;
		
		next = cur->next;

	}
	cur->next = newhead;
	newhead = cur;
	return newhead;*/
	
	//��

	struct ListNode* newHead = NULL;
	struct ListNode* cur = head;

	while (cur)
	{
		struct ListNode* next = cur->next;

		//ͷ��
		cur->next = newHead;
		newHead = cur;

		cur = next;
	}
	return newHead;


}

//int main(void)
//{
//	int arr[2][3] = { 1,2,3,4,5,6 };
//	int i = 0, j = 0;
//	for (i = 0; i < 3; i++)
//	{
//		for (j = 0; j < 2; j++)
//		{
//			printf("%d ", arr[j][i]);
//		}
//		printf("\n");
//	}
//	return 0;
//}

//203. �Ƴ�����Ԫ��
//����һ�������ͷ�ڵ� head ��һ������ val ������ɾ���������������� Node.val == val �Ľڵ㣬������ �µ�ͷ�ڵ� ��

//��ȱ��
//struct ListNode* removeElements(struct ListNode* head, int val) 
//{
//
//	struct ListNode* phead = head;
//	struct ListNode* cur = head;
//	struct ListNode* next = NULL;
//	//struct LisrNode* prev = NULL;
//	struct LisrNode* pop = NULL;
//
//	while (cur)
//	{
//		if (phead->val==val)
//		{
//			pop = cur;
//			phead = cur->next;
//			cur = cur->next;
//			free(pop);
//			
//		}
//		if (cur->val == val)
//		{
//			pop = cur;
//			cur = cur->next;
//			free(pop);
//		}
//		if (cur == NULL)
//			return phead;
//		cur = cur->next;
//	}
//	return phead;
//}

//��Ʒ
struct ListNode* removeElements(struct ListNode* head, int val)
{
	/*while( head && head->val == val)
	{

		head = head->next;
	}
	if(head==NULL)
		return head;
	struct ListNode* prev = head;
	struct ListNode* next = NULL;

	struct ListNode* cur = head->next;
	while (cur)
	{
		if (cur->val == val)
		{
			next = cur->next;
			prev ->next= next;
			if (prev == NULL)
				break;
			cur = prev->next;
		}
		else
		{
			cur = cur->next;
			prev = prev->next;
		}
	}
	return head;*/

	//��

	struct ListNode* prev = NULL, * cur = head;
	while (cur)
	{
		if (cur->val == val)
		{
			//if(prev==NULL)  //˵��Ҫɾ��Ԫ�ش��ڵ�һ��
			if (cur == head)
			{
				head = cur->next;
				free(cur);
				cur = head;
			}
			else
			{
				prev->next = cur->next;
				free(cur);
				cur = prev->next; 
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return head;


}