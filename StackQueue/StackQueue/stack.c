#define _CRT_SECURE_NO_WARNINGS 1
//����ȳ�
//����������
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
	ps->top = 0;//topָ�����ջ��Ԫ�ص���һ��
	//ps->top = -1;//topָ�����ջ��Ԫ��
}
void StackDestory(ST* ps)
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}

//��ջ��ջ
void StackPush(ST* ps, STDataType x)
{
	assert(ps);

	//����,����
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
	//���ջ�գ���pop��ֱ�ӱ���
	assert(ps->top > 0);
	ps->top--;
}
//ȡջ��Ԫ��
STDataType StackTop(ST* ps)
{
	assert(ps);
	//��ֹջ��
	assert(ps->top > 0);

	return ps->a[ps->top - 1];
}
//ջ�Ĵ�С
int StackSize(ST* ps)
{
	assert(ps);
	return ps->top;
}
//�ж�ջ�Ƿ�Ϊ��
//int StackEmpty(ST* ps); //���ǿշ���1���շ���0��
//��
bool StackEmpty(ST* ps)
{
	assert(ps);
	return ps->top == 0;//��Ϊ1,����true,��Ϊ0,����false
}
