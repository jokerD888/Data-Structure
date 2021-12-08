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
////�������������򣬺���ݹ�ǵݹ�ʵ��
//struct TreeNode {
//	int value;
//	TreeNode* left;
//	TreeNode* right;
//};
//
////�ݹ�
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
////�ǵݹ�
////ջֱ��ģ��
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
////1.ÿ��������������߽��ջ�����ε����Ĺ����У���ӡ�������ڵ�,
////2���Ե����ڵ�����������в���1
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
////��s1�е�����ѹ��s2,����ջ�����ʣ���������ε���s2����Ϊ������������򣬿ɵú������
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
////���Ŀ��-----------------------------------
//#include<queue>
//#include<map>
////����Ҷ�ӽڵ�------------------
////��ϣ
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
//        int curLevel = 1;   //��ǰ����
//        int curLevelNodes = 0;  //��ǰ�����ڵ�
//        int cntMax = INT_MIN;   //�������ֵ
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
////�ǹ�ϣ
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
////��Ҷ�ӽڵ�---------------------------
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
// //�ж�����������---------------------------------------------------
// //98. ��֤����������
// //�����������֤�Ƿ������򼴿�
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
////�ǵݹ�
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
//			// �����������õ��Ľڵ��ֵС�ڵ���ǰһ�� inorder��˵�����Ƕ���������
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
////����ֱ�Ӹ������������������ʣ�ͨ���ݹ鲻�ϵ�������������ֵ����
//class Solution {
//public:
//	bool helper(TreeNode* root, long long lower, long long upper) {
//		if (root == nullptr) {
//			return true;
//		}
//		if (root->val <= lower || root->val >= upper) {
//			return false;
//		}
//		//�ݹ������������������䣬�ݹ�����������������  
//		return helper(root->left, lower, root->val) && helper(root->right, root->val, upper);
//	}
//	bool isValidBST(TreeNode* root) {
//		return helper(root, LONG_MIN, LONG_MAX);
//	}
//};
//
//
//
////�ж���ȫ������-------------------------------------
////������ȫ�����������ʣ��ɵ�����������ɶ������ķ�������
////1)���Һ��ӵ�û������ 
////2)�����˲�˫ȫ�Ľڵ�֮���ַ��ֵ�ǰ�ڵ��Ȼ�к���
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
//			//��������˲�˫ȫ�Ľڵ�֮���ַ��ֵ�ǰ�ڵ��Ȼ�к���  ��  ���Һ��ӵ�û������ --��ֱ�ӷ���false
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
////�ж�ƽ�������---------------------------------
////����ƽ�����������������
////1)��������ƽ������� 2����������ƽ������� 3�����������߶Ȳ����2
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



//105. ��ǰ��������������й��������-----------------------------------------------------------
//�ڡ��ݹ项�ر���ĳ�������Ĺ����У�����Ҳ�ǽ������������һ��ȫ�µ���������������˳����б�����
//�ھ�ǰ��������͡���������������ʣ����ǾͿ��Եó������������
//��������һ�������ԣ�ǰ���������ʽ����
//[���ڵ�, [��������ǰ��������], [��������ǰ��������]]
//�����ڵ�����ǰ������еĵ�һ���ڵ㡣�������������ʽ����
//[[������������������], ���ڵ�, [������������������]]
//�ݹ�

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
//		// ǰ������еĵ�һ���ڵ���Ǹ��ڵ�
//		int preorder_root = preorder_left;
//		// ����������ж�λ���ڵ�
//		int inorder_root = index[preorder[preorder_root]];
//
//		// �ȰѸ��ڵ㽨������
//		TreeNode* root = new TreeNode(preorder[preorder_root]);
//		// �õ��������еĽڵ���Ŀ
//		int size_left_subtree = inorder_root - inorder_left;
//		// �ݹ�ع����������������ӵ����ڵ�
//		// ��������С��� ��߽�+1 ��ʼ�� size_left_subtree����Ԫ�ؾͶ�Ӧ����������С��� ��߽� ��ʼ�� ���ڵ㶨λ-1����Ԫ��
//		root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
//		// �ݹ�ع����������������ӵ����ڵ�
//		// ��������С��� ��߽�+1+�������ڵ���Ŀ ��ʼ�� �ұ߽硹��Ԫ�ؾͶ�Ӧ����������С��� ���ڵ㶨λ+1 �� �ұ߽硹��Ԫ��
//		root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
//		return root;
//	}
//
//	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//		int n = preorder.size();
//		// �����ϣӳ�䣬�������ǿ��ٶ�λ���ڵ�
//		for (int i = 0; i < n; ++i) {
//			index[inorder[i]] = i;
//		}
//		return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
//	}
//};
////�ǵݹ�
//class Solution {
//public:
//	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//		if (!preorder.size()) {
//			return nullptr;
//		}
//		TreeNode* root = new TreeNode(preorder[0]);
//		stack<TreeNode*> stk;		//ά������ǰ�ڵ�����л�û�п��ǹ��Ҷ��ӵ����Ƚڵ㡹
//		stk.push(root);
//		int inorderIndex = 0;	//ָ�����������ĳ��λ��,��Ӧ�Ľڵ��ǡ���ǰ�ڵ㲻�������ߴﵽ�����սڵ㡹
//		for (int i = 1; i < preorder.size(); ++i) {
//			int preorderVal = preorder[i];
//			TreeNode* node = stk.top();
//			if (node->val != inorder[inorderIndex]) {	//ջ��Ԫ�ز�����inorderIndex��ָ�ڵ�Ļ�������ǰ�ڵ��ջ
//				node->left = new TreeNode(preorderVal);		//����ǰ�ڵ���Ϊջ���ڵ������
//				stk.push(node->left);
//			} else {	//��ȵĻ������ϵĳ�ջ��inorderIndex++,ֱ�����߲����
//				while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {	
//					node = stk.top();
//					stk.pop();
//					++inorderIndex;
//				}
//				//��inorderIndex��ָ�ڵ���Ϊ����ջ�Ľڵ���Һ���
//				node->right = new TreeNode(preorderVal);
//				stk.push(node->right);
//			}
//		}
//		return root;
//	}
//};
//
//
////106. �����������������й��������---------------------------------------------------------------------------
//class Solution {
//public:
//	unordered_map<int, int> index;
//
//	TreeNode* myBuildTree(vector<int>& postorder, vector<int>& inorder, int pos_L, int pos_R, int in_L, int in_R) {
//		if (pos_L > pos_R) {
//			return nullptr;
//		}
//
//		//������������һ���ڵ�Ϊ���ڵ�
//		int pos_root = postorder[pos_R];
//		//��������и��ڵ�λ��
//		int in_root = index[pos_root];
//
//		//���ڵ�
//		TreeNode* root = new TreeNode(pos_root);
//		//�������ڵ����
//		int size_L = in_root - in_L;
//		//�ݹ�������
//		root->left = myBuildTree(postorder, inorder, pos_L, pos_L + size_L - 1, in_L, in_L + size_L - 1);
//		//�ݹ�������
//		root->right = myBuildTree(postorder, inorder, pos_L + size_L, pos_R - 1, in_root + 1, in_R);
//
//		return root;
//	}
//
//	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//		int n = postorder.size();
//		//�����ϣӳ�䣬���ٶ�λ���ڵ�
//		for (int i = 0; i < n; ++i) {
//			index[inorder[i]] = i;
//		}
//		return myBuildTree(postorder, inorder, 0, n - 1, 0, n - 1);
//	}
//};

//�ݹ����Ƿ�������������---------------------------------------
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


//�ݹ���·�������������
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



//����dp�ж���������------------------------------------------------------
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



//���������������Ľڵ㣬�ҳ����ǵ���͹������Ƚڵ�  236.�������������������
//TreeNode* lowestCommonAncestor
//node1��node2һ������headΪͷ����
//����node1��node2����͹�������
#include<map>
#include<set>
//��һ��
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
//�����

//�������ȣ����������
// 1��node1��node2��Ϊ��������
// 2)node1��node2�������Ҳ��й�������
//���һ�������ϼ�û��node1��û��node2f����nullptr
//TreeNode* lca(TreeNode* root, TreeNode* node1, TreeNode* node2) {
//	if (!root || root == node1 || root == node2) {
//		return root;
//	}
//	TreeNode* left = lca(root->left, node1, node2);
//	TreeNode* right = lca(root->right, node1, node2);
//	if (left && right) {	//��������1�����������Զ���ᱻִ�У���������2��ִ�е��˴�����䣬��ʱroot��Ϊ��������
//		return root;
//	}
//	//�������������������з���ֵ
//	return left != nullptr ? left : right;
//}


//�����������ĳһ�ڵ�ĺ�̽ڵ�--------------------------------------------------
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
//	if (node->right) {	//node����������������ڵ�һ����������������ߵĽڵ�
//		return getLeftMost(node->right);
//	} else {	//��������
//		Node* parent = node->parent;
//		while (parent && parent->left != node) {//��ǰ�ڵ����丸�׽ڵ��Һ��ӣ�
//			node = parent;						//����parentΪnullptr����ѭ����˵����ʼ��node�ڵ������������ҵĽڵ㣬�����ڵ㼴Ϊ��
//			parent = node->parent;				//���ߵ�ǰ�ڵ�����ĳ���ڵ����������ҵĽڵ�ʱ��������ѭ�������ҵ��ˡ�ĳ���ڵ㡱��Ϊ��ʼnode�ڵ�ĺ���
//		}
//		return parent;
//	}
//}


//�����������л��ͷ����л�-------------------------------------
//����ʽ
#include<queue>
#include<string>
#include<sstream>
//���л�
string serialByPre(TreeNode* root) {
	if (!root) {
		return "#_";
	}
	string res = to_string(root->val) + "_";
	res += serialByPre(root->left);
	res += serialByPre(root->right);
	return res;
}
//�����л�
//�ַ����ָ�
vector<string> stringSplit(string str, const char split)
{
	istringstream iss(str);	// ������
	string token;			// ���ջ�����
	vector<string> ans;
	while (getline(iss, token, split))	// ��splitΪ�ָ���
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
//��_ȥ�������ڵ����
TreeNode* reconByPreString(string preStr) {
	vector<string> value = stringSplit(preStr, '-');
	queue<string> Q;
	for (int i = 0; i != value.size(); ++i) {
		Q.push(value[i]);
	}
	return reconPreOrder(Q);
}




//��ֽ��
//������������Ϊ��������ÿ��һ�Σ�����ȼ�һ��ʼ�մ������¿�����ÿһ���۵����������ۺ�ʼ�շֲ�����һ���ۺ۵��������࣬�ϲ�Ϊ���������´�Ϊ��͹��
//���е���ڵ㶼Ϊ������,�ҽڵ㶼Ϊ��͹��
void printProcess(int i, int N, bool down) {
	if (i > N) {
		return;
	}
	printProcess(i + 1, N, true);
	cout << (down ? "�� " : "͹ ");
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