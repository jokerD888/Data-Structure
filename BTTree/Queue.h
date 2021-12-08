#define _CRT_SECURE_NO_WARNINGS 1
#pragma one
//队列，先进先出(头删）
//适宜用链表
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
struct BinaryTreeNode;
typedef struct BinaryTreeNode* QDataType;

typedef struct QueueNode
{
	struct QueueNode* next;
	QDataType data;
}QNode;


typedef struct Queue
{
	QNode* head;
	QNode* tail;
}Queue;

void QueueInit(Queue* pq); 
void QueueDestory(Queue* pq);
//入队
void QueuePush(Queue* pq, QDataType x);
//出队
void QueuePop(Queue* pq);
QDataType QueueFront(Queue* pq);
QDataType QueueBack(Queue* pq);
int QueueSize(Queue* pq);
bool QueueEmpty(Queue* pq);

