#define _CRT_SECURE_NO_WARNINGS 1

//��


//108. ����������ת��Ϊ����������

#include<iostream>
using namespace std;
#include<vector>
#include<unordered_map>

//�ݹ�
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//����������������������������У��������������Ҫʹ֮��Ϊһ�߶�ƽ���������
//��ѡ�������м�Ԫ����Ϊroot,root����ߣ��ұ��ֱַ����ϸ����������Եݹ����
class Solution {
public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return helper(nums, 0, nums.size() - 1);
	}

	TreeNode* helper(vector<int>& nums, int left, int right) {
		if (left > right)
			return nullptr;

		int mid = left + ((right - left) >> 1); //�������������

		TreeNode* root = new TreeNode(nums[mid]);
		root->left = helper(nums, left, mid - 1);
		root->right = helper(nums, mid + 1, right);
		return root;
	}


};


//105. ��ǰ��������������й��������


//��һ���ݹ�
class Solution {
private:
	unordered_map<int, int> index;

public:
	TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
		if (preorder_left > preorder_right) {
			return nullptr;
		}

		// ǰ������еĵ�һ���ڵ���Ǹ��ڵ�
		int preorder_root = preorder_left;
		// ����������ж�λ���ڵ�
		int inorder_root = index[preorder[preorder_root]];

		// �ȰѸ��ڵ㽨������
		TreeNode* root = new TreeNode(preorder[preorder_root]);
		// �õ��������еĽڵ���Ŀ
		int size_left_subtree = inorder_root - inorder_left;
		// �ݹ�ع����������������ӵ����ڵ�
		// ��������С��� ��߽�+1 ��ʼ�� size_left_subtree����Ԫ�ؾͶ�Ӧ����������С��� ��߽� ��ʼ�� ���ڵ㶨λ-1����Ԫ��
		root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
		// �ݹ�ع����������������ӵ����ڵ�
		// ��������С��� ��߽�+1+�������ڵ���Ŀ ��ʼ�� �ұ߽硹��Ԫ�ؾͶ�Ӧ����������С��� ���ڵ㶨λ+1 �� �ұ߽硹��Ԫ��
		root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int n = preorder.size();
		// �����ϣӳ�䣬�������ǿ��ٶ�λ���ڵ�
		for (int i = 0; i < n; ++i) {
			index[inorder[i]] = i;
		}
		return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
	}
};

//����������
#include<stack>
class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	
		if (!preorder.size()) {
			return nullptr;
		}

		TreeNode* root = new TreeNode(preorder[0]);
		stack<TreeNode*> stk;
		stk.push(root);
		int inorderIndex = 0;
		for (int i = 1; i < preorder.size(); ++i) {
			int preorderVal = preorder[i];
			TreeNode* node = stk.top();
			if (node->val != inorder[inorderIndex]) {
				node->left = new TreeNode(preorderVal);
				stk.push(node->left);
			} else {
				while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
					node = stk.top();
					stk.pop(); 
					++inorderIndex;
				}
				node->right = new TreeNode(preorderVal);
				stk.push(node->right);
			}
		}
		return root;
	}
};


//103. �������ľ���β������
#include<queue>
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) {
            return ans;
        }

        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        bool isOrderLeft = true;

        //����ʵϰ���Ĳ�α���
        while (!nodeQueue.empty()) {
            deque<int> levelList;
            int size = nodeQueue.size();
            //������ǰ��
            for (int i = 0; i < size; ++i) {
                auto node = nodeQueue.front();
                nodeQueue.pop();
                //�������ҵĻ���β�壬����ͷ��
                if (isOrderLeft) {
                    levelList.push_back(node->val);
                } else {
                    levelList.push_front(node->val);
                }
                //����ǰ�ڵ����Һ��ӽڵ����
                if (node->left) {
                    nodeQueue.push(node->left);
                }
                if (node->right) {
                    nodeQueue.push(node->right);
                }
            }
            //���������
            ans.emplace_back(vector<int>{levelList.begin(), levelList.end()});
            isOrderLeft = !isOrderLeft;
        }

        return ans;
    }
};
//��
class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> ans;
		if (!root) {
			return ans;
		}

		queue<TreeNode*> nodeQueue;
		nodeQueue.push(root);
		bool isOrderLeft = true;

		//����ʵϰ���Ĳ�α���
		while (!nodeQueue.empty()) {
			deque<int> levelList;
			int size = nodeQueue.size();
			//������ǰ��
			vector<int> res;
			for (int i = 0; i < size; ++i) {
				auto node = nodeQueue.front();
				nodeQueue.pop();
				res.push_back(node->val);
				if (node->left)
					nodeQueue.push(node->left);
				if (node->right)
					nodeQueue.push(node->right);
			}
			if (!isOrderLeft)
				reverse(res.begin(), res.end());

			isOrderLeft = !isOrderLeft;
			ans.push_back(res);
		}

		return ans;
	}
};
