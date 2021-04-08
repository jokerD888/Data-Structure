#define _CRT_SECURE_NO_WARNINGS 1
//链表分割
//现有一链表的头指针 ListNode* pHead，给一定值x，编写一段代码将所有小于x的结点排在其余结点之前，且不能改变原来的数据顺序，
//返回重新排列后的链表的头指针。
//typedef struct ListNode ListNode;
//class Partition {
//public:
//    ListNode* partition(ListNode* pHead, int x)
//    {
//        ListNode* lessHead, * lessTail;
//        ListNode* greaterHead, * greaterTail;
//        lessHead = lessTail = (ListNode*)malloc(sizeof(ListNode));
//        greaterHead = greaterTail = (ListNode*)malloc(sizeof(ListNode));
//        lessHead->next = greaterHead->next = NULL;
//
//        ListNode* cur = pHead;
//        while (cur)
//        {
//            if (cur->val < x)
//            {
//                lessTail->next = cur;
//                lessTail = lessTail->next;
//            }
//            else
//            {
//                greaterTail->next = cur;
//                greaterTail = greaterTail->next;
//            }
//            cur = cur->next;
//        }
//        lessTail->next = greaterHead->next;
//        greaterTail->next = NULL;
//
//        ListNode* list = lessHead->next;
//        free(lessHead);
//        free(greaterHead);
//
//        return list;
//
//
//    }
//};


//链表的回文结构
//对于一个链表，请设计一个时间复杂度为O(n), 额外空间复杂度为O(1)的算法，判断其是否为回文结构。
//给定一个链表的头指针A，请返回一个bool值，代表其是否为回文结构。保证链表长度小于等于900。

//struct ListNode* reverseList(struct ListNode* head) {
//    struct ListNode* newHead = NULL;
//    struct ListNode* cur = head;
//
//    while (cur)
//    {
//        struct ListNode* next = cur->next;
//
//        //头插
//        cur->next = newHead;
//        newHead = cur;
//
//        cur = next;
//    }
//    return newHead;
//}
//class PalindromeList {
//public:
//    bool chkPalindrome(ListNode* A)
//    {
//        ListNode* fast = A;
//        ListNode* slow = A;
//        ListNode* prev = NULL;
//
//        while (fast && fast->next)
//        {
//            prev = slow;
//            slow = slow->next;
//            fast = fast->next->next;
//        }
//        prev->next = NULL;
//        slow = reverseList(slow);
//        while (A)
//        {
//            if (A->val != slow->val)
//            {
//                return false;
//            }
//            else
//            {
//                A = A->next;
//                slow = slow->next;
//            }
//        }
//        return true;
//    }
//};