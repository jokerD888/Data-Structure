#define _CRT_SECURE_NO_WARNINGS 1
//#include<Stdio.h>
//#include<stdbool.h>
////��������ǰ�����
////���Ҫ��ȫ�ֱ���i,���뺯��preorderTraversalʱ��Ҫ��i��Ϊ0��������Ϊ0,i���ۼӣ���������Խ�硣���Ƽ��˷������������ӿ�һ����ã�
//// ���ܻ���ִ��󣬷����̰߳�ȫ������
//// 
// // Definition for a binary tree node.
//  struct TreeNode {
//      int val;
//      struct TreeNode *left;
//      struct TreeNode *right;
// };
//
//
//
// /**
//  * Note: The returned array must be malloced, assume caller calls free().
//  */
//  int TreeSize(struct TreeNode* root)
//  {
//      return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//void _prevOrder(struct TreeNode* root, int* a, int* pi)
//{
//    if (root == NULL)
//    {
//        return;
//    }
//    a[*pi] = root->val;
//    (*pi)++;
//
//    _prevOrder(root->left,a,pi);
//    _prevOrder(root->right,a,pi);
//
//}
//int* preorderTraversal(struct TreeNode* root, int* returnSize) 
//{
//    int size = TreeSize(root);
//    int* a = (int*)malloc(sizeof(int)*size);
//    int i = 0;
//    _prevOrder(root, a, &i);
//
//    *returnSize = size;
//
//    return a;
//}
////��������������
//int TreeSize(struct TreeNode* root)
//{
//    return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//void _InOrder(struct TreeNode* root, int* a, int* pi)
//{
//
//    if (root == NULL)
//    {
//        return;
//    }
//    _InOrder(root->left, a, pi);
//
//    a[*pi] = root->val;
//    (*pi)++;
//
//    _InOrder(root->right, a, pi);
//
//}
//int* inorderTraversal(struct TreeNode* root, int* returnSize)
//{
//    int size = TreeSize(root);
//    int* a = (int*)malloc(sizeof(int) * size);
//    int i = 0;
//    _InOrder(root, a, &i);
//
//    *returnSize = size;
//
//    return a;
//}
//
//
////����
//int TreeSize(struct TreeNode* root)
//{
//    return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//void _PostOrder(struct TreeNode* root, int* a, int* pi)
//{
//
//    if (root == NULL)
//    {
//        return;
//    }
//    _PostOrder(root->left, a, pi);
//    _PostOrder(root->right, a, pi);
//
//    a[*pi] = root->val;
//    (*pi)++;
//
//
//}
//int* postorderTraversal(struct TreeNode* root, int* returnSize) {
//    int size = TreeSize(root);
//    int* a = (int*)malloc(sizeof(int) * size);
//    int i = 0;
//    _PostOrder(root, a, &i);
//
//    *returnSize = size;
//
//    return a;
//}
//
//
////��������������
//int maxDepth(struct TreeNode* root) {
//     
//    if (root == NULL)
//        return 0;
//    int left = maxDepth(root->left);
//    int right = maxDepth(root->right);
//    return left>right ?left + 1 :right + 1;
//}
//
//
////ƽ�������
//int maxDepth(struct TreeNode* root) {
//
//    if (root == NULL)
//        return 0;
//    int left = maxDepth(root->left);
//    int right = maxDepth(root->right);
//    return left > right ? left + 1 : right + 1;
//}
//
//bool isBalanced(struct TreeNode* root) {
//    if (root == NULL)
//        return true;
//    int leftDepth = maxDepth(root->left);
//    int rightDepth = maxDepth(root->right);
//    //if (leftDepth - rightDepth<2 && leftDepth - rightDepth > -2)
//     //   return true;
//    return abs(leftDepth - rightDepth) < 2 && isBalanced(root->left) && isBalanced(root->right);
//}
//
////����һ����
//void DestoryTree(struct TreeNode* root)
//{
//    if (root == NULL)
//        return;
//    DestoryTree(root->left);
//    DestoryTree(root->right);
//    free(root);
//}


//�廪��ѧ��������꿼�и����ϻ���
//����������
//��һ�����򣬶����û������һ����������ַ��������ݴ��ַ�������һ������������ָ�뷽ʽ�洢���� 
//�������µ���������ַ����� ABC##DE#G##F### ���С�#����ʾ���ǿո񣬿ո��ַ����������������˶������Ժ��ٶԶ������������������������������
#include<stdio.h>
typedef struct TreeNode
{
	struct TreeNode* left;
	struct TreeNode* right;
	char val;
}TNode;

TNode* CreateTree(char* a, int* pi)
{
	if (a[*pi] == '#')
	{
		++(*pi);
		return NULL;
	}

	TNode* root = (TNode*)malloc(sizeof(TNode));
	if (root == NULL)
	{
		printf("malloc failed!\n");
		exit(-1);
	}
	root->val = a[*pi];
	++(*pi);

	root->left = CreateTree(a, pi);
	root->right = CreateTree(a, pi);

	return root;
}

void InOrder(TNode* root)
{
	if (root == NULL)
	{
		return;
	}
	InOrder(root->left);
	printf("%c ", root->val);
	InOrder(root->right);
}
int main(void)
{
	char str[100];
	scanf("%s", str);
	int i = 0;
	TNode* root = CreateTree(str, &i);
	InOrder(root);
	return 0;
}