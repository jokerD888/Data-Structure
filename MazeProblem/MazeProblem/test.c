#define _CRT_SECURE_NO_WARNINGS 1

//�Թ�����1
//���ӣ�https://www.nowcoder.com/questionTerminal/cf24906056f4488c9ddb132f317e03bc
//��Դ��ţ����
//�������� :
//���������������ֱ��ʾ��ά�������������������������Ӧ�����飬���е�1��ʾǽ�ڣ�0��ʾ�����ߵ�·�����ݱ�֤��Ψһ��, �������ж�����������Թ�ֻ��һ��ͨ����
//�������:
//���Ͻǵ����½ǵ����·������ʽ��������ʾ��
//ʾ��1
//����
//5 5
//0 1 0 0 0
//0 1 1 1 0
//0 0 0 0 0
//0 1 1 1 0
//0 0 0 1 0
//���
//(0, 0)
//(1, 0)
//(2, 0)
//(2, 1)
//(2, 2)
//(2, 3)
//(2, 4)
//(3, 4)
//(4, 4)
//


//#include<stdio.h>
//#include<assert.h>
//#include<stdlib.h>
//#include<stdbool.h>
//typedef struct Position
//{
//	int row;
//	int col;
//
//}PT;
///////////////////////////////////////////////////////////////////////////
//typedef PT STDataType;
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
//			ps->capacity *= 2;
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
//ST path;
///////////////////////////////////////////////////////////////////////////
//
//void PrintMaze(int** maze, int N, int M)
//{
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < M; j++)
//		{
//			printf("%d ", maze[i][j]);
//		}
//		printf("\n");
//		
//	}
//}
//void PrintPass(ST* ps)
//{
//	ST rPath;
//	StackInit(&rPath);
//	//ps���ݵ���rPath
//	while (!StackEmpty(ps))
//	{
//		StackPush(&rPath, StackTop(ps));
//		StackPop(ps);
//	}
//	while (!StackEmpty(&rPath))
//	{
//		PT top = StackTop(&rPath);
//		printf("(%d,%d)\n", top.row, top.col);
//		StackPop(&rPath);
//	}
//
//	StackDestory(&rPath);
//}
//bool isPass(int** maze, int N, int M, PT pos)
//{
//	if (pos.row >= 0 && pos.row < N &&
//		pos.col >= 0 && pos.col < M &&
//		maze[pos.row][pos.col] == 0)
//	{
//		return true;
//	}
//	else
//		return false;
//
//}
//
//bool GetMazePath(int** maze, int N, int M,PT cur)
//{
//	StackPush(&path, cur);
//
//	//����
//	if (cur.col == M - 1 && cur.row == N - 1)
//	{
//		return true;
//	}
//	//̽��curλ�õ��������ҷ���
//	PT next;
//	maze[cur.row][cur.col] = 2;//�߹���Ϊ2
//
//	//��
//	next = cur;
//	next.row -= 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//��
//	next = cur;
//	next.row += 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//��
//	next = cur;
//	next.col -= 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//��
//	next = cur;
//	next.col += 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	StackPop(&path);
//	return false;
//}
//int main(void)
//{
//	int N, M;
//	while (scanf("%d%d", &N, &M) != EOF)
//	{
//		int** maze = (int**)malloc(sizeof(int*) * N);
//		if (maze == NULL)
//		{
//			printf("malloc failed!\n");
//			exit(-1);
//		}
//		for (int i = 0; i < N; i++)
//		{
//			maze[i] = (int*)malloc(sizeof(int) * M);
//		}
//
//		//��ά���������
//		for (int i = 0; i < N; i++)
//		{
//			for (int j = 0; j < M; j++)
//			{
//				scanf("%d", &maze[i][j]);
//			}
//		}
//		//PrintMaze(maze, N, M);
//
//		StackInit(&path);
//
//		PT entry = { 0,0 };
//		if (GetMazePath(maze, N, M, entry))
//		{
//			PrintPass(&path);
//		}
//		else
//		{
//			printf("û��ͨ·!\n");
//		}
//
//		StackDestory(&path);
//
//		for (int i = 0; i < N; i++)
//		{
//			free(maze[i]);
//		}
//		free(maze);
//		maze = NULL;
//	}
//	return 0;
//}









//�Թ�����2�����·����
//���ӣ�https://www.nowcoder.com/questionTerminal/571cfbe764824f03b5c0bfd2eb0a8ddf
//��Դ��ţ����
//
//С������һ�첻С��������һ�������Թ�, С����ϣ�����Լ���ʣ������ֵP������������Թ���Ϊ���������,
//  ��������һ��n* m�ĸ����Թ�, �Թ�ÿ��λ��Ϊ0����1, 0�������λ�����ϰ���, С���ܴﵽ�������λ��; 1����С���ܿ��Դﵽ��λ�á�
// С���ܳ�ʼ��(0, 0)λ��, �����Թ��ĳ�����(0, m - 1)(��֤������λ�ö���1, ���ұ�֤һ������㵽�յ�ɴ��·��), 
// С�������Թ���ˮƽ�ƶ�һ����λ������Ҫ����1������ֵ, ������һ����λ������Ҫ����3����λ������ֵ, �����ƶ�����������ֵ, 
// ��С���ܵ�����ֵ����0��ʱ��û�е������, С���ܽ��޷������Թ���������Ҫ�����С���ܼ�����ܷ��ý�ʣ������ֵ�����Թ�(���ﵽ(0, m - 1)λ��)��
//
//�������� :
//�������n + 1�� :
//	��һ��Ϊ��������n, m(3 <= m, n <= 10), P(1 <= P <= 100)
//	��������n�� :
//	ÿ��m��0����1, �Կո�ָ�
//
//
//	������� :
//����������Թ�, �����һ������������С��·��, �����ʽ��������ʾ; ������������Թ�, �����"Can not escape!"�� �������ݱ�֤��Ψһ
//ʾ��1
//����
//4 4 10 1 0 0 1 1 1 0 1 0 1 1 1 0 0 1 1
//���
//[0, 0], [1, 0], [1, 1], [2, 1], [2, 2], [2, 3], [1, 3], [0, 3]

#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct Position
{
	int row;
	int col;

}PT;
/////////////////////////////////////////////////////////////////////////
typedef PT STDataType;

typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;

void StackInit(ST* ps);
void StackDestory(ST* ps);

//��ջ��ջ
void StackPush(ST* ps, STDataType x);
void StackPop(ST* ps);
//ȡջ��Ԫ��
STDataType StackTop(ST* ps);
//ջ�Ĵ�С
int StackSize(ST* ps);
//�ж�ջ�Ƿ�Ϊ��
//int StackEmpty(ST* ps); //���ǿշ���1���շ���0��
//��
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
			ps->capacity *= 2;
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

void StackCopy(ST* source, ST* dest)
{
	dest->a = (STDataType*)malloc(sizeof(STDataType) * source->capacity);
	memcpy(dest->a, source->a, sizeof(STDataType) * source->top);
	dest->top = source->top;

	dest->capacity = source->capacity;

}

ST path;
ST minpath;
/////////////////////////////////////////////////////////////////////////

void PrintMaze(int** maze, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%d ", maze[i][j]);
		}
		printf("\n");
		
	}
}
void PrintPass(ST* ps)
{
	ST rPath;
	StackInit(&rPath);
	//path���ݵ���rPath
	while (!StackEmpty(ps))
	{
		StackPush(&rPath, StackTop(ps));
		StackPop(ps);
	}
	while (StackSize(&rPath)>1)
	{
		PT top = StackTop(&rPath);
		printf("[%d,%d],", top.row, top.col);
		StackPop(&rPath);
	}
	PT top = StackTop(&rPath);
	printf("[%d,%d]", top.row, top.col);
	StackPop(&rPath);

	StackDestory(&rPath);
}
bool isPass(int** maze, int N, int M, PT pos)
{
	if (pos.row >= 0 && pos.row < N &&
		pos.col >= 0 && pos.col < M &&
		maze[pos.row][pos.col] == 1)
	{
		return true;
	}
	else
		return false;

}

void GetMazePath(int** maze, int N, int M,PT cur,int P)
{
	StackPush(&path, cur);

	//����
	if (cur.col == M - 1 && cur.row ==0)
	{
		//�ҵ��˸��̵�·��
		if (P>=0 && StackEmpty(&minpath) || StackSize(&path) < StackSize(&minpath))
		{
			StackDestory(&minpath);
			StackCopy(&path, &minpath);
		}

	}
	//̽��curλ�õ��������ҷ���
	PT next;
	maze[cur.row][cur.col] = 2;//�߹���Ϊ2

	//��
	next = cur;
	next.row -= 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next, P - 3);
	}

	//��
	next = cur;
	next.row += 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next, P);
	}

	//��
	next = cur;
	next.col -= 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next,P-1);
	}

	//��
	next = cur;
	next.col += 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next,P-1);
	}


	maze[cur.row][cur.col] = 1;
	StackPop(&path);
}
int main(void)
{
	int N, M,P;
	while (scanf("%d%d%d", &N, &M, &P) != EOF)
	{
		int** maze = (int**)malloc(sizeof(int*) * N);
		if (maze == NULL)
		{
			printf("malloc failed!\n");
			exit(-1);
		}
		for (int i = 0; i < N; i++)
		{
			maze[i] = (int*)malloc(sizeof(int) * M);
		}

		//��ά���������
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				scanf("%d", &maze[i][j]);
			}
		}
		//PrintMaze(maze, N, M);

		StackInit(&path);
		StackInit(&minpath);


		PT entry = { 0,0 };
		GetMazePath(maze, N, M, entry, P);

		if (!StackEmpty(&minpath))
		{
			PrintPass(&minpath);
		}
		else
		{
			printf("Can not escape!\n");
		}

		StackDestory(&path);
		StackDestory(&minpath);


		for (int i = 0; i < N; i++)
		{
			free(maze[i]);
		}
		free(maze);
		maze = NULL;
	}
	return 0;
}
