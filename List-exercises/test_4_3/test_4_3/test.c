#define _CRT_SECURE_NO_WARNINGS 1

//876. 链表的中间结点
//给定一个头结点为 head 的非空单链表，返回链表的中间结点。
//如果有两个中间结点，则返回第二个中间结点。

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


    //或
    struct ListNode* slow = head;
    struct ListNode* fast = head;


    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;

}


//链接：https://www.nowcoder.com/questionterminal/529d3ae5a407492994ad2a246518148a
//来源：牛客网
//
//链表中倒数第k个结点
//热度指数：1242425时间限制：c / c++ 1秒，其他语言2秒空间限制：c / c++ 64m，其他语言128m
//算法知识视频讲解
//输入一个链表，输出该链表中倒数第k个结点。
//示例1
//输入
//1, { 1,2,3,4,5 }
//输出
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


//21. 合并两个有序链表
//将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
//解法，新建链表取小结点下来尾插 
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

    //取小尾插
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

