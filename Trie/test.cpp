#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<string>
class TrieTree {
public:
	class TrieNode
	{
	public:
		int pass;	//节点被通过了多少次
		int endNode;	//次节点为终点的个数
		//vector<TrieNode*>* nexts;
		TrieNode* nexts[26] = { nullptr };	//26条路，26个字母	
		//若数据量较大，可用map<char,Node*> nexts

		TrieNode() {
			pass = 0;
			endNode = 0;
			//nexts = new vector<TrieNode*>(26);
		}
		~TrieNode() {	//重写析构函数，防止内存泄露
			for (int i = 0; i < 26; ++i) {
				if (nexts[i] != nullptr) {
					delete nexts[i];
					nexts[i] = nullptr;
				}
			}

		}
	};


private:
	TrieNode* root;
public:
	TrieTree() {
		root = new TrieNode();
	}

	void insert(const string& word) {
		if (word.empty()) {
			return;
		}
		TrieNode* node = root;
		node->pass++;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {	//从左到右遍历字符串
			index = word[i] - 'a';		//获取字母映射的下标
			if (node->nexts[index] == nullptr) {
				node->nexts[index] = new TrieNode;
			}
			node = node->nexts[index];
			node->pass++;
		}
		node->endNode++;
	}

	void deleteWord(const string& word) {
		if (search(word) == 0) {
			return;
		}

		TrieNode* node = root;
		node->pass--;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {
			index = word[i] - 'a';
			if (--node->nexts[index]->pass == 0) {
				delete	node->nexts[index];	//TrieNode析构函数已经做了递归删除，在此直接delete即可
				node->nexts[index] = nullptr;	//记得置空 
				return;
			}
			node = node->nexts[index];
		}
		node->endNode--;;

	}

	//查找word这个单词之前加入过几次
	int search(const string& word) {
		if (word.size() == 0) {
			return 0;
		}
		TrieNode* node = root;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {
			index = word[i] - 'a';
			if (node->nexts[index] == nullptr) {	//没加过此单词
				return 0;
			}
			node = node->nexts[index];
		}
		return node->endNode;
	}

	int prefixNumber(string& pre) {
		if (pre.size() == 0) {
			return 0;
		}
		TrieNode* node = root;
		int index = 0;
		for (int i = 0; i < pre.size(); ++i) {
			index = pre[i] - 'a';
			if (node->nexts[index] == nullptr) {
				return 0;
			}
			node = node->nexts[index];
		}
		return node->pass;
	}

};

int main()
{
	TrieTree t;
	t.insert("abcd");
	t.insert("abcde");
	t.insert("ab");
	t.insert("abc");
	t.deleteWord("abcd");
	t.deleteWord("abcde");
	t.deleteWord("abc");




	return 0;
}