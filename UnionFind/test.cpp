#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<map>
#include<set>
#include<vector>
#include<stack>

template<class T>
class UnionFind {
public:
	class Node {
	public:
		T value;
		Node(T v) :value(v){}
	};


	class UnionSet {
	private:
		map<T, Node*> nodes;	//��T����Ϊ�ڵ�
		map<Node*, Node*> parents;	//valueΪkey���ϲ�ڵ�
		map<Node*, int> sizeSet;	//��¼���ϵ����ϲ�ڵ㣨����ڵ㣩��������Ԫ�ظ���

		

		Node* findFather(Node* cur) {
			stack<Node*> path;
			while (cur != parents[cur]) {
				path.push(cur);
				cur = parents[cur];
			}

			while (!path.empty()) {
				parents[path.top()] = cur;
				path.pop();
			}
			return cur;
		}
	public:
		UnionSet(multiset<T> values) {
			for (auto v : values) {
				Node* node = new Node(v);
				nodes.emplace(v, node);
				parents.emplace(node, node);	//��ʼ��ʱ���Լ�ָ���Լ�
				sizeSet.emplace(node, 1);

			}
		}
		~UnionSet() {
			for (auto &v : nodes) {
				delete v.second;
				v.second = nullptr;
			}
		}
		bool isSameSet(T a, T b) {
			if (!nodes.count(a) || !nodes.count(b)) {
				return false;
			}
			return findFather(nodes[a]) == findFather(nodes[b]);
		}

		void unionSet(T a, T b) {
			if (!nodes.count(a) || !nodes.count(b)) {
				return;
			}
			Node* aHead = findFather(nodes[a]);
			Node* bHead = findFather(nodes[b]);
			if (aHead != bHead) {
				int aSetSize = sizeSet[aHead];
				int bSetSize = sizeSet[bHead];
				auto big = aSetSize >= bSetSize ? aHead : bHead;
				auto small = big == aHead ? bHead : aHead;
				parents[small] = big;
				sizeSet[big] = aSetSize + bSetSize;
				sizeSet.erase(small);

			}
		}

	};


};

int main()
{
	multiset<int> res;
	res.insert(2);
	res.insert(3);
	res.insert(4);
	res.insert(5);
	res.insert(6);
	res.insert(7);
	res.insert(8);
	res.insert(1);

	UnionFind<int>::UnionSet s(res);
	cout << s.isSameSet(1, 2) << endl;
	s.unionSet(1, 2);
	cout << s.isSameSet(1, 2);
	


	
	
	
	
	return 0;
}