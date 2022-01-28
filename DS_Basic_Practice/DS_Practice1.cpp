//199. 二叉树的右视图
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
////依次找出每层中最右边的元素
////通过记录当前层的最大节点个数，递减直到为0，即可在队列中找到下一层最右边的节点，效率优于下方官解
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
////官解
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
//                // 维护二叉树的最大深度
//                max_depth = max(max_depth, depth);
//
//                // 由于每一层最后一个访问到的节点才是我们要的答案，因此不断更新对应深度的信息即可
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
////在搜索过程中，我们总是先访问右子树。那么对于每一层来说，我们在这层见到的第一个结点一定是最右边的结点。
////由于我们无法直接得到树的高度，所以多用一个stack记录节点的层数
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
//                // 维护二叉树的最大深度
//                max_depth = max(max_depth, depth);
//
//                // 如果不存在对应深度的节点我们才插入
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



////319. 灯泡开关
////模拟
////堆区溢出
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
////数学
////第i个灯泡的反转次数等于它所有因子（包括1和i）的个数，一开始的状态的灭的，
////只有反转奇数次才会变成亮的，所以只有因子个数为奇数的灯泡序号才会亮，只有平方数的因子数为奇数（比如6=1*6,2*3，它们的因子总是成对出现的，
////而4=1*4,2*2，只有平方数的平方根因子会只出现1次），所以最终答案等于n以内（包括n和1）的平方数数量，只要计算sqrt(n)即可
////由于sqrt涉及到浮动数运算，?为了保证不出现精度问题，我们可以计算 sqrt（n+0.5）这样可以保证计算出来的结果向下取整在 32 位整数范围内一定正确。
//class Solution {
//public:
//    int bulbSwitch(int n) {
//        return sqrt(n + 0.5);
//    }
//};
//
//
//
////113. 路径总和 II
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
////利用深度遍历和回溯，依次遍历到每个叶子，到叶子后比较所走路劲是否等于targetSum
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
//         //遍历到叶子节点，并且经过路径符合题目要求
//         if (root->left == nullptr && root->right == nullptr && targetSum == 0) {
//             //将此路径插入到答案数组
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
// //利用unordered_map parent记录节点关系，子为key,父为value
// //利用que_sum记录每个节点及其之前路径上的节点value总和，一但遍历到叶子节点，就对照想对于的que_sum于目标数量的大小，进行判断插入
// //由于是从尾到头进行插入，所以在插入ret之前还需对tmp进行翻转
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


