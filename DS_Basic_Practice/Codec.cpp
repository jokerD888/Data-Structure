//297. 二叉树的序列化与反序列化

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//先序遍历--------------------------------------------------------------------------
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "#";
        }
        return to_string(root->val) + ' ' + serialize(root->left) + ' ' + serialize(root->right);
    }

    TreeNode* mydeserialize(istringstream& ss) {
        string tmp;
        ss >> tmp;  //利用string读取的特性，读取到空格结束，来分离源数据
        if (tmp == "#") {
            return nullptr;
        }
        TreeNode* node = new TreeNode(stoi(tmp));
        node->left = mydeserialize(ss);
        node->right = mydeserialize(ss);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream ss(data);     //利用内存IO来快捷分离源数据
        return mydeserialize(ss);
    }
};

//DFS--------------------------------------------------------------------------
//时间O（N）
//空间O（N）   栈空间
class Codec {
public:
    //DFS遍历树
    void rserialize(TreeNode* root, string& str) {
        if (!root) {
            str += "None,";
            return;
        }
        str += to_string(root->val) + ",";
        rserialize(root->left, str);
        rserialize(root->right, str);
    }

    string serialize(TreeNode* root) {      //序列化
        string ret;
        rserialize(root, ret);
        return ret;
    }

    //借助分离出的数据，进行DFS重新构造还原二叉树
    TreeNode* rdeserialize(list<string>& dataArray) {
        if (dataArray.front() == "None") {
            dataArray.pop_front();
            return nullptr;
        }
        TreeNode* cur = new TreeNode(stoi(dataArray.front()));
        dataArray.pop_front();
        cur->left = rdeserialize(dataArray);
        cur->right = rdeserialize(dataArray);
        return cur;
    }

    TreeNode* deserialize(string data) {    //反序列
        list<string> dataArray;
        string tmp;
        for (auto v : data) {
            if (v == ',') {     //因为序列化的方法中，字符串一定是以","结尾，最后一个value也会分离出来的
                dataArray.push_back(tmp);
                tmp.clear();
            } else {
                tmp.push_back(v);
            }
        }
        return rdeserialize(dataArray);
    }
};

//官解
class Codec {
public:
    //DFS遍历树
    void rserialize(TreeNode* root, string& str) {
        if (root == nullptr) {
            str += "None,";
        } else {
            str += to_string(root->val) + ",";  
            rserialize(root->left, str);
            rserialize(root->right, str);
        }
    }

    string serialize(TreeNode* root) {      //序列化
        string ret;
        rserialize(root, ret);
        return ret;
    }

    //借助分离出的数据，进行DFS重新构造还原二叉树
    TreeNode* rdeserialize(list<string>& dataArray) {
        if (dataArray.front() == "None") {
            dataArray.erase(dataArray.begin());
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        root->left = rdeserialize(dataArray);
        root->right = rdeserialize(dataArray);
        return root;
    }

    TreeNode* deserialize(string data) {    //反序列
        list<string> dataArray;
        string str;
        //以逗号为分隔符，将源数据分离出来
        for (auto& ch : data) { 
            if (ch == ',') {
                dataArray.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        if (!str.empty()) {
            dataArray.push_back(str);
            str.clear();
        }
        return rdeserialize(dataArray);
    }
};


//括号表示编码+ 递归下降解码--------------------------------------------
//官解


class Codec {
public:
    //（左子树序列化结果）value(右子树反序列化结果）
    string serialize(TreeNode* root) {
        if (!root) {
            return "X";
        }
        auto left = "(" + serialize(root->left) + ")";
        auto right = "(" + serialize(root->right) + ")";
        return left + to_string(root->val) + right;
    }



    inline int parseInt(const string& data, int& ptr) {
        int x = 0, sgn = 1;
        if (!isdigit(data[ptr])) {
            sgn = -1;
            ++ptr;
        }
        //转为数字
        while (isdigit(data[ptr])) {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }
    inline TreeNode* parseSubtree(const string& data, int& ptr) {
         ++ptr; // 跳过左括号
         auto subtree = parse(data, ptr);
         ++ptr; // 跳过右括号
         return subtree;
     }
    TreeNode* parse(const string& data, int& ptr) {
        if (data[ptr] == 'X') {
            ++ptr;
            return nullptr;
        }
        auto cur = new TreeNode(0);
        cur->left = parseSubtree(data, ptr);
        cur->val = parseInt(data, ptr);
        cur->right = parseSubtree(data, ptr);
        return cur;
    }
    //根据序列化的定义
    //T -> (T)num(T) | X
    //用 T 代表一棵树序列化之后的结果，| 表示 T 的构成为 (T) num (T) 或者 X，| 左边是对 T 的递归定义，右边规定了递归终止的边界条件。
    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

//或
class Codec {
public:
    //（左子树序列化结果）value(右子树反序列化结果）
    string serialize(TreeNode* root) {
        if (!root) {
            return "X";
        }
        auto left = "(" + serialize(root->left) + ")";
        auto right = "(" + serialize(root->right) + ")";
        return left + to_string(root->val) + right;
    }



    inline int parseInt(const string& data, int& ptr) {
        int x = 0, sgn = 1;
        if (!isdigit(data[ptr])) {
            sgn = -1;
            ++ptr;
        }
        //转为数字
        while (isdigit(data[ptr])) {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }
    TreeNode* parse(const string& data, int& ptr) {
        if (data[ptr] == 'X') {
            ++ptr;
            return nullptr;
        }
        auto cur = new TreeNode(0);
        cur->left = parse(data, ++ptr);     //与上相比，减少了递归调用的开销
        ++ptr;
        cur->val = parseInt(data, ptr);
        cur->right = parse(data, ++ptr);
        ++ptr;
        return cur;
    }
    //根据序列化的定义
    //T -> (T)num(T) | X
    //用 T 代表一棵树序列化之后的结果，| 表示 T 的构成为 (T) num (T) 或者 X，| 左边是对 T 的递归定义，右边规定了递归终止的边界条件。
    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

