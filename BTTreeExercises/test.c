#define _CRT_SECURE_NO_WARNINGS 1
//#include<Stdio.h>
//#include<stdbool.h>
////二叉树的前序遍历
////如果要用全局变量i,进入函数preorderTraversal时，要将i置为0，若不置为0,i会累加，出现数组越界。不推荐此方法，如果多个接口一起调用，
//// 可能会出现错误，发生线程安全的问题
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
////中序后序遍历类似
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
////后序
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
////二叉树的最大深度
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
////平衡二叉树
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
////销毁一棵树
//void DestoryTree(struct TreeNode* root)
//{
//    if (root == NULL)
//        return;
//    DestoryTree(root->left);
//    DestoryTree(root->right);
//    free(root);
//}


//清华大学计算机历年考研复试上机题
//二叉树遍历
//编一个程序，读入用户输入的一串先序遍历字符串，根据此字符串建立一个二叉树（以指针方式存储）。 
//例如如下的先序遍历字符串： ABC##DE#G##F### 其中“#”表示的是空格，空格字符代表空树。建立起此二叉树以后，再对二叉树进行中序遍历，输出遍历结果。
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