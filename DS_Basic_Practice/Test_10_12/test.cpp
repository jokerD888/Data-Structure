#define _CRT_SECURE_NO_WARNINGS 1

//树


//108. 将有序数组转换为二叉搜索树

#include<iostream>
using namespace std;
#include<vector>
#include<unordered_map>

//递归
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//二叉搜索树的中序遍历是升序序列，因数组有序递增要使之成为一高度平衡二叉树，
//则选择数组中间元素作为root,root的左边，右边又分别是严格递增，则可以递归进行
class Solution {
public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return helper(nums, 0, nums.size() - 1);
	}

	TreeNode* helper(vector<int>& nums, int left, int right) {
		if (left > right)
			return nullptr;

		int mid = left + ((right - left) >> 1); //避免了数据溢出

		TreeNode* root = new TreeNode(nums[mid]);
		root->left = helper(nums, left, mid - 1);
		root->right = helper(nums, mid + 1, right);
		return root;
	}


};


//105. 从前序与中序遍历序列构造二叉树


//法一：递归
class Solution {
private:
	unordered_map<int, int> index;

public:
	TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
		if (preorder_left > preorder_right) {
			return nullptr;
		}

		// 前序遍历中的第一个节点就是根节点
		int preorder_root = preorder_left;
		// 在中序遍历中定位根节点
		int inorder_root = index[preorder[preorder_root]];

		// 先把根节点建立出来
		TreeNode* root = new TreeNode(preorder[preorder_root]);
		// 得到左子树中的节点数目
		int size_left_subtree = inorder_root - inorder_left;
		// 递归地构造左子树，并连接到根节点
		// 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
		root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
		// 递归地构造右子树，并连接到根节点
		// 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
		root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int n = preorder.size();
		// 构造哈希映射，帮助我们快速定位根节点
		for (int i = 0; i < n; ++i) {
			index[inorder[i]] = i;
		}
		return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
	}
};

//法二：迭代
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


//103. 二叉树的锯齿形层序遍历
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

        //队列实习树的层次遍历
        while (!nodeQueue.empty()) {
            deque<int> levelList;
            int size = nodeQueue.size();
            //遍历当前层
            for (int i = 0; i < size; ++i) {
                auto node = nodeQueue.front();
                nodeQueue.pop();
                //从左往右的话就尾插，否则头插
                if (isOrderLeft) {
                    levelList.push_back(node->val);
                } else {
                    levelList.push_front(node->val);
                }
                //将当前节点左右孩子节点入队
                if (node->left) {
                    nodeQueue.push(node->left);
                }
                if (node->right) {
                    nodeQueue.push(node->right);
                }
            }
            //插入答案数组
            ans.emplace_back(vector<int>{levelList.begin(), levelList.end()});
            isOrderLeft = !isOrderLeft;
        }

        return ans;
    }
};
//或
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

		//队列实习树的层次遍历
		while (!nodeQueue.empty()) {
			deque<int> levelList;
			int size = nodeQueue.size();
			//遍历当前层
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
