//297. �����������л��뷴���л�

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//�������--------------------------------------------------------------------------
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
        ss >> tmp;  //����string��ȡ�����ԣ���ȡ���ո������������Դ����
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
        istringstream ss(data);     //�����ڴ�IO����ݷ���Դ����
        return mydeserialize(ss);
    }
};

//DFS--------------------------------------------------------------------------
//ʱ��O��N��
//�ռ�O��N��   ջ�ռ�
class Codec {
public:
    //DFS������
    void rserialize(TreeNode* root, string& str) {
        if (!root) {
            str += "None,";
            return;
        }
        str += to_string(root->val) + ",";
        rserialize(root->left, str);
        rserialize(root->right, str);
    }

    string serialize(TreeNode* root) {      //���л�
        string ret;
        rserialize(root, ret);
        return ret;
    }

    //��������������ݣ�����DFS���¹��컹ԭ������
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

    TreeNode* deserialize(string data) {    //������
        list<string> dataArray;
        string tmp;
        for (auto v : data) {
            if (v == ',') {     //��Ϊ���л��ķ����У��ַ���һ������","��β�����һ��valueҲ����������
                dataArray.push_back(tmp);
                tmp.clear();
            } else {
                tmp.push_back(v);
            }
        }
        return rdeserialize(dataArray);
    }
};

//�ٽ�
class Codec {
public:
    //DFS������
    void rserialize(TreeNode* root, string& str) {
        if (root == nullptr) {
            str += "None,";
        } else {
            str += to_string(root->val) + ",";  
            rserialize(root->left, str);
            rserialize(root->right, str);
        }
    }

    string serialize(TreeNode* root) {      //���л�
        string ret;
        rserialize(root, ret);
        return ret;
    }

    //��������������ݣ�����DFS���¹��컹ԭ������
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

    TreeNode* deserialize(string data) {    //������
        list<string> dataArray;
        string str;
        //�Զ���Ϊ�ָ�������Դ���ݷ������
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


//���ű�ʾ����+ �ݹ��½�����--------------------------------------------
//�ٽ�


class Codec {
public:
    //�����������л������value(�����������л������
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
        //תΪ����
        while (isdigit(data[ptr])) {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }
    inline TreeNode* parseSubtree(const string& data, int& ptr) {
         ++ptr; // ����������
         auto subtree = parse(data, ptr);
         ++ptr; // ����������
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
    //�������л��Ķ���
    //T -> (T)num(T) | X
    //�� T ����һ�������л�֮��Ľ����| ��ʾ T �Ĺ���Ϊ (T) num (T) ���� X��| ����Ƕ� T �ĵݹ鶨�壬�ұ߹涨�˵ݹ���ֹ�ı߽�������
    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

//��
class Codec {
public:
    //�����������л������value(�����������л������
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
        //תΪ����
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
        cur->left = parse(data, ++ptr);     //������ȣ������˵ݹ���õĿ���
        ++ptr;
        cur->val = parseInt(data, ptr);
        cur->right = parse(data, ++ptr);
        ++ptr;
        return cur;
    }
    //�������л��Ķ���
    //T -> (T)num(T) | X
    //�� T ����һ�������л�֮��Ľ����| ��ʾ T �Ĺ���Ϊ (T) num (T) ���� X��| ����Ƕ� T �ĵݹ鶨�壬�ұ߹涨�˵ݹ���ֹ�ı߽�������
    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

