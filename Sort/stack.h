#define _CRT_SECURE_NO_WARNINGS 1
#pragma one

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
typedef int STDataType;

//��̬
//#define MAX 10000
//struct Stack
//{
//	STDataType a[MAX];
//	int top;
//	 
//};



typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;

void StackInit(ST* ps);
void StackDestory(ST* ps);

//��ջ��ջ
void StackPush(ST* ps, STDataType x);
void StackPop(ST* ps);
//ȡջ��Ԫ��
STDataType StackTop(ST* ps);
//ջ�Ĵ�С
int StackSize(ST* ps);
//�ж�ջ�Ƿ�Ϊ��
//int StackEmpty(ST* ps); //���ǿշ���1���շ���0��
//��
bool StackEmpty(ST* ps);