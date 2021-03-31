#define _CRT_SECURE_NO_WARNINGS 1
#include"SList.h"


void TestSList1()
{
	SListNode* pList = NULL;
	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);

	SListPrint(pList);

	SListPopBack(&pList);
	SListPopBack(&pList);
	SListPopBack(&pList);
	SListPopBack(&pList);
	SListPopBack(&pList);

	SListPrint(pList);


	SListPushFront(&pList, 1);
	SListPushFront(&pList, 2);
	SListPushFront(&pList, 3);
	SListPushFront(&pList, 4);
	SListPushFront(&pList, 5);

	SListPrint(pList);

	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);

	SListPrint(pList);


}
void TestSList2()
{
	SListNode* pList = NULL;
	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);

	SListPrint(pList);

	SListNode* pos = SListFind(pList, 3);
	if (pos)
	{
		pos->data = 30;
	}
	SListInserAfter(pos, 40);
	SListPrint(pList);

	SListEraseAfter(pos);
	SListPrint(pList);

}
int main(void)
{
	
	//TestSList1();
	TestSList2();
	return 0;
}
