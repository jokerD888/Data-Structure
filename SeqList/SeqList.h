#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//#define PUSHFRONT 1
//#define POPFRONT 2
//#define PUSHBACK 3
//#define POPBACK 4
//#define INSERT 5
//#define ERASE 6
//#define PRINT 7

enum Option
{
	EXIT,
	PUSHFRONT,
	POPFRONT,
	PUSHBACK,
	POPBACK,
	INSERT,
	ERASE,
	PRINT
};
//顺序表，有效数组在数组中必须是连续的
//静态顺序表设计（固定大小）
//typedef int SLDataType;
//#define N 10
//
////vector
//struct SeqList
//{
//	int a[N];
//	int size;
//};
//void SeqListPushBack(struct SeqList* ps, SLDataType x);
//void SeqListPopBack(struct SeqList* ps);
//void SeqListPushFront(struct SeqList* ps, SLDataType x);
//void SeqListPopFront(struct SeqList* ps);
//


//动态态顺序表设计（大小可变）
typedef int SLDataType;
#define N 10

//vector
typedef struct SeqList
{
	SLDataType* a;
	int size;      //有效数据的个数
	int capacity; //容量空间的大小
}SL,SeqList;



//初始化
void SeqListInit(SL* ps);
//打印
void SeqListPrint(SL* ps);
//增容
void SeqListCheckCapacity(SL* ps);

//尾插尾删  头插头删
void SeqListPushBack(SL* ps, SLDataType x);
void SeqListPopBack(SL* ps);
void SeqListPushFront(SL* ps, SLDataType x);
void SeqListPopFront(SL* ps);
//任意位置的插入和删除
void SeqListInsert(SL*ps, int pos, SLDataType x);
void SeqListErase(SL* ps, int pos);

void menu();
