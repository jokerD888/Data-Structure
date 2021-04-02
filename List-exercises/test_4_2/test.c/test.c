#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//剑指 Offer 24. 反转链表
//定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
//示例:
//输入: 1->2->3->4->5->NULL
//输出 : 5->4->3->2->1->NULL
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

//头插法
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
	
	//或

	struct ListNode* newHead = NULL;
	struct ListNode* cur = head;

	while (cur)
	{
		struct ListNode* next = cur->next;

		//头插
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

//203. 移除链表元素
//给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

//残缺版
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

//成品
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

	//或

	struct ListNode* prev = NULL, * cur = head;
	while (cur)
	{
		if (cur->val == val)
		{
			//if(prev==NULL)  //说明要删的元素处于第一个
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