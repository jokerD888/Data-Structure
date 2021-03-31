#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
typedef int SListDataType;
//结点
typedef struct SListNode
{
	SListDataType data;
	struct SListNode* next;

}SListNode;
//尾插
void SListPushBack(SListNode** pphead, SListDataType x); 
void SListPopBack(SListNode** pphead);

void SListPushFront(SListNode** pphead, SListDataType x);
void SListPopFront(SListNode* phead);

void SListPrint(SListNode* phead);
SListNode* SListFind(SListNode* phead,SListDataType x);

//在某位置后方插入/删除
void SListInserAfter(SListNode* pos, SListDataType x);
void SListEraseAfter(SListNode* pos);