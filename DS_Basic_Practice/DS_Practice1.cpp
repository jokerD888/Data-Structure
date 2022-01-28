//199. ������������ͼ
//#include<vector>
//#include<stack>
//#include<queue>
//#include<unordered_map>
//struct TreeNode {
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
//
////bfs
////�����ҳ�ÿ�������ұߵ�Ԫ��
////ͨ����¼��ǰ������ڵ�������ݼ�ֱ��Ϊ0�������ڶ������ҵ���һ�����ұߵĽڵ㣬Ч�������·��ٽ�
//class Solution {
//public:
//    vector<int> rightSideView(TreeNode* root) {
//        if (!root)
//            return{};
//        vector<int> ans;
//        queue<TreeNode*> nodeQueue;
//        nodeQueue.push(root);
//        size_t flag = 1;
//        while (!nodeQueue.empty()) {
//            TreeNode* cur = nodeQueue.front();
//            nodeQueue.pop();
//            flag--;
//        
//            if (cur->left)
//                nodeQueue.push(cur->left);
//            if (cur->right)
//                nodeQueue.push(cur->right);
//            if (flag == 0) {
//                ans.push_back(cur->val);
//                flag = nodeQueue.size();
//            }
//        }
//
//        return ans;
//    }
//};
//
////�ٽ�
//class Solution {
//public:
//    vector<int> rightSideView(TreeNode* root) {
//        unordered_map<int, int> rightmostValueAtDepth;
//        int max_depth = -1;
//
//        queue<TreeNode*> nodeQueue;
//        queue<int> depthQueue;
//        nodeQueue.push(root);
//        depthQueue.push(0);
//
//        while (!nodeQueue.empty()) {
//            TreeNode* node = nodeQueue.front(); nodeQueue.pop();
//            int depth = depthQueue.front(); depthQueue.pop();
//
//            if (node != NULL) {
//                // ά����������������
//                max_depth = max(max_depth, depth);
//
//                // ����ÿһ�����һ�����ʵ��Ľڵ��������Ҫ�Ĵ𰸣���˲��ϸ��¶�Ӧ��ȵ���Ϣ����
//                rightmostValueAtDepth[depth] = node->val;
//
//                nodeQueue.push(node->left);
//                nodeQueue.push(node->right);
//                depthQueue.push(depth + 1);
//                depthQueue.push(depth + 1);
//            }
//        }
//        vector<int> rightView;
//        for (int depth = 0; depth <= max_depth; ++depth) {
//            rightView.push_back(rightmostValueAtDepth[depth]);
//        }
//
//        return rightView;
//    }
//};
//
////dfs
////�����������У����������ȷ�������������ô����ÿһ����˵���������������ĵ�һ�����һ�������ұߵĽ�㡣
////���������޷�ֱ�ӵõ����ĸ߶ȣ����Զ���һ��stack��¼�ڵ�Ĳ���
//class Solution {
//public:
//    vector<int> rightSideView(TreeNode* root) {
//        
//        unordered_map<int, int> rightmostValueAtDepth;
//        int max_depth = -1;
//
//        stack<TreeNode*> nodeStack;
//        stack<int> depthStack;
//        nodeStack.push(root);
//        depthStack.push(0);
//
//        while (!nodeStack.empty()) {
//            TreeNode* node = nodeStack.top(); nodeStack.pop();
//            int depth = depthStack.top(); depthStack.pop();
//
//            if (node != NULL) {
//                // ά����������������
//                max_depth = max(max_depth, depth);
//
//                // ��������ڶ�Ӧ��ȵĽڵ����ǲŲ���
//                if (rightmostValueAtDepth.find(depth) == rightmostValueAtDepth.end()) {
//                    rightmostValueAtDepth[depth] = node->val;
//                }
//
//                nodeStack.push(node->left);
//                nodeStack.push(node->right);
//                depthStack.push(depth + 1);
//                depthStack.push(depth + 1);
//            }
//        }
//
//        vector<int> rightView;
//        for (int depth = 0; depth <= max_depth; ++depth) {
//            rightView.push_back(rightmostValueAtDepth[depth]);
//        }
//
//        return rightView;
//    }
//};



////319. ���ݿ���
////ģ��
////�������
//class Solution {
//public:
//    int bulbSwitch(int n) {
//        vector<bool> light(n+1,false);
//
//        for (int i = 1; i <= n+1; i++) {
//            for (int j = 0; j <= n+1; j += i)
//                light[j] = !light[j];
//        }
//
//        int ans = 0;
//        for (int i = 1; i < n + 1; i++) {
//            if (light[i])
//                ans++;
//        }
//
//        return ans;
//    }
//};
//
//
////��ѧ
////��i�����ݵķ�ת�����������������ӣ�����1��i���ĸ�����һ��ʼ��״̬����ģ�
////ֻ�з�ת�����βŻ������ģ�����ֻ�����Ӹ���Ϊ�����ĵ�����ŲŻ�����ֻ��ƽ������������Ϊ����������6=1*6,2*3�����ǵ��������ǳɶԳ��ֵģ�
////��4=1*4,2*2��ֻ��ƽ������ƽ�������ӻ�ֻ����1�Σ����������մ𰸵���n���ڣ�����n��1����ƽ����������ֻҪ����sqrt(n)����
////����sqrt�漰�����������㣬?Ϊ�˱�֤�����־������⣬���ǿ��Լ��� sqrt��n+0.5���������Ա�֤��������Ľ������ȡ���� 32 λ������Χ��һ����ȷ��
//class Solution {
//public:
//    int bulbSwitch(int n) {
//        return sqrt(n + 0.5);
//    }
//};
//
//
//
////113. ·���ܺ� II
//#include<queue>
// struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//    
//};
////
//////dfs 
////������ȱ����ͻ��ݣ����α�����ÿ��Ҷ�ӣ���Ҷ�Ӻ�Ƚ�����·���Ƿ����targetSum
// class Solution {
// public:
//     vector<vector<int>> ret;
//     vector<int> path;
//
//     void dfs(TreeNode* root, int targetSum) {
//         if (root == nullptr) {
//             return;
//         }
//         path.emplace_back(root->val);
//         targetSum -= root->val;
//         //������Ҷ�ӽڵ㣬���Ҿ���·��������ĿҪ��
//         if (root->left == nullptr && root->right == nullptr && targetSum == 0) {
//             //����·�����뵽������
//             ret.emplace_back(path);
//         }
//         dfs(root->left, targetSum);
//         dfs(root->right, targetSum);
//         path.pop_back();
//     }
//
//     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
//         dfs(root, targetSum);
//         return ret;
//     }
// };
//
// //bfs
// //����unordered_map parent��¼�ڵ��ϵ����Ϊkey,��Ϊvalue
// //����que_sum��¼ÿ���ڵ㼰��֮ǰ·���ϵĽڵ�value�ܺͣ�һ��������Ҷ�ӽڵ㣬�Ͷ�������ڵ�que_sum��Ŀ�������Ĵ�С�������жϲ���
// //�����Ǵ�β��ͷ���в��룬�����ڲ���ret֮ǰ�����tmp���з�ת
//#include<unordered_map>
// class Solution {
// public:
//     vector<vector<int>> ret;
//     unordered_map<TreeNode*, TreeNode*> parent;
//
//     void getPath(TreeNode* node) {
//         vector<int> tmp;
//         while (node != nullptr) {
//             tmp.emplace_back(node->val);
//             node = parent[node];
//         }
//         reverse(tmp.begin(), tmp.end());
//         ret.emplace_back(tmp);
//     }
//
//     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
//         if (root == nullptr) {
//             return ret;
//         }
//
//         queue<TreeNode*> que_node;
//         queue<int> que_sum;
//         que_node.emplace(root);
//         que_sum.emplace(0);
//
//         while (!que_node.empty()) {
//             TreeNode* node = que_node.front();
//             que_node.pop();
//             int rec = que_sum.front() + node->val;
//             que_sum.pop();
//
//             if (node->left == nullptr && node->right == nullptr) {
//                 if (rec == targetSum) {
//                     getPath(node);
//                 }
//             } else {
//                 if (node->left != nullptr) {
//                     parent[node->left] = node;
//                     que_node.emplace(node->left);
//                     que_sum.emplace(rec);
//                 }
//                 if (node->right != nullptr) {
//                     parent[node->right] = node;
//                     que_node.emplace(node->right);
//                     que_sum.emplace(rec);
//                 }
//             }
//         }
//         return ret;
//     }
// };


