#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define MAXSIZE 20
#define ElemType char
 typedef struct SLinkList
{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];//component�ǽṹ�����飬SLinkList��һ���ṹ�����͵�����

 //typedef struct SLinkList SLL;
//��ʼ����������
void InitSpare(SLinkList space);
//�������ݽ��
int MallocSL(SLinkList space);
//�����н����յ���������
void FreeSL(SLinkList space, int k);

void Print(SLinkList space);



