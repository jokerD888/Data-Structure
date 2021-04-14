#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
//˫������
//�ص㣺�ṹ���ӣ�ʹ�ü�

typedef int LTDataType;
typedef struct ListNode
{
	struct ListNode* next;
    struct ListNode* prev;
	LTDataType data;

}ListNode;
 
//��ʼ����һ
//void ListInit(ListNode** pphead);
//��ʼ������
ListNode* ListInit();
void ListDestory(ListNode** pphead);
void ListClear(ListNode* phead);

ListNode* BuyListNode(LTDataType x);
void ListPrint(ListNode* phead);
void ListPushBack(ListNode* pehad, LTDataType x);
void ListPopBack(ListNode* phead);

void ListPushFront(ListNode* pehad, LTDataType x);
void ListPopFront(ListNode* phead);

ListNode* ListFind(ListNode* phead, LTDataType x);
//��posǰ�����
void ListInsert(ListNode* pos, LTDataType x); 
void ListErase(ListNode* pos);


