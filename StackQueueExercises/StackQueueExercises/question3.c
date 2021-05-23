#define _CRT_SECURE_NO_WARNINGS 1

//用栈实现队列
// 
//法一：
//先入栈到s1再出到另一个栈s2，再从s2出栈即可完成入队出队，若想再入队，s2出栈到s1中，再s1中入栈

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
//typedef int STDataType;
////静态
////#define MAX 10000
////struct Stack
////{
////	STDataType a[MAX];
////	int top;
////	 
////};
//
//
//
//typedef struct Stack
//{
//	STDataType* a;
//	int top;
//	int capacity;
//}ST;
//
//void StackInit(ST* ps);
//void StackDestory(ST* ps);
//
////出栈入栈
//void StackPush(ST* ps, STDataType x);
//void StackPop(ST* ps);
////取栈顶元素
//STDataType StackTop(ST* ps);
////栈的大小
//int StackSize(ST* ps);
////判断栈是否为空
////int StackEmpty(ST* ps); //（非空返回1，空返回0）
////或
//bool StackEmpty(ST* ps);
//void StackInit(ST* ps)
//{
//	assert(ps);
//	ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
//	if (ps->a == NULL)
//	{
//		printf("realloc fail\n");
//		exit(-1);
//	}
//	ps->capacity = 4;
//	ps->top = 0;//top指向的是栈顶元素的下一个
//	//ps->top = -1;//top指向的是栈顶元素
//}
//void StackDestory(ST* ps)
//{
//	assert(ps);
//	free(ps->a);
//	ps->a = NULL;
//	ps->top = ps->capacity = 0;
//}
//
////出栈入栈
//void StackPush(ST* ps, STDataType x)
//{
//	assert(ps);
//
//	//满了,增容
//	if (ps->top == ps->capacity)
//	{
//		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * ps->capacity * 2);
//		if (tmp == NULL)
//		{
//			printf("realloc fail\n");
//			exit(-1);
//		}
//		else
//		{
//			ps->a = tmp;
//			ps->capacity *=2;
//		}
//
//	}
//	ps->a[ps->top] = x;
//	ps->top++;
//}
//void StackPop(ST* ps)
//{
//	assert(ps);
//	//如果栈空，再pop，直接报错
//	assert(ps->top > 0);
//	ps->top--;
//}
////取栈顶元素
//STDataType StackTop(ST* ps)
//{
//	assert(ps);
//	//防止栈空
//	assert(ps->top > 0);
//
//	return ps->a[ps->top - 1];
//}
////栈的大小
//int StackSize(ST* ps)
//{
//	assert(ps);
//	return ps->top;
//}
////判断栈是否为空
////int StackEmpty(ST* ps); //（非空返回1，空返回0）
////或
//bool StackEmpty(ST* ps)
//{
//	assert(ps);
//	return ps->top == 0;//真为1,返回true,假为0,返回false
//}
//
//
//typedef struct {
//	ST s1;
//	ST s2;
//} MyQueue;
//
///** Initialize your data structure here. */
//
//MyQueue* myQueueCreate() {
//	MyQueue* ps = malloc(sizeof(MyQueue));
//	if (ps == NULL)
//	{
//		printf("malloc failed!\n");
//		exit(-1);
//	}
//
//	StackInit(&ps->s1);
//	StackInit(&ps->s2);
//
//	return ps;
//
//}
//
///** Push element x to the back of queue. */
//void myQueuePush(MyQueue* obj, int x) {
//	if (!StackEmpty(&obj->s2))
//	{
//		StackPush(&obj->s1, StackTop(&obj->s2));
//	}
//	StackPush(&obj->s1, x);
//}
//
///** Removes the element from in front of queue and returns that element. */
//int myQueuePop(MyQueue* obj) {
//	while (!StackEmpty(&obj->s1))
//	{
//		StackPush(&obj->s2, StackTop(&obj->s1));
//		StackPop(&obj->s1);
//	}
//
//	if (StackEmpty(&obj->s2))
//	{
//		printf("请先入队元素\n");
//		exit(-1);
//	}
//
//	int result = StackTop(&obj->s2);
//	StackPop(&obj->s2);
//
//	while (!StackEmpty(&obj->s2))
//	{
//		StackPush(&obj->s1, StackTop(&obj->s2));
//		StackPop(&obj->s2);
//	}
//
//	return result;
//
//}
//
///** Get the front element. */
//int myQueuePeek(MyQueue* obj) {
//	while (!StackEmpty(&obj->s1))
//	{
//		StackPush(&obj->s2, StackTop(&obj->s1));
//		StackPop(&obj->s1);
//
//	}
//
//	if (StackEmpty(&obj->s2))
//	{
//		printf("请先入队元素\n");
//		exit(-1);
//	}
//
//	int result = StackTop(&obj->s2);
//
//	return result;
//}
//
///** Returns whether the queue is empty. */
//bool myQueueEmpty(MyQueue* obj) {
//	return StackEmpty(&obj->s1) && StackEmpty(&obj->s2);
//}
//
//void myQueueFree(MyQueue* obj) {
//	StackDestory(&obj->s1);
//	StackDestory(&obj->s2);
//	free(obj);
//
//}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/



//法二：定义两个栈，pushST和popST，  入数据，往pushST入   出数据，看popST中有没有数据，有直接出，没有就把pushST数据全部导入popST中，再出数据
//规范写法
typedef int STDataType;
struct Stack
{
	STDataType* a;
	int top;       // 栈顶
	int capacity;  // 容量，方便增容
};

//typedef struct Stack ST;
typedef struct Stack Stack;

void StackInit(Stack* pst);
void StackDestroy(Stack* pst);

// 性质就决定在栈顶出入数据
void StackPush(Stack* pst, STDataType x);
void StackPop(Stack* pst);
STDataType StackTop(Stack* pst);

// 空返回1 非空返回0
//int StackEmpty(Stack* pst);
bool StackEmpty(Stack* pst);
int StackSize(Stack* pst);

void StackInit(Stack* pst)
{
	assert(pst);

	//pst->a = NULL;
	//pst->top = 0;
	//pst->capacity = 0;

	pst->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	pst->top = 0;
	pst->capacity = 4;
}

void StackDestroy(Stack* pst)
{
	assert(pst);
	free(pst->a);
	pst->a = NULL;
	pst->capacity = pst->top = 0;
}

// 性质就决定在栈顶出入数据
void StackPush(Stack* pst, STDataType x)
{
	assert(pst);
	if (pst->top == pst->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(pst->a, sizeof(STDataType) * pst->capacity * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1); // 结束整个程序
		}

		pst->a = tmp;
		pst->capacity *= 2;
	}

	pst->a[pst->top] = x;
	pst->top++;
}

void StackPop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));
	pst->top--;
}

STDataType StackTop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));

	return pst->a[pst->top - 1];
}

// 空返回1 非空返回0
//int StackEmpty(Stack* pst);
bool StackEmpty(Stack* pst)
{
	assert(pst);

	return pst->top == 0;
}

int StackSize(Stack* pst)
{
	assert(pst);

	return pst->top;
}

typedef struct {
	Stack pushST;
	Stack popST;
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
	StackInit(&q->pushST);
	StackInit(&q->popST);

	return q;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	StackPush(&obj->pushST, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	/*if(StackEmpty(&obj->popST))
	{
	while(!StackEmpty(&obj->pushST))
	{
	StackPush(&obj->popST, StackTop(&obj->pushST));
	StackPop(&obj->pushST);
	}
	}
	*/

	int top = myQueuePeek(obj);
	StackPop(&obj->popST);
	return top;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	if (StackEmpty(&obj->popST))
	{
		while (!StackEmpty(&obj->pushST))
		{
			StackPush(&obj->popST, StackTop(&obj->pushST));
			StackPop(&obj->pushST);
		}
	}

	return StackTop(&obj->popST);
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return StackEmpty(&obj->pushST) && StackEmpty(&obj->popST);
}

void myQueueFree(MyQueue* obj) {
	StackDestroy(&obj->pushST);
	StackDestroy(&obj->popST);
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