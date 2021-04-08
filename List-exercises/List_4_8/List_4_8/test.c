#define _CRT_SECURE_NO_WARNINGS 1
//����ָ�
//����һ�����ͷָ�� ListNode* pHead����һ��ֵx����дһ�δ��뽫����С��x�Ľ������������֮ǰ���Ҳ��ܸı�ԭ��������˳��
//�����������к�������ͷָ�롣
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


//����Ļ��Ľṹ
//����һ�����������һ��ʱ�临�Ӷ�ΪO(n), ����ռ临�Ӷ�ΪO(1)���㷨���ж����Ƿ�Ϊ���Ľṹ��
//����һ�������ͷָ��A���뷵��һ��boolֵ���������Ƿ�Ϊ���Ľṹ����֤������С�ڵ���900��

//struct ListNode* reverseList(struct ListNode* head) {
//    struct ListNode* newHead = NULL;
//    struct ListNode* cur = head;
//
//    while (cur)
//    {
//        struct ListNode* next = cur->next;
//
//        //ͷ��
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