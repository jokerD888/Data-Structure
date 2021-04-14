#define _CRT_SECURE_NO_WARNINGS 1
//链表结构
//1.单向，双向
//2.带头，不带头
//3.循环，不循环
//常用：无头单向非循环链表，带头双向循环链表
#include"list.h"

void TestList1()
{
	/*ListNode* phead = NULL;
	ListInit(&phead);*/
	ListNode* phead = ListInit();
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPushBack(phead, 4);

	ListPrint(phead);

	ListPopBack(phead);
	ListPopBack(phead);
	ListPopBack(phead);
	ListPopBack(phead);

	ListPrint(phead);


	ListPushFront(phead, 1);
	ListPushFront(phead, 2);
	ListPushFront(phead, 3);
	ListPushFront(phead, 4);
	ListPushFront(phead, 5);

	ListPrint(phead);


	ListPopFront(phead);
	ListPopFront(phead);
	ListPrint(phead);

	ListPopFront(phead);
	ListPopFront(phead);
	ListPrint(phead);


	ListDestory(&phead);

}

void TestList2()
{
	ListNode* phead = ListInit();
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPushBack(phead, 4);
	ListPrint(phead);
	
	ListNode* pos = ListFind(phead, 3);
	ListInsert(pos, 30);
	ListPrint(phead);

	ListErase(pos);
	ListPrint(phead);

	ListDestory(&phead);

 }
int main(void)
{
	TestList1();
	//TestList2();
 	return 0;
}