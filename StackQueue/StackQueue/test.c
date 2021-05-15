#define _CRT_SECURE_NO_WARNINGS 1

#include"stack.h"
#include"Queue.h"
//≤‚ ‘’ª

void TestStack(void)
{
	ST st;
	StackInit(&st);
	StackPush(&st, 1);
	StackPush(&st, 2);
	printf("%d ", StackTop(&st));
	StackPop(&st);
	StackPush(&st, 3);
	printf("%d ", StackTop(&st));
	StackPop(&st);
	StackPush(&st, 4);
	StackPush(&st, 5);

	while (!StackEmpty(&st))
	{
		printf("%d ", StackTop(&st));
		StackPop(&st);
	}
	printf("\n");


	StackDestory(&st);
}



//≤‚ ‘∂”¡–
void TestQueue()
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, 1);
	QueuePush(&q, 2);
	printf("%d ", QueueFront(&q));
	QueuePop(&q);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	printf("%d ", QueueFront(&q));
	QueuePop(&q);
	QueuePush(&q, 5);

	while (!QueueEmpty(&q))
	{
		printf("%d ", QueueFront(&q));
		QueuePop(&q);
	}

	QueueDestory(&q);
}
int main(void)
{

	//TestStack();
	TestQueue();
	return 0;
}