#define _CRT_SECURE_NO_WARNINGS 1
#include"list.h"

void difference(SLinkList space)
{
	int m, n,j;
	int i;
	int head,tail,prev,cur;
	InitSpare(space);
	head = MallocSL(space);
	tail = head;
	scanf("%d%d", &m, &n);
	getchar();
	for (j = 1; j <= m; j++)
	{
		i = MallocSL(space);
		scanf("%c", &(space[i].data));
		space[tail].cur = i;
		tail = i;
		getchar();
	}
	space[tail].cur = 0;
	for (j = 1; j <= n; j++)
	{
		char c;
		scanf("%c", &c);

		prev = head;
		cur = space[head].cur;
		while (cur != space[tail].cur && space[cur].data != c)
		{
			prev = cur;
			cur = space[cur].cur;
		}

		//无相同元素，插入tail所指结点之后
		if (cur == space[tail].cur)
		{
			i = MallocSL(space);
			space[i].data = c;
			space[i].cur = space[tail].cur;
			space[tail].cur = i;
		}
		else
		{
			//有相同元素，删除表中元素
			space[prev].cur = space[cur].cur;
			FreeSL(space, cur);
			if (tail == cur)
				tail = prev;//若删除的是r所指结点，则修改尾指针
		}
		getchar();

	}
}
int main(void)
{
	SLinkList space;
	difference(space);
	Print(space);
	return 0;
}