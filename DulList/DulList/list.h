#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
//双向链表
//特点：结构复杂，使用简单

typedef int LTDataType;
typedef struct ListNode
{
	struct ListNode* next;
    struct ListNode* prev;
	LTDataType data;

}ListNode;
 
//初始化法一
//void ListInit(ListNode** pphead);
//初始化法二
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
//在pos前面插入
void ListInsert(ListNode* pos, LTDataType x); 
void ListErase(ListNode* pos);


