#define _CRT_SECURE_NO_WARNINGS 1
#include"list.h"
//��ʼ����������
void InitSpare(SLinkList space)
{
	//��һά���������������һ����������SLL[0].curΪͷָ��
	int i = 0;
	for (i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
	}
	space[MAXSIZE - 1].cur = 0;
}

int MallocSL(SLinkList space)
{

	//�����ÿռ�����Ϊ�ǿգ��򷵻ط���Ľڵ��±꣬���򷵻�0��
	int i = 0;
	i = space[0].cur;
	if (space[0].cur)
	{
		space[0].cur = space[i].cur;
	}
	return i;
}


//�����н����յ���������
void FreeSL(SLinkList space, int k)
{
	//���±�Ϊk�Ŀ��н����յ���������(ͷ�壩
	space[k].cur = space[0].cur;
	space[0].cur = k;
}


void Print(SLinkList space)
{
	int cur = space[1].cur;
	while (cur)
	{

		printf("%c->", space[cur].data);
		cur = space[cur].cur;
	}
	printf("NULL\n");
}
