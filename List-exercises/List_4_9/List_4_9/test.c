#define _CRT_SECURE_NO_WARNINGS 1

//160. 相交链表
#include<stdio.h>
 struct ListNode {
    int val;
    struct ListNode* next;
    
};
 typedef struct ListNode ListNode;
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) 
{
    int nA = 0, nB = 0,n;
    ListNode* curA = headA;
    ListNode* curB = headB;

    while (curA)
    {
        nA++;
        curA = curA->next;
    }
    while (curB)
    {
        nB++;
        curB = curB->next;
    }

    curA = headA;
    curB = headB;
    if (nA > nB)
    {
        n = nA - nB;
        while ( n )
        {
            curA = curA->next;
            n--;
        }
    }
    else
    {
        n = nB - nA;
        while (n)
        {
            curB = curB->next;
            n--;
        }
    }

    while (curA)
    {
        if (curA == curB)
            return curA;
        else
        {
            curA = curA->next;
            curB = curB->next;
        }
    }
    return NULL;

}

//或
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB)
{
    int la = 0, lb = 0;
    ListNode* curA = headA;
    ListNode* curB = headB;

    while (curA)
    {
        ++la;
        curA = curA->next;
    }

    while (curB)
    {
        ++lb;
        curB = curB->next;
    }

    ListNode* longList = headA;
    ListNode* shortList = headB;

    if (lb > la)
    {
        longList = headB;
        shortList= headA;
    }
    int gap = abs(la - lb); 
    while (gap--)
    {
        longList = longList->next;
    }

    while (longList)
    {
        if (longList == shortList)
            return longList;
        
        longList = longList->next;
        shortList = shortList->next;
        
    }
    return NULL;

}


//141. 环形链表

//bool hasCycle(struct ListNode* head) 
//{
//    struct ListNode* fast = head;
//    struct ListNode* slow = head;
//    
//    while (fast && fast->next)
//    {
//        slow = slow->next;
//        fast = fast->next->next;
//        
//        if (slow == fast)
//            return true;
//    }
//    return false;
//}

//142. 环形链表 II
//找到相遇点，断开，形成两个链表，找两链表交点
//易理解，代码量多
struct ListNode* detectCycle(struct ListNode* head) 
{
    struct ListNode* fast = head;
    struct ListNode* slow = head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            break;
    }

    if (fast == NULL)
    {
        return NULL;
    }
    struct ListNode* newhead = fast->next;
    slow->next = NULL;

    struct ListNode* cur = head;
    struct ListNode* newcur = newhead;
    int n1 = 0, n2 = 0;
    struct ListNode* longList = head;
    struct ListNode* shortList = newhead;
    
    while (cur)
    {
        n1++;
        cur = cur->next;
    }
    while (newcur)
    {
        n2++;
        newcur = newcur->next;
    }

    if (n2 > n1)
    {
        longList = newhead;
        shortList = head;
    }
    int gap = abs(n1 - n2);
    while (gap--)
    {
        longList = longList->next;
    }

    while (longList)
    {
        if (longList == shortList)
            return longList;
        longList = longList->next;
        shortList = shortList->next;
    }

    return NULL;

    
}