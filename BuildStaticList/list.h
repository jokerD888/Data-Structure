#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define MAXSIZE 20
#define ElemType char
 typedef struct SLinkList
{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];//component是结构体数组，SLinkList是一个结构体类型的数组

 //typedef struct SLinkList SLL;
//初始化备用链表
void InitSpare(SLinkList space);
//分配数据结点
int MallocSL(SLinkList space);
//将空闲结点回收到备用链表
void FreeSL(SLinkList space, int k);

void Print(SLinkList space);



