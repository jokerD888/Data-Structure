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
		int pass;	//�ڵ㱻ͨ���˶��ٴ�
		int endNode;	//�νڵ�Ϊ�յ�ĸ���
		//vector<TrieNode*>* nexts;
		TrieNode* nexts[26] = { nullptr };	//26��·��26����ĸ	
		//���������ϴ󣬿���map<char,Node*> nexts

		TrieNode() {
			pass = 0;
			endNode = 0;
			//nexts = new vector<TrieNode*>(26);
		}
		~TrieNode() {	//��д������������ֹ�ڴ�й¶
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
		for (int i = 0; i < word.size(); ++i) {	//�����ұ����ַ���
			index = word[i] - 'a';		//��ȡ��ĸӳ����±�
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
				delete	node->nexts[index];	//TrieNode���������Ѿ����˵ݹ�ɾ�����ڴ�ֱ��delete����
				node->nexts[index] = nullptr;	//�ǵ��ÿ� 
				return;
			}
			node = node->nexts[index];
		}
		node->endNode--;;

	}

	//����word�������֮ǰ���������
	int search(const string& word) {
		if (word.size() == 0) {
			return 0;
		}
		TrieNode* node = root;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {
			index = word[i] - 'a';
			if (node->nexts[index] == nullptr) {	//û�ӹ��˵���
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