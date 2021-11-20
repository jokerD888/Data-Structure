#define _CRT_SECURE_NO_WARNINGS 1


//二叉树先序，中序，后序递归非递归实现
#include<iostream>
using namespace std;
#include<stack>

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
};

//递归
void preOrderRecur(TreeNode* head) {
	if (head == nullptr) {
		return;
	}
	cout << head->value << " ";
	preOrderRecur(head->left);
	preOrderRecur(head->right);
}

void inOrderRecur(TreeNode* head) {
	if (head == nullptr) {
		return;
	}
	inOrderRecur(head->left);
	cout << head->value << " ";
	inOrderRecur(head->right);
}

void posOrderRecur(TreeNode* head) {
	if (head == nullptr) {
		return;
	}
	posOrderRecur(head->left);
	posOrderRecur(head->right);
	cout << head->value << " ";

}


//非递归
//栈直接模拟
void preOrderUnRecur(TreeNode* head) {
	cout << "pre-order:";
	if (head != nullptr) {
		stack<TreeNode*> st;
		st.push(head);
		while (!st.empty()) {
			head = st.top();
			st.pop();
			cout << head->value << " ";
			if (head->right) {
				st.push(head->right);
			}
			if (head->left) {
				st.push(head->left);
			}
		}
	}
	cout << endl;
}

//1.每颗子树整棵树左边界进栈，依次弹出的过程中，打印，弹出节点,
//2、对弹出节点的右子树进行步骤1
void inOrderUnRecur(TreeNode* head) {
	cout << "pre-order:" ;
	if (head) {
		stack<TreeNode*> st;
		while (!st.empty() || head) {
			if (head) {
				st.push(head);
				head = head->left;
			} else {
				head = st.top();
				st.pop();
				cout << head->value << " ";
				head = head->right;
			}
		}
	}
	cout << endl;
}


//将s1中弹出的压入s2,根据栈的性质，最后在依次弹出s2，即为先序遍历的逆序，可得后序遍历
void posOrderUnRecur(TreeNode* head) {
	cout << "pos-order:";
	if (head) {
		stack<TreeNode*> st;
		stack<TreeNode*> help;
		st.push(head);
		while (!st.empty()){
			head = st.top();
			st.pop();
			help.push(head);
			if (head->left) {
				st.push(head->left);
			}
			if (head->right) {
				st.push(head->right);
			}
		}
		while (!help.empty()) {
			cout << help.top()->value << " " ;
			help.pop();
		}
	}
	cout << endl;
}


int main(void)
{

	TreeNode* root = new TreeNode{ 0 };
	TreeNode* real = root;
	root->left = new TreeNode{ 1 };
	root->right = new TreeNode{ 2 };

	TreeNode* tmp = root->right;
	root = root->left;
	root->left = new TreeNode{ 3 };
	root->right = new TreeNode{ 4 };

	root = tmp;
	root->left = new TreeNode{ 5 };
	root->right = new TreeNode{ 6 };
	root = real;
	preOrderRecur(root);
	cout << endl;
	preOrderUnRecur(root);

	inOrderRecur(root);
	cout << endl;
	inOrderUnRecur(root);

	posOrderRecur(root);
	cout << endl;
	posOrderUnRecur(root);


	return 0;
}