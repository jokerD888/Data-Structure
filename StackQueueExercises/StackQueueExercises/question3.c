#define _CRT_SECURE_NO_WARNINGS 1

//用栈实现队列
//先入栈到s1再出到另一个栈s2，再从s2出栈即可完成入队出队，若想再入队，s2出栈到s1中，再s1中入栈
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
void StackInit(ST* ps)
{
	assert(ps);
	ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	if (ps->a == NULL)
	{
		printf("realloc fail\n");
		exit(-1);
	}
	ps->capacity = 4;
	ps->top = 0;//top指向的是栈顶元素的下一个
	//ps->top = -1;//top指向的是栈顶元素
}
void StackDestory(ST* ps)
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}

//出栈入栈
void StackPush(ST* ps, STDataType x)
{
	assert(ps);

	//满了,增容
	if (ps->top == ps->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * ps->capacity * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		else
		{
			ps->a = tmp;
			ps->capacity *=2;
		}

	}
	ps->a[ps->top] = x;
	ps->top++;
}
void StackPop(ST* ps)
{
	assert(ps);
	//如果栈空，再pop，直接报错
	assert(ps->top > 0);
	ps->top--;
}
//取栈顶元素
STDataType StackTop(ST* ps)
{
	assert(ps);
	//防止栈空
	assert(ps->top > 0);

	return ps->a[ps->top - 1];
}
//栈的大小
int StackSize(ST* ps)
{
	assert(ps);
	return ps->top;
}
//判断栈是否为空
//int StackEmpty(ST* ps); //（非空返回1，空返回0）
//或
bool StackEmpty(ST* ps)
{
	assert(ps);
	return ps->top == 0;//真为1,返回true,假为0,返回false
}


typedef struct {
	ST s1;
	ST s2;
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* ps = malloc(sizeof(MyQueue));
	if (ps == NULL)
	{
		printf("malloc failed!\n");
		exit(-1);
	}

	StackInit(&ps->s1);
	StackInit(&ps->s2);

	return ps;

}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	if (!StackEmpty(&obj->s2))
	{
		StackPush(&obj->s1, StackTop(&obj->s2));
	}
	StackPush(&obj->s1, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	while (!StackEmpty(&obj->s1))
	{
		StackPush(&obj->s2, StackTop(&obj->s1));
		StackPop(&obj->s1);
	}

	if (StackEmpty(&obj->s2))
	{
		printf("请先入队元素\n");
		exit(-1);
	}

	int result = StackTop(&obj->s2);
	StackPop(&obj->s2);

	while (!StackEmpty(&obj->s2))
	{
		StackPush(&obj->s1, StackTop(&obj->s2));
		StackPop(&obj->s2);
	}

	return result;

}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	while (!StackEmpty(&obj->s1))
	{
		StackPush(&obj->s2, StackTop(&obj->s1));
		StackPop(&obj->s1);

	}

	if (StackEmpty(&obj->s2))
	{
		printf("请先入队元素\n");
		exit(-1);
	}

	int result = StackTop(&obj->s2);

	return result;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return StackEmpty(&obj->s1) && StackEmpty(&obj->s2);
}

void myQueueFree(MyQueue* obj) {
	StackDestory(&obj->s1);
	StackDestory(&obj->s2);
	free(obj);

}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/