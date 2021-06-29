#define _CRT_SECURE_NO_WARNINGS 1
//后进先出
//适宜用数组
#include"Stack.h"
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
			ps->capacity*=2;
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
