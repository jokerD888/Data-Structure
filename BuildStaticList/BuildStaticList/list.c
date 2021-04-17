#define _CRT_SECURE_NO_WARNINGS 1
#include"list.h"
//初始化备用链表
void InitSpare(SLinkList space)
{
	//将一维数组各个分量链成一个备用链表，SLL[0].cur为头指针
	int i = 0;
	for (i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
	}
	space[MAXSIZE - 1].cur = 0;
}

int MallocSL(SLinkList space)
{

	//若备用空间链表为非空，则返回分配的节点下标，否则返回0；
	int i = 0;
	i = space[0].cur;
	if (space[0].cur)
	{
		space[0].cur = space[i].cur;
	}
	return i;
}


//将空闲结点回收到备用链表
void FreeSL(SLinkList space, int k)
{
	//将下标为k的空闲结点回收到备用链表(头插）
	space[k].cur = space[0].cur;
	space[0].cur = k;
}


void Print(SLinkList space)
{
	int cur = space[1].cur;
	while (cur)
	{

		printf("%c->", space[cur].data);
		cur = space[cur].cur;
	}
	printf("NULL\n");
}
