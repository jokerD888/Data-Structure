//ע����������CSDN�û�ԴAron������˳���������ѧϰ��̬����

#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#define MAX 10
/*
����n�뼯��m�й��е�Ԫ����Ҫɾ���γ��µļ���m
�����
6 4
c b e g f d
a b n f
*/
struct {
	char date;
	int cur;
}Space[MAX];
//�����ľ�̬���� 
void Init() {
	for (int i = 0; i < MAX - 1; ++i) {
		Space[i].cur = i + 1;
	}
}
//��ʼ����̬����Ŀռ䣬����˵��ʱ������ȫ���Ǳ������� ,��ʼ������Ҫ����Assign...������ʵ��ǰ�ᡣ 
int AssignEmptyList() {
	int i;
	i = Space[0].cur;
	if (Space[0].cur) {
		Space[0].cur = Space[i].cur;
	}
	return i;
}
//��������ռ�ĵ�ȡ��һ��һ��ռ� 
void FreeLink(int k) {
	Space[k].cur = Space[0].cur;  //��ɾ���Ľڵ���α�ָ��ԭ��ͷָ��ָ���λ�ã� 
	Space[0].cur = k;  //��ɾ���ڵ��λ�ø������������ͷָ�� 
}
//�ռ����õĿռ�����������,����ͷ�巨���ڱ�������ĵ�һ��ռ�֮ǰ���룬ʹ�÷������� 
//���²����á� 
int main()
{
	memset(Space, '0', sizeof(Space));
	int n, m;  //n��mΪ�������ϵĳ�Ա������m�����룬n������ 
	int S = 0, r; // SΪ��̬�����ͷָ�룬Space[0].curΪ���������ͷָ�룬ָ���һ�����ռ䣬
			   // r������Ϊ�ҵ�����m��β�ڵ� 
	Init();//��ʼ���ռ� 
	S = AssignEmptyList();//�õ���̬�����ͷָ�룬���Ҵ�����ͷָ���ͷ��㣬Ҳ����˵��Space[1}.curָ���һ���ڵ� 
	r = S;
	scanf("%d %d", &m, &n);
	getchar();//��ʽ���������� 
	for (int j = 1, i; j <= m; j++) {
		i = AssignEmptyList();  //�����һ��ѭ����iָ��̬����õ��ĵ�һ���ڵ㣬Ȼ������ 
		scanf("%c", &Space[i].date); //���ڵ㸳ֵ 
		getchar();//��ʽ���������� 
		Space[r].cur = i;//��һ���о�����Ҫ����Ϊ���������ù����У�����ͷָ��ָ����һ���ռ���α� �� 
						//��Ϊ����α��ǳ�ʼ��״̬�Զ����ӵģ�Ҳ���������������ͷ�ڵ�͵�һ�ڵ������ 
		r = i;//rÿһ��ѭ����ָ��̬����ռʱ��β�ڵ� 
	}
	Space[r].cur = 0;//β�ڵ㲻��Ҫָ���κ�
	//�°벿���ǽ�����n�ϲ���m�Ĺ��� 
	char b;
	int p, k;
	for (int j = 1; j <= n; j++) {
		scanf("%c", &b);
		getchar();//��ʽ����������
		p = S;// p��������Ϊ��ɾ����̬����ĳһ��󣬺ñ����������ռ�
		k = Space[S].cur;//k��������Ϊ�˴������һ�ڵ������β�ڵ��ѭ������ 
		while (k != Space[r].cur && Space[k].date != b) {     //��һ�������Ǵ�ͷ��β��ѭ������m��û��n��Ԫ�أ�֮��ִ�� if���
													//�ڶ�������������Ԫ�ص�Ψһ�� 
			p = k;    //p��Զ��kֵָ��Ŀռ�ڵ��һ�� 
			k = Space[k].cur;  //�ݹ�ѭ������ 
		}
		if (k == Space[r].cur) {  //���n�е�����һ��Ԫ�ز���m�У���ִ��if��Ҳ����˵ k=0 �ͺ�rָ���β�ڵ���α���� 
			int i;
			i = AssignEmptyList(); //���һ���ռ� 
			Space[i].date = b;   //�ռ丳ֵ 
			Space[i].cur = Space[r].cur;  // ��β�ڵ���α�Ҳ����0������ռʱ��β�ڵ�i 
			Space[r].cur = i;  // ԭ��β�ڵ���α�ָ���µ�β�ڵ�ĵ�ַ 
			r = i;  //�����̷Ůʿû�е� 
		}
		else {      //������������� 
			Space[p].cur = Space[k].cur;  // ��ɾ���ĸýڵ���α긳���ýڵ����һ�ڵ���α� ������Ϊ���þ�̬�������Ӻ� 
			FreeLink(k);
			if (r == k)r = p;  //��ɾ������r��ָ�Ľڵ㣬��Ҫ�޸�βָ�� 
		}
		/*for(int i=0;i<10;i++)
		{
			printf("%d %c %d\n",i,Space[i].date,Space[i].cur);
		}
		printf("\nβָ���ǣ�%d\n",r);//�������Ե���������ʹ�ô������ */
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d %c %d\n", i, Space[i].date, Space[i].cur);
	}
	return 0;
}


