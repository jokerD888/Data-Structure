//#define _CRT_SECURE_NO_WARNINGS 1
//
//

#include<iostream>
using namespace std;
#include<stack>
#include<unordered_map>
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
////二叉树先序，中序，后序递归非递归实现
//struct TreeNode {
//	int value;
//	TreeNode* left;
//	TreeNode* right;
//};
//
////递归
//void preOrderRecur(TreeNode* head) {
//	if (head == nullptr) {
//		return;
//	}
//	cout << head->value << " ";
//	preOrderRecur(head->left);
//	preOrderRecur(head->right);
//}
//
//void inOrderRecur(TreeNode* head) {
//	if (head == nullptr) {
//		return;
//	}
//	inOrderRecur(head->left);
//	cout << head->value << " ";
//	inOrderRecur(head->right);
//}
//
//void posOrderRecur(TreeNode* head) {
//	if (head == nullptr) {
//		return;
//	}
//	posOrderRecur(head->left);
//	posOrderRecur(head->right);
//	cout << head->value << " ";
//
//}
//
//
////非递归
////栈直接模拟
//void preOrderUnRecur(TreeNode* head) {
//	cout << "pre-order:";
//	if (head != nullptr) {
//		stack<TreeNode*> st;
//		st.push(head);
//		while (!st.empty()) {
//			head = st.top();
//			st.pop();
//			cout << head->value << " ";
//			if (head->right) {
//				st.push(head->right);
//			}
//			if (head->left) {
//				st.push(head->left);
//			}
//		}
//	}
//	cout << endl;
//}
//
////1.每颗子树整棵树左边界进栈，依次弹出的过程中，打印，弹出节点,
////2、对弹出节点的右子树进行步骤1
//void inOrderUnRecur(TreeNode* head) {
//	cout << "pre-order:" ;
//	if (head) {
//		stack<TreeNode*> st;
//		while (!st.empty() || head) {
//			if (head) {
//				st.push(head);
//				head = head->left;
//			} else {
//				head = st.top();
//				st.pop();
//				cout << head->value << " ";
//				head = head->right;
//			}
//		}
//	}
//	cout << endl;
//}
//
//
////将s1中弹出的压入s2,根据栈的性质，最后在依次弹出s2，即为先序遍历的逆序，可得后序遍历
//void posOrderUnRecur(TreeNode* head) {
//	cout << "pos-order:";
//	if (head) {
//		stack<TreeNode*> st;
//		stack<TreeNode*> help;
//		st.push(head);
//		while (!st.empty()){
//			head = st.top();
//			st.pop();
//			help.push(head);
//			if (head->left) {
//				st.push(head->left);
//			}
//			if (head->right) {
//				st.push(head->right);
//			}
//		}
//		while (!help.empty()) {
//			cout << help.top()->value << " " ;
//			help.pop();
//		}
//	}
//	cout << endl;
//}
//
////树的宽度-----------------------------------
//#include<queue>
//#include<map>
////不算叶子节点------------------
////哈希
//class Solution {
//public:
//    int widthOfBinaryTree(TreeNode* root) {
//        if (!root)
//            return 0;
//
//        queue<TreeNode*> nodeQueue;
//        nodeQueue.push(root);
//        map<TreeNode*, int> levelMap;
//        levelMap.emplace(root, 1);
//        int curLevel = 1;   //当前层数
//        int curLevelNodes = 0;  //当前层数节点
//        int cntMax = INT_MIN;   //数宽最大值
//        while (!nodeQueue.empty()) {
//            TreeNode* cur = nodeQueue.front();
//            nodeQueue.pop();
//            int curNodeLevel = levelMap[cur];
//            if (curNodeLevel == curLevel) {
//                curLevelNodes++;
//            } else {
//                cntMax = max(cntMax,curLevelNodes);
//                curLevel++;
//                curLevelNodes = 1;
//            }
//            if (cur->left) {
//                levelMap.emplace(cur->left, curNodeLevel + 1);
//                nodeQueue.push(cur->left);
//            }
//            if (cur->right) {
//                levelMap.emplace(cur->right, curNodeLevel + 1);
//                nodeQueue.push(cur->right);
//            }
//        }
//        cntMax= cntMax = max(cntMax, curLevelNodes);
//        return cntMax;
//    }
//};
////非哈希
//class Solution {
//public:
//    int widthOfBinaryTree(TreeNode* root) {
//        if (!root)
//            return 0;
//        queue<TreeNode*> nodeQueue;
//        nodeQueue.push(root);
//        TreeNode* nodeCurEnd = root;
//        TreeNode* nextEnd = nullptr;
//        int curLevelNode = 0, ans = 0;
//
//        while (!nodeQueue.empty()) {
//            TreeNode* cur = nodeQueue.front();
//            nodeQueue.pop();
//            curLevelNode++;
//            if (cur->left) {
//                nodeQueue.push(cur->left);
//                nextEnd = cur->left;
//            }
//            if (cur->right) {
//                nodeQueue.push(cur->right);
//                nextEnd = cur->right;
//            }
//            if (cur == nodeCurEnd) {
//                ans = max(ans, curLevelNode);
//                curLevelNode = 0;
//                nodeCurEnd = nextEnd;
//                nextEnd = nullptr;
//            }
//        }
//        return ans;
//
//    }
//};
//
//
////算叶子节点---------------------------
//class Solution {
//public:
//	int widthOfBinaryTree(TreeNode* root) {
//		queue<pair<TreeNode*, int>> nodeQueue;
//		nodeQueue.push(make_pair(root, 0));
//		int ans = 0;
//		while (!nodeQueue.empty()) {
//			int size = nodeQueue.size(), L = nodeQueue.front().second, R;
//			while (size--) {
//				TreeNode* node = nodeQueue.front().first;
//				R = nodeQueue.front().second;
//				nodeQueue.pop();
//				if (node->left) {
//					nodeQueue.push(make_pair(node->left, R * 2 - L * 2));
//				}
//				if (node->right) {
//					nodeQueue.push(make_pair(node->right, R * 2 + 1 - L * 2));
//				}
//			}
//			ans = max(ans, R - L + 1);
//		}
//		return ans;
//	}
//};
// 
// //dfs
// class Solution {
//public:
//    int ans;
//    map<int, int> left;
//    int widthOfBinaryTree(TreeNode* root) {
//        ans = 0;
//        dfs(root, 0, 0);
//        return ans;
//    }
//    void dfs(TreeNode* root, int depth, int pos) {
//        if (!root)
//            return;
//        if(left.find(depth)==left.end())
//            left[depth]= pos;
//        ans = max(ans, pos - left[depth] + 1);
//        dfs(root->left, depth + 1, 2 * pos);
//        dfs(root->right, depth + 1, 2 * pos + 1);
//    }
//};
//
//
//
// //判断搜索二叉树---------------------------------------------------
// //98. 验证二叉搜索树
// //中序遍历，验证是否是升序即可
// struct TreeNode {
//	 int val;
//	 TreeNode* left;
//	 TreeNode* right;
//	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	 TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}	 
// };
//class Solution {
//public:
//	long long preValue = LONG_MIN;
//	bool isValidBST(TreeNode* root) {
//		if (!root) {
//			return true;
//		}
//		bool isLeftBst = isValidBST(root->left);
//		if (!isLeftBst) {
//			return false;
//		}
//		if (root->val <= preValue) {
//			return false;
//		} else {
//			preValue = root->val;
//		}
//		return isValidBST(root->right);
//	}
//};
////非递归
//class Solution {
//public:
//	bool isValidBST(TreeNode* root) {
//		stack<TreeNode*> st;
//		long long inorder = (long long)INT_MIN - 1;
//
//		while (!st.empty() || root != nullptr) {
//			while (root != nullptr) {
//				st.push(root);
//				root = root->left;
//			}
//			root = st.top();
//			st.pop();
//			// 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
//			if (root->val <= inorder) {
//				return false;
//			}
//			inorder = root->val;
//			root = root->right;
//		}
//		return true;
//	}
//};
//
////或者直接根据搜索二叉树的性质，通过递归不断调整左右子树数值区间
//class Solution {
//public:
//	bool helper(TreeNode* root, long long lower, long long upper) {
//		if (root == nullptr) {
//			return true;
//		}
//		if (root->val <= lower || root->val >= upper) {
//			return false;
//		}
//		//递归左子树，收缩上区间，递归右子树收缩下区间  
//		return helper(root->left, lower, root->val) && helper(root->right, root->val, upper);
//	}
//	bool isValidBST(TreeNode* root) {
//		return helper(root, LONG_MIN, LONG_MAX);
//	}
//};
//
//
//
////判断完全二叉树-------------------------------------
////根据完全二叉树的性质，可得两个构成完成二叉树的反条件，
////1)有右孩子但没有左孩子 
////2)遇到了不双全的节点之后，又发现当前节点居然有孩子
//class Solution {
//public:
//	bool isCBT(TreeNode* root) {
//		if (!root) {
//			return true;
//		}
//
//		queue<TreeNode*> nodeQueue;
//		bool leaf = false;
//		TreeNode* L = nullptr;
//		TreeNode* R = nullptr;
//		nodeQueue.push(root);
//		while (!nodeQueue.empty()) {
//			TreeNode* cur = nodeQueue.front();
//			nodeQueue.pop();
//			L = cur->left;
//			R = cur->right;
//			//如果遇到了不双全的节点之后，又发现当前节点居然有孩子  或  有右孩子但没有左孩子 --》直接返回false
//			if ((leaf && (L || R) || (!L && R))) {
//				return false;
//			}
//			if (L)
//				nodeQueue.push(L);
//			if (R)
//				nodeQueue.push(R);
//			if (!L || !R)
//				leaf = true;
//		}
//		return true;
//	}
//};
//
//
////判断平衡二叉树---------------------------------
////满足平衡二叉树的三个条件
////1)左子树是平衡二叉树 2）右子树是平衡二叉树 3）左右子树高度差不超过2
//class Solution {
//public:
//	
//	class Returntype {
//	public:
//		bool isBalanced;
//		int height;
//
//		Returntype(bool isB, int hei) :isBalanced(isB), height(hei)
//		{}
//	};
//
//	bool isBalanced(TreeNode* root) {
//		return process(root).isBalanced;
//	}
//
//	Returntype process(TreeNode* x) {
//		if (!x) {
//			return Returntype (true, 0);
//		}
//		Returntype leftData = process(x->left);
//		Returntype rightData = process(x->right);
//		int height = max(leftData.height, rightData.height) + 1;
//		bool isBalanced = leftData.isBalanced && rightData.isBalanced && abs(leftData.height - rightData.height) < 2;
//		return Returntype(isBalanced, height);
//
//	}
//};


//



//105. 从前序与中序遍历序列构造二叉树-----------------------------------------------------------
//在「递归」地遍历某个子树的过程中，我们也是将这颗子树看成一颗全新的树，按照上述的顺序进行遍历。
//挖掘「前序遍历」和「中序遍历」的性质，我们就可以得出本题的做法。
//对于任意一颗树而言，前序遍历的形式总是
//[根节点, [左子树的前序遍历结果], [右子树的前序遍历结果]]
//即根节点总是前序遍历中的第一个节点。而中序遍历的形式总是
//[[左子树的中序遍历结果], 根节点, [右子树的中序遍历结果]]
//递归

//class Solution {
//private:
//	unordered_map<int, int> index;
//
//public:
//	TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
//		if (preorder_left > preorder_right) {
//			return nullptr;
//		}
//
//		// 前序遍历中的第一个节点就是根节点
//		int preorder_root = preorder_left;
//		// 在中序遍历中定位根节点
//		int inorder_root = index[preorder[preorder_root]];
//
//		// 先把根节点建立出来
//		TreeNode* root = new TreeNode(preorder[preorder_root]);
//		// 得到左子树中的节点数目
//		int size_left_subtree = inorder_root - inorder_left;
//		// 递归地构造左子树，并连接到根节点
//		// 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
//		root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
//		// 递归地构造右子树，并连接到根节点
//		// 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
//		root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
//		return root;
//	}
//
//	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//		int n = preorder.size();
//		// 构造哈希映射，帮助我们快速定位根节点
//		for (int i = 0; i < n; ++i) {
//			index[inorder[i]] = i;
//		}
//		return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
//	}
//};
////非递归
//class Solution {
//public:
//	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//		if (!preorder.size()) {
//			return nullptr;
//		}
//		TreeNode* root = new TreeNode(preorder[0]);
//		stack<TreeNode*> stk;		//维护「当前节点的所有还没有考虑过右儿子的祖先节点」
//		stk.push(root);
//		int inorderIndex = 0;	//指向中序遍历的某个位置,对应的节点是「当前节点不断往左走达到的最终节点」
//		for (int i = 1; i < preorder.size(); ++i) {
//			int preorderVal = preorder[i];
//			TreeNode* node = stk.top();
//			if (node->val != inorder[inorderIndex]) {	//栈顶元素不等于inorderIndex所指节点的话，将当前节点进栈
//				node->left = new TreeNode(preorderVal);		//将当前节点作为栈顶节点的左孩子
//				stk.push(node->left);
//			} else {	//相等的话，不断的出栈，inorderIndex++,直到两者不相等
//				while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {	
//					node = stk.top();
//					stk.pop();
//					++inorderIndex;
//				}
//				//将inorderIndex所指节点作为最后出栈的节点的右孩子
//				node->right = new TreeNode(preorderVal);
//				stk.push(node->right);
//			}
//		}
//		return root;
//	}
//};
//
//
////106. 从中序与后序遍历序列构造二叉树---------------------------------------------------------------------------
//class Solution {
//public:
//	unordered_map<int, int> index;
//
//	TreeNode* myBuildTree(vector<int>& postorder, vector<int>& inorder, int pos_L, int pos_R, int in_L, int in_R) {
//		if (pos_L > pos_R) {
//			return nullptr;
//		}
//
//		//后序遍历的最后一个节点为根节点
//		int pos_root = postorder[pos_R];
//		//中序遍历中根节点位置
//		int in_root = index[pos_root];
//
//		//建节点
//		TreeNode* root = new TreeNode(pos_root);
//		//左子树节点个数
//		int size_L = in_root - in_L;
//		//递归左子树
//		root->left = myBuildTree(postorder, inorder, pos_L, pos_L + size_L - 1, in_L, in_L + size_L - 1);
//		//递归右子树
//		root->right = myBuildTree(postorder, inorder, pos_L + size_L, pos_R - 1, in_root + 1, in_R);
//
//		return root;
//	}
//
//	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//		int n = postorder.size();
//		//构造哈希映射，快速定位根节点
//		for (int i = 0; i < n; ++i) {
//			index[inorder[i]] = i;
//		}
//		return myBuildTree(postorder, inorder, 0, n - 1, 0, n - 1);
//	}
//};

//递归检查是否是搜索二叉树---------------------------------------
//int preValue = INT_MIN;
//bool checkBST(TreeNode* head) {
//	if (head == nullptr)
//		return true;
//	bool isLeftBST = checkBST(head->left);
//	if (!isLeftBST)
//		return false;
//	if (head->val <= preValue)
//		return false;
//	else {
//		preValue = head->val;
//	}
//	return checkBST(head->right);
//}


//递归套路检查搜索二叉树
//class ReturnData {
//public:
//	bool isBST;
//	int min;
//	int max;
//	ReturnData(bool is,int mi,int ma):isBST(is),min(mi),max(ma){}
//};
//
//ReturnData* process(TreeNode* x) {
//	if (x == nullptr)
//		return;
//	ReturnData* leftData = process(x->left);
//	ReturnData* rightData = process(x->right);
//	int mi=x->val;
//	int ma=x->val;
//	if (leftData) {
//		mi = min(mi, leftData->min);
//		//ma = max(ma, leftData->max);
//	}
//	if (rightData) {
//		// mi = min(mi, rightData->min);
//		ma = max(ma, rightData->max);
//	}
//	
//	bool isBST = true;
//	if (leftData && (!leftData->isBST || leftData->max >= x->val)) {
//		isBST = false;
//	}
//	if (rightData && (!rightData->isBST || rightData->min <= x->val)) {
//		isBST = false;
//	}
//
//	return  new ReturnData(isBST, mi, ma);
//}



//树形dp判断满二叉树------------------------------------------------------
//class Info {
//public:
//	int height;
//	int nodes;
//	Info(int h,int n):height(h),nodes(n){}
//};
//Info* f(TreeNode* root) {
//	if (root == nullptr) {
//		return new Info(0, 0);
//	}
//	Info* leftData = f(root->left);
//	Info* rightData = f(root->right);
//	int height = max(leftData->height, rightData->height) + 1;
//	int nodes = leftData->nodes + rightData->nodes + 1;
//	return new Info(height, nodes);
//}
//bool isFull(TreeNode* root) {
//	if (!root) {
//		return true;
//	}
//	Info* data = f(root);
//	return data->nodes == (1 << data->height) - 1;
//}



//给定两个二叉树的节点，找出它们的最低公共祖先节点  236.二叉树的最近公共祖先
//TreeNode* lowestCommonAncestor
//node1和node2一定属于head为头的树
//返回node1和node2的最低公共祖先
#include<map>
#include<set>
//解一：
//void process(TreeNode* root, map<TreeNode*, TreeNode*>& fatherMap) {
//	if (!root) {
//		return;
//	}
//	fatherMap[root->left] = root;
//	fatherMap[root->right] = root;
//	process(root->left, fatherMap);
//	process(root->right, fatherMap);
//
//}
//
//TreeNode* lca(TreeNode* root,TreeNode* node1,TreeNode* node2) {
//
//	map<TreeNode*, TreeNode*> fatherMap;
//	fatherMap[root] = root;
//	process(root, fatherMap);
//	set<TreeNode*> s;
//	TreeNode* cur = node1;
//	while (cur != fatherMap[cur]) {
//		s.insert(cur);
//		cur = fatherMap[cur];
//	}
//	s.insert(root);
//	cur = node2;
//	while (s.find(cur) == s.end()) {
//		cur = fatherMap[cur];
//	}
//	return *s.find(cur);
//}
//解二：

//公共族先，有两种情况
// 1）node1或node2即为公共祖先
// 2)node1和node2得向上找才有公共祖先
//如果一个子树上既没有node1又没有node2f返回nullptr
//TreeNode* lca(TreeNode* root, TreeNode* node1, TreeNode* node2) {
//	if (!root || root == node1 || root == node2) {
//		return root;
//	}
//	TreeNode* left = lca(root->left, node1, node2);
//	TreeNode* right = lca(root->right, node1, node2);
//	if (left && right) {	//如果是情况1）此条语句永远不会被执行，如果是情况2）执行到了此条语句，此时root即为公共祖先
//		return root;
//	}
//	//左右两棵树，并不都有返回值
//	return left != nullptr ? left : right;
//}


//求中序遍历中某一节点的后继节点--------------------------------------------------
//struct Node {
//	int val;
//	Node* left;
//	Node* right;
//	Node* parent;
//	Node() : val(0), left(nullptr), right(nullptr),parent(nullptr) {}
//	Node(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
//	Node(int x, Node* left, Node* right ,Node* pa) : val(x), left(left), right(right) ,parent(pa){}
//};
//Node* getLeftMost(Node* node) {
//	if (!node) {
//		return node;
//	}
//	while (node->left) {
//		node = node->left;
//	}
//	return node;
//}
//Node* getSuccessorNode(Node* node) {
//	if (!node) {
//		return node;
//	}
//	if (node->right) {	//node有右子树，其后续节点一定是其右子树最左边的节点
//		return getLeftMost(node->right);
//	} else {	//无右子树
//		Node* parent = node->parent;
//		while (parent && parent->left != node) {//当前节点是其父亲节点右孩子，
//			node = parent;						//若是parent为nullptr跳出循环，说明初始的node节点是整棵树最右的节点，后续节点即为空
//			parent = node->parent;				//或者当前节点属于某个节点左子树最右的节点时，当跳出循环，即找到了“某个节点”即为初始node节点的后续
//		}
//		return parent;
//	}
//}


//二叉树的序列化和反序列化-------------------------------------
//先序方式
#include<queue>
#include<string>
#include<sstream>
//序列化
string serialByPre(TreeNode* root) {
	if (!root) {
		return "#_";
	}
	string res = to_string(root->val) + "_";
	res += serialByPre(root->left);
	res += serialByPre(root->right);
	return res;
}
//反序列化
//字符串分割
vector<string> stringSplit(string str, const char split)
{
	istringstream iss(str);	// 输入流
	string token;			// 接收缓冲区
	vector<string> ans;
	while (getline(iss, token, split))	// 以split为分隔符
	{
		ans.push_back(token);
	}
	return ans;
}

TreeNode* reconPreOrder(queue<string>& Q) {
	string value = Q.front();
	Q.pop();
	if (value == "#") {
		return nullptr;
	}
	TreeNode* root = new TreeNode(stoi(value));
	root->left = reconPreOrder(Q);
	root->right = reconPreOrder(Q);
	return root;
	
}
//将_去掉将各节点入队
TreeNode* reconByPreString(string preStr) {
	vector<string> value = stringSplit(preStr, '-');
	queue<string> Q;
	for (int i = 0; i != value.size(); ++i) {
		Q.push(value[i]);
	}
	return reconPreOrder(Q);
}




//折纸条
//想象，整个过程为二叉树，每折一次，树深度加一，始终从上往下看，且每一次折叠产生的新折痕始终分布在上一次折痕的上下两侧，上侧为“凹”，下次为“凸”
//所有的左节点都为“凹”,右节点都为“凸”
void printProcess(int i, int N, bool down) {
	if (i > N) {
		return;
	}
	printProcess(i + 1, N, true);
	cout << (down ? "凹 " : "凸 ");
	printProcess(i + 1, N, false);
}
void printAllFolds(int N) {
	printProcess(1, N, true);
}





//int main(void)
//{
//
//	TreeNode* root = new TreeNode{ 0 };
//	TreeNode* real = root;
//	root->left = new TreeNode{ 1 };
//	root->right = new TreeNode{ 2 };
//
//	TreeNode* tmp = root->right;
//	root = root->left;
//	root->left = new TreeNode{ 3 };
//	root->right = new TreeNode{ 4 };
//
//	root = tmp;
//	root->left = new TreeNode{ 5 };
//	root->right = new TreeNode{ 6 };
//	root = real;
//	preOrderRecur(root);
//	cout << endl;
//	preOrderUnRecur(root);
//
//	inOrderRecur(root);
//	cout << endl;
//	inOrderUnRecur(root);
//
//	posOrderRecur(root);
//	cout << endl;
//	posOrderUnRecur(root);
//
//
//	return 0;
//}