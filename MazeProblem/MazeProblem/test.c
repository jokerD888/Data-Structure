#define _CRT_SECURE_NO_WARNINGS 1

//迷宫问题1
//链接：https://www.nowcoder.com/questionTerminal/cf24906056f4488c9ddb132f317e03bc
//来源：牛客网
//输入描述 :
//输入两个整数，分别表示二维数组的行数，列数。再输入相应的数组，其中的1表示墙壁，0表示可以走的路。数据保证有唯一解, 不考虑有多解的情况，即迷宫只有一条通道。
//输出描述:
//左上角到右下角的最短路径，格式如样例所示。
//示例1
//输入
//5 5
//0 1 0 0 0
//0 1 1 1 0
//0 0 0 0 0
//0 1 1 1 0
//0 0 0 1 0
//输出
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
//	//ps数据倒到rPath
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
//	//出口
//	if (cur.col == M - 1 && cur.row == N - 1)
//	{
//		return true;
//	}
//	//探测cur位置的上下左右方向
//	PT next;
//	maze[cur.row][cur.col] = 2;//走过置为2
//
//	//上
//	next = cur;
//	next.row -= 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//下
//	next = cur;
//	next.row += 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//左
//	next = cur;
//	next.col -= 1;
//	if (isPass(maze, N, M, next))
//	{
//		if (GetMazePath(maze, N, M, next))
//			return true;
//	}
//
//	//右
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
//		//二维数组的输入
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
//			printf("没有通路!\n");
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









//迷宫问题2（最短路径）
//链接：https://www.nowcoder.com/questionTerminal/571cfbe764824f03b5c0bfd2eb0a8ddf
//来源：牛客网
//
//小青蛙有一天不小心落入了一个地下迷宫, 小青蛙希望用自己仅剩的体力值P跳出这个地下迷宫。为了让问题简单,
//  假设这是一个n* m的格子迷宫, 迷宫每个位置为0或者1, 0代表这个位置有障碍物, 小青蛙达到不了这个位置; 1代表小青蛙可以达到的位置。
// 小青蛙初始在(0, 0)位置, 地下迷宫的出口在(0, m - 1)(保证这两个位置都是1, 并且保证一定有起点到终点可达的路径), 
// 小青蛙在迷宫中水平移动一个单位距离需要消耗1点体力值, 向上爬一个单位距离需要消耗3个单位的体力值, 向下移动不消耗体力值, 
// 当小青蛙的体力值等于0的时候还没有到达出口, 小青蛙将无法逃离迷宫。现在需要你帮助小青蛙计算出能否用仅剩的体力值跳出迷宫(即达到(0, m - 1)位置)。
//
//输入描述 :
//输入包括n + 1行 :
//	第一行为三个整数n, m(3 <= m, n <= 10), P(1 <= P <= 100)
//	接下来的n行 :
//	每行m个0或者1, 以空格分隔
//
//
//	输出描述 :
//如果能逃离迷宫, 则输出一行体力消耗最小的路径, 输出格式见样例所示; 如果不能逃离迷宫, 则输出"Can not escape!"。 测试数据保证答案唯一
//示例1
//输入
//4 4 10 1 0 0 1 1 1 0 1 0 1 1 1 0 0 1 1
//输出
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

//出栈入栈
void StackPush(ST* ps, STDataType x);
void StackPop(ST* ps);
//取栈顶元素
STDataType StackTop(ST* ps);
//栈的大小
int StackSize(ST* ps);
//判断栈是否为空
//int StackEmpty(ST* ps); //（非空返回1，空返回0）
//或
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
			ps->capacity *= 2;
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
	//path数据倒到rPath
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

	//出口
	if (cur.col == M - 1 && cur.row ==0)
	{
		//找到了更短的路径
		if (P>=0 && StackEmpty(&minpath) || StackSize(&path) < StackSize(&minpath))
		{
			StackDestory(&minpath);
			StackCopy(&path, &minpath);
		}

	}
	//探测cur位置的上下左右方向
	PT next;
	maze[cur.row][cur.col] = 2;//走过置为2

	//上
	next = cur;
	next.row -= 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next, P - 3);
	}

	//下
	next = cur;
	next.row += 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next, P);
	}

	//左
	next = cur;
	next.col -= 1;
	if (isPass(maze, N, M, next))
	{
		GetMazePath(maze, N, M, next,P-1);
	}

	//右
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

		//二维数组的输入
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
