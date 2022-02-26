#define _CRT_SECURE_NO_WARNINGS 1
#pragma one

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
typedef int STDataType;

//静态
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

//出栈入栈
void StackPush(ST* ps, STDataType x);
void StackPop(ST* ps);
//取栈顶元素
STDataType StackTop(ST* ps);
//栈的大小
int StackSize(ST* ps);
//判断栈是否为空
//int StackEmpty(ST* ps); //（非空返回1，空返回0）
//或
bool StackEmpty(ST* ps);