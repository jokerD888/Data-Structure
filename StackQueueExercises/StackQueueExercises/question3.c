#define _CRT_SECURE_NO_WARNINGS 1

//��ջʵ�ֶ���
// 
//��һ��
//����ջ��s1�ٳ�����һ��ջs2���ٴ�s2��ջ���������ӳ��ӣ���������ӣ�s2��ջ��s1�У���s1����ջ

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
//typedef int STDataType;
////��̬
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
////��ջ��ջ
//void StackPush(ST* ps, STDataType x);
//void StackPop(ST* ps);
////ȡջ��Ԫ��
//STDataType StackTop(ST* ps);
////ջ�Ĵ�С
//int StackSize(ST* ps);
////�ж�ջ�Ƿ�Ϊ��
////int StackEmpty(ST* ps); //���ǿշ���1���շ���0��
////��
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
//	ps->top = 0;//topָ�����ջ��Ԫ�ص���һ��
//	//ps->top = -1;//topָ�����ջ��Ԫ��
//}
//void StackDestory(ST* ps)
//{
//	assert(ps);
//	free(ps->a);
//	ps->a = NULL;
//	ps->top = ps->capacity = 0;
//}
//
////��ջ��ջ
//void StackPush(ST* ps, STDataType x)
//{
//	assert(ps);
//
//	//����,����
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
//	//���ջ�գ���pop��ֱ�ӱ���
//	assert(ps->top > 0);
//	ps->top--;
//}
////ȡջ��Ԫ��
//STDataType StackTop(ST* ps)
//{
//	assert(ps);
//	//��ֹջ��
//	assert(ps->top > 0);
//
//	return ps->a[ps->top - 1];
//}
////ջ�Ĵ�С
//int StackSize(ST* ps)
//{
//	assert(ps);
//	return ps->top;
//}
////�ж�ջ�Ƿ�Ϊ��
////int StackEmpty(ST* ps); //���ǿշ���1���շ���0��
////��
//bool StackEmpty(ST* ps)
//{
//	assert(ps);
//	return ps->top == 0;//��Ϊ1,����true,��Ϊ0,����false
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
//		printf("�������Ԫ��\n");
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
//		printf("�������Ԫ��\n");
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



//��������������ջ��pushST��popST��  �����ݣ���pushST��   �����ݣ���popST����û�����ݣ���ֱ�ӳ���û�оͰ�pushST����ȫ������popST�У��ٳ�����
//�淶д��
typedef int STDataType;
struct Stack
{
	STDataType* a;
	int top;       // ջ��
	int capacity;  // ��������������
};

//typedef struct Stack ST;
typedef struct Stack Stack;

void StackInit(Stack* pst);
void StackDestroy(Stack* pst);

// ���ʾ;�����ջ����������
void StackPush(Stack* pst, STDataType x);
void StackPop(Stack* pst);
STDataType StackTop(Stack* pst);

// �շ���1 �ǿշ���0
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

// ���ʾ;�����ջ����������
void StackPush(Stack* pst, STDataType x)
{
	assert(pst);
	if (pst->top == pst->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(pst->a, sizeof(STDataType) * pst->capacity * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1); // ������������
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

// �շ���1 �ǿշ���0
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