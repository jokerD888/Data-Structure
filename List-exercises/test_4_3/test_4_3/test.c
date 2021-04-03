#define _CRT_SECURE_NO_WARNINGS 1

//876. ������м���
//����һ��ͷ���Ϊ head �ķǿյ���������������м��㡣
//����������м��㣬�򷵻صڶ����м��㡣

/**
  Definition for singly-linked list.
  */
#include<stdio.h>
  struct ListNode {
      int val;
      struct ListNode *next;
  };
 


struct ListNode* middleNode(struct ListNode* head) 
{
    //struct ListNode* slow = head;
    //struct ListNode* fast = head;
    //struct ListNode* next = head;


    //while (fast)
    //{
    //    
    //    next = fast->next;
    //    if (next == NULL)
    //        break;
    //    fast = next->next;

    //    slow = slow->next;

    //}
    //return slow;


    //��
    struct ListNode* slow = head;
    struct ListNode* fast = head;


    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;

}


//���ӣ�https://www.nowcoder.com/questionterminal/529d3ae5a407492994ad2a246518148a
//��Դ��ţ����
//
//�����е�����k�����
//�ȶ�ָ����1242425ʱ�����ƣ�c / c++ 1�룬��������2��ռ����ƣ�c / c++ 64m����������128m
//�㷨֪ʶ��Ƶ����
//����һ����������������е�����k����㡣
//ʾ��1
//����
//1, { 1,2,3,4,5 }
//���
//{ 5 }

  struct ListNode {
 	int val;
 	struct ListNode *next;
  };
 
struct ListNode* FindKthToTail(struct ListNode* pListHead, int k) 
{

    struct ListNode* slow = pListHead;
    struct ListNode* fast = pListHead;

    while (k--)
    {
        if (fast)
            fast = fast->next;
        else
            return NULL;
    }

    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;

}


//21. �ϲ�������������
//��������������ϲ�Ϊһ���µ� ���� �������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�
//�ⷨ���½�����ȡС�������β�� 
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) 
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    struct ListNode* head = l1, * tail = NULL;
    if (l1->val < l2->val)
    {
        head = tail = l1;
        l1 = l1->next;
    }
    else
    {
        head = tail = l2;
        l2 = l2->next;
    }

    //ȡСβ��
    while (l1 && l2)
    {
        if (l1->val < l2->val)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else
        {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    if (l1)
        tail->next = l1;
    else
        tail->next = l2;
    return head;

}

