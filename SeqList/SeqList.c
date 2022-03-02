#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"


//初始化
void SeqListInit(SL* ps)
{
	/*ps->size = 0;
	ps->a = NULL;
	ps->capacity = 0;*/
	ps->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if (ps->a == NULL)
	{
		printf("申请内存失败\n");
		exit(-1);//强制退出
	}
	ps->size = 0;
	ps->capacity = 4;
	
}
//打印
void SeqListPrint(SL* ps)
{
	assert(ps);
	
	int i = 0;
	for (i = 0; i < ps->size; ++i)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}
void SeqListCheckCapacity(SL* ps)
{
	assert(ps);
	//如果满了需要增容
	if (ps->size >= ps->capacity)
	{
		ps->capacity *= 2;
		ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * ps->capacity);
		if (ps->a == NULL)
		{
			printf("扩容失败\n");
			exit(-1);
		}
	}
}


//尾插尾删  头插头删
void SeqListPushBack(SL* ps, SLDataType x)
{
	assert(ps);
	SeqListCheckCapacity(ps);

	ps->a[ps->size] = x;
	ps->size++;
}
void SeqListPopBack(SL* ps)
{
	assert(ps);
	//ps->a[ps->size - 1] = 0;//没什么意义
	ps->size--;

}
void SeqListPushFront(SL* ps, SLDataType x)
{
	assert(ps);
	SeqListCheckCapacity(ps);

	int end = ps->size - 1;
	while (end>=0)
	{
		ps->a[end + 1] = ps->a[end];
		--end;
	}

	ps->a[0] = x;
	ps->size++;
}
void SeqListPopFront(SL* ps)
{
	assert(ps);
	int start = 0;
	while (start < ps->size - 1)
	{
		ps->a[start] = ps->a[start + 1];
		++start;	
	}
	ps->size--;
}
//任意位置的插入和删除
//pos为要被删除的第几个元素
void SeqListInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	SeqListCheckCapacity(ps);
	
	int end = ps->size - 1;
	while (end >=pos-1)
	{
		ps->a[end + 1] = ps->a[end];
		--end;
	}

	ps->a[pos-1] = x;
	ps->size++;
	
}
void SeqListErase(SL* ps, int pos)
{
	assert(ps);
	int start = pos-1;
	while (start < ps->size - 1)
	{
		ps->a[start] = ps->a[start + 1];
		++start;
	}
	ps->size--;
}

void menu()
{
	printf("*****************************\n");
	printf("********0.退出****************\n");
	printf("***1.头插     2.头删**********\n");
	printf("***3.尾插     4.尾删**********\n");
	printf("***5.任意插   6.任意删*********\n");
	printf("***    7.打印显示     *********\n");
	printf("*****************************\n");

}
