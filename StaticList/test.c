//注：以下来自CSDN用户源Aron，仅借此程序调试理解学习静态链表

#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#define MAX 10
/*
集合n与集合m中共有的元素需要删除形成新的集合m
测试项：
6 4
c b e g f d
a b n f
*/
struct {
	char date;
	int cur;
}Space[MAX];
//连续的静态链表 
void Init() {
	for (int i = 0; i < MAX - 1; ++i) {
		Space[i].cur = i + 1;
	}
}
//初始化静态链表的空间，可以说这时的链表全部是备用链表 ,初始化很重要，是Assign...函数的实现前提。 
int AssignEmptyList() {
	int i;
	i = Space[0].cur;
	if (Space[0].cur) {
		Space[0].cur = Space[i].cur;
	}
	return i;
}
//备用链表空间的调取，一次一块空间 
void FreeLink(int k) {
	Space[k].cur = Space[0].cur;  //被删除的节点的游标指向原来头指针指向的位置， 
	Space[0].cur = k;  //被删除节点的位置赋给备用链表的头指针 
}
//收集不用的空间至备用链表,采用头插法，在备用链表的第一块空间之前插入，使用方便巧妙 
//以下测试用。 
int main()
{
	memset(Space, '0', sizeof(Space));
	int n, m;  //n、m为两个集合的成员总数，m先输入，n后输入 
	int S = 0, r; // S为静态链表的头指针，Space[0].cur为备用链表的头指针，指向第一块空余空间，
			   // r的作用为找到集合m的尾节点 
	Init();//初始化空间 
	S = AssignEmptyList();//得到静态链表的头指针，并且创建了头指针的头结点，也就是说，Space[1}.cur指向第一个节点 
	r = S;
	scanf("%d %d", &m, &n);
	getchar();//格式吸。哈哈哈 
	for (int j = 1, i; j <= m; j++) {
		i = AssignEmptyList();  //这里第一次循环的i指向静态链表得到的第一个节点，然后类推 
		scanf("%c", &Space[i].date); //给节点赋值 
		getchar();//格式吸。哈哈哈 
		Space[r].cur = i;//这一步感觉不需要，因为空链表利用过程中，就让头指针指向上一个空间的游标 ， 
						//因为这个游标是初始化状态自动连接的，也就是隐含的完成了头节点和第一节点的连接 
		r = i;//r每一次循环都指向静态链表占时的尾节点 
	}
	Space[r].cur = 0;//尾节点不需要指向任何
	//下半部分是将集合n合并到m的过程 
	char b;
	int p, k;
	for (int j = 1; j <= n; j++) {
		scanf("%c", &b);
		getchar();//格式吸。哈哈哈
		p = S;// p的作用是为了删除静态链表某一块后，好被备用链表收集
		k = Space[S].cur;//k的作用是为了从链表第一节点访问至尾节点的循环条件 
		while (k != Space[r].cur && Space[k].date != b) {     //第一个条件是从头至尾的循环满足m中没有n的元素，之后执行 if语句
													//第二个条件是数据元素的唯一性 
			p = k;    //p永远比k值指向的空间节点低一点 
			k = Space[k].cur;  //递归循环查找 
		}
		if (k == Space[r].cur) {  //如果n中的其中一个元素不在m中，就执行if，也就是说 k=0 就和r指向的尾节点的游标相等 
			int i;
			i = AssignEmptyList(); //获得一个空间 
			Space[i].date = b;   //空间赋值 
			Space[i].cur = Space[r].cur;  // 将尾节点的游标也就是0，赋给占时的尾节点i 
			Space[r].cur = i;  // 原来尾节点的游标指向新的尾节点的地址 
			r = i;  //这个是谭女士没有的 
		}
		else {      //如果不满足条件 
			Space[p].cur = Space[k].cur;  // 将删除的该节点的游标赋给该节点的上一节点的游标 ，这是为了让静态链表连接好 
			FreeLink(k);
			if (r == k)r = p;  //若删除的是r所指的节点，需要修改尾指针 
		}
		/*for(int i=0;i<10;i++)
		{
			printf("%d %c %d\n",i,Space[i].date,Space[i].cur);
		}
		printf("\n尾指针是：%d\n",r);//单个测试第三行数据使用此条语句 */
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d %c %d\n", i, Space[i].date, Space[i].cur);
	}
	return 0;
}


