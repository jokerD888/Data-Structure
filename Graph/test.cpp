#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
//��ͼ�ı�ʾ��ʽ���ָ������ֲ������½ṹ�洢���ɽ������ṹ��ͼת��Ϊ�Լ����õ�����
//�洢�ṹ----------------------------
class Edge {		//�ߵ���Ϣ��:Ȩ�أ����ȣ����
public:
	int weight;
	Node* from;
	Node* to;
	Edge(int w,Node* from,Node* to):weight(w),from(from),to(to){}
};
//һ���ڵ���Ϣ�У�ֵ�����ȣ��������һ���ڵ㣬ָ����һ���ڵ�ı�
class Node {		
public:
	int value;
	int in;
	int out;
	vector<Node*> nexts;
	vector<Edge*> edges;	//���ڡ��ҡ��ıߣ����Դ˽ڵ�Ϊ���ı�
	Node(int v) :value(v),in(0),out(0){}
};
//ͼ����Ϣ�У��㼯,nodes�ڵ��ź���ڵ���Ϣӳ�䣬����Ϣ��
class Graph {	
public:
	map<int, Node*> nodes;	//�㼯
	set<Edge*> edges;	//�߼�
	Graph() {}
};
//�洢�ṹ----------------------------

//N*3�ľ���[weight,from�ڵ��ϵ�ֵ��to�ڵ��ϵ�ֵ]
//���̣���������һ�������㣬�յ㣬Ȩ����Ϣ����ͼ�㼯���������յ���Ϣ�����������Node ���յ�Node��Ϣ ,new��Edge,
//		������յ������Ϣ���ƣ���new���ı߼��뵽�߼���
Graph* createGraph(vector<vector<int>> matrix) {
	Graph* graph = new Graph;	//��ͼ
	int len = matrix.size();
	for (int i = 0; i < len; ++i) {
		int weight = matrix[i][0];	//������ �ߵ�Ȩ�أ���㣬�յ�
		int from = matrix[i][1];
		int to = matrix[i][2];
		if (graph->nodes.find(from) != graph->nodes.end()) {	//map�����Ƿ���������Ϣ,�������
			graph->nodes[from] = new Node(from);
		}
		if (graph->nodes.find(to) != graph->nodes.end()) {	//map�����Ƿ����յ����Ϣ,�������
			graph->nodes[to] = new Node(to);
		}
		Node* fromNode = graph->nodes[from];			//�ҳ��ߵ����ڵ���յ�ڵ�
		Node* toNode = graph->nodes[to];
		Edge* newEdge = new Edge(weight, fromNode, toNode);	//�����
		fromNode->nexts.push_back(toNode);	//�����ڵ��next����յ�ڵ�
		fromNode->out++;		//����++��
		toNode->in++;		//�յ�ڵ����++
		fromNode->edges.push_back(newEdge);	//�������ӱ���Ϣ
		graph->edges.insert(newEdge);	//����Ϣ��ӵ��߼�
	}
	return graph;
}



//ͼ�Ŀ�����ȱ���----------------------------------------------
//���̣��������п�ȱ�����set�����б�ǣ���ֹ�����ɻ���ԭʼ�ڵ���ӣ�����ѭ�������в�Ϊ�գ���pop����ͷ�����д����Զ�ͷָ��ĵ���б���
//		��û��������е���ӣ�setͬ����¼
void graBFS(Node* node) {
	if (!node) {
		return;
	}
	queue<Node*> q;
	set<Node*> s;		//���⻷�α��������ݹ�
	q.push(node);		//�����ݷ�Χ�����������ֱ�ʾ��Ϊ�˸������ʹ������������
	s.insert(node);
	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();
		cout << cur->value << ' ';	//�Բ�ͬ�Ŀ�����ȱ���Ҫ��ɽ����滻
		for (auto next : cur->nexts) {		//��cur�ڵ�������յ�ڵ���б�������û��������е����
			if (!s.count(next))	{
				s.insert(next);	
				q.push(next);
			}
		}
	}

}



//ͼ�Ĺ�ȵ����ȱ���-------------------------------------------------------
//���̣�ջ��set,�ô�ͬ�ϣ���ȥѭ��ǰ�ȴ���ԭʼ�ڵ㣬ѭ���ڣ�������ǰ�ڵ�ָ��Ľڵ㣬�����нڵ�û����ջ������ǰ�ڵ�ʹ˽ڵ�һͬ��ջ
//		cur���룬next���룬����cur�ڵ㣬break;
void graDFS(Node* node) {
	if (!node) {
		return;
	}
	stack<Node*> st;
	set<Node*> se;		//���⻷�α��������ݹ�//�����ݷ�Χ�����������ֱ�ʾ��Ϊ�˸������ʹ������������
	st.push(node);
	se.insert(node);		
	cout << node->value << ' ';		//�Բ�ͬ��������ȱ���Ҫ��ɽ����滻 ����
	while (!st.empty()) {
		Node* cur = st.top();
		st.pop();
		for (auto next : cur->nexts) {
			if (!se.count(next)) {
				st.push(cur);		//�����ǰ�ڵ㻹��ָ�������յ㣬������������Ҫͨ���ص�cur�ڵ������·��������ȱ���
				st.push(next);
				se.insert(next);
				cout << node->value << ' ';		//�Բ�ͬ��������ȱ���Ҫ��ɽ����滻 ����
				break;
			}
		}
	}

}


//��������---------------------------------------------------------
//���̣�map��key��¼�ڵ㣬value��¼��ȣ�queue��¼���Ϊ0�ĵ�
//��ʼ���ҳ���һ�����Ϊ0�ĵ㣬�����˵�ָ����յ㣬���յ����--
//--���������Ϊ0��Ҳ����queue��
vector<Node*> sortedTopology(Graph* gra) {
	//key:ĳһ��node
	//value:ʣ������
	map<Node*, int> inMap;
	//������Ϊ0�ĵ㣬���
	queue<Node*> zeroInQueue;
	for (auto node : gra->nodes) {
		inMap[node.second] = node.second->in;
		if (node.second->in == 0) {
			zeroInQueue.push(node.second);
		}
	}

	//��������Ľ�������μ���result
	vector<Node*> result;
	while (!zeroInQueue.empty()) {
		Node* cur = zeroInQueue.front();
		zeroInQueue.pop();
		result.push_back(cur);
		for (auto next : cur->nexts) {
			inMap[next]--;	//����Ӱ��
			if (inMap[next] == 0) {
				zeroInQueue.push(next);
			}
		}
	}
	return result;
}


//��С������(����ͼ��
//K�㷨------------------------------------------------------
class Kruskal {
public:
	//���鼯����ṹ
	class MySets {
	public:
		map<Node*, vector<Node*>> setMap;
		MySets(){}
		//��ʼ������ÿ���ڵ����Ϊһ������
		MySets(vector<Node*> nodes) {
			for (auto cur : nodes) {
				vector<Node*> set;
				set.push_back(cur);
				setMap[cur] = set; 
			}
		}
		//�жϼ����Ƿ���ͬ
		bool isSameSet(Node* from, Node* to) {
			vector<Node*> fromSet = setMap[from];
			vector<Node*> toSet = setMap[to];
			return  fromSet == toSet;
		}
		//�ϲ�����  
		void unionSet(Node* from, Node* to) {
			vector<Node*> fromSet = setMap[from];
			vector<Node*> toSet = setMap[to];
			for (auto toNode : toSet) {
				fromSet.push_back(toNode);
				setMap[toNode] = fromSet;
			}
		}
	};
	class myCompair {
	public:
		bool operator()(Edge* a, Edge* b) {
			return a->weight < b->weight;
		}
	};

	vector<Edge*> kruskalMST(Graph* gra) {
		vector<Node*> tmp;
		for (auto node : gra->nodes) {
			tmp.push_back(node.second);
		}
		MySets unionFind(tmp);		//�Զ��岢�鼯
		priority_queue<Edge*,myCompair()> priorityQueue;	//���ȶ��У�ʹ�ð�Ȩ����������
		for (auto edge : gra->edges) {		//�������ȶ���
			priorityQueue.push(edge);	
		}
		vector<Edge*> result;
		while (!priorityQueue.empty()) {	
			Edge* edge = priorityQueue.top();	
			priorityQueue.pop();
			if (!unionFind.isSameSet(edge->from, edge->to)) {	//�����㲻��һ�����ϣ��ϲ�
				result.push_back(edge);
				unionFind.unionSet(edge->from, edge->to);
			}
		}
		return result;
	}
};


//Prim�㷨--------------------------------------------------------
//���̣����ȣ�ѡһ���ڵ㣬���ýڵ����������ı������ȶӣ�����ѭ����ȡ��Ȩ����С�ıߣ����toNode,����toNode�Ƿ��Ѵ���set��
//		�������ڣ���˵����µ㣬�˱�����result�߼����ٽ�toNode�����ı������ȶӣ�ѭ������
class Prim {
public:
	class myCompair {
	public:
		bool operator()(Edge* a, Edge* b) {
			return a->weight < b->weight;
		}
	};

	vector<Edge*> primMST(Graph* gra) {
		//�����ı߽���С����
		priority_queue<Edge,myCompair> priQueue;
		set<Node*> s;
		vector<Edge*> result;		//������ѡ�ı���result����
		for (auto node : gra->nodes) {		//�������һ���㣬����ɭ�ֵ������Ѱ����һ����С������
			//node��ʼ��
			if (!s.count(node.second)) {
				s.insert(node.second);
				for (auto edge : node.second->edges) {//��һ���㣬�������������ı�
					priQueue.push(edge);
				}

				while (!priQueue.empty()) {
					Edge* edge = priQueue.top();	//ȡ�������ı��У���С�ı�
					priQueue.pop();
					Node* toNode = edge->to;	//���ܵ�һ���µ�
					if (!s.count(toNode)) {		//�����е�ʱ������µ�
						s.insert(toNode);
						result.push_back(edge);
						for (auto nextEdge : toNode->edges) {	//��Ȼ�б߻ᱻ�ظ��������ȶ��У�����Ӧ�ĵ��ѱ�����set�У��ᱻ����
							priQueue.push(nextEdge);		//��Ӱ�����ս��������������ʱ�䣬�����һ���Ż����ɽ�һ���߼�set
						}
					}
				}
			}
		}
		return result;
	}
};



//Dijkstras��Դ���·���㷨
//���÷�Χ��������ȨֵΪ�����ıߣ��������ۼ�ֵΪ�����Ļ�

class Dijkstra {
public:
	map<Node*, int> dijkstra(Node* head) {
		//��head���������е����С����
		//key:��head��������key
		//value:��head��������key����С����
		//����ڱ��У�û��T�ļ�¼�������Ǵ�head��������T�����ľ���Ϊ������
		map<Node*, int> distanceMap;
		distanceMap.emplace(head, 0);
		//�Ѿ��������Ľڵ㣬����selectedNodes�У��Ժ���Ҳ����
		set<Node*> selectedNodes;	//��ѡ����Ľڵ�
		Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);	//�ҳ���С�߽ڵ�
		while (minNode) {
			int distance = distanceMap[minNode];	//�ҳ�Դ�ڵ㵽minNode�ľ���
			for (auto edge : minNode->edges) {		//����minNode�����ı�
				Node* toNode = edge->to;
				if (!distanceMap.count(toNode)) {		//���minNodeָ��ĵ�û�м�¼��distanceMap�У�˵��Դ�㵽�˵����Ϊ����
					distanceMap[toNode] = distance + edge->weight;	//������ؽڵ�
				} else {
					distanceMap[edge->to] = min(distanceMap[toNode], distance + edge->weight);	//�������·��
				}
			}
			selectedNodes.insert(minNode);	//������������ؽڵ��¼���˺�����
			minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);	//�ҳ���С�߽ڵ� 
		}

		return distanceMap;
	}

	Node* getMinDistanceAndUnselectedNode(map<Node*, int>& distanceMap, set<Node*> touchedNodes) {
		Node* minNode = nullptr;
		int minDistance = INT_MAX;
		for (auto entry : distanceMap) {
			Node* node = entry.first;
			int distance = entry.second;
			if (!touchedNodes.count(node) && distance < minDistance) {
				minNode = node;
				minDistance = distance; 
			}
		}
		return minNode;
	}
};
