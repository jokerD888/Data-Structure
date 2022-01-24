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
//���ο�����С�ıߣ������ϵ�ʱ���Ƿ�ɻ��������ɻ����ϣ����ɻ������ӣ�������һ����
//���ڳɻ����жϣ�ʹ�ò��鼯���жϣ��ӱߵ�ʱ�򣬿��Ǳߵ������ϵ㣬�������ڵ㲻��ͬһ���ϣ���ϲ��󲻳ɻ�
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
// K�㷨�ǴӱߵĽǶȿ��ǣ�p�㷨�Ǵӵ�Ƕȳ���
//˼·�� ����ѡһ�㣬������صıߣ�����������ѡһ����С�ıߣ���ѡ������ѡ����С�ߵ���һ�ϵ㣬������رߣ� �������н����ı���ѡ��С��
// ��ѡ��С�ߵĹ����У����ߵ������˵��ѱ�ѡ�����������˱ߣ�����һ���ߣ����μ�����ֱ�����ȶ���Ϊ��
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
//˼·����һ����¼Դ�ڵ㵽�����ڵ�ľ��룬������û��ĳ���ڵ�ļ�¼��˵��Դ�ڵ㵽�˽��ľ���Ϊ�����ʼʱֻ��¼���Լ����Լ��ľ���0
//ѡ����С����ĵ㣬�����Ӵ˵�����ı��ܲ���ʹ��� Դ�㵽������þ����С�������ԣ����д���롣���ڵ�ı߱��������Ҳ���øõ��ˡ�
//���μ�����ֱ�����е㱻���������ɵó��𰸣�
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
	
	//�Ľ��������ֶ�������
	class NodeRecord {
	public:
		Node* node;
		int distance;
		NodeRecord(Node* node,int distance):node(node),distance(distance){}
	};

	class NodeHeap {
	public:
		NodeHeap(int cnt) {
			nodes = vector<Node*>(cnt);
			this->size = 0;
		}

		bool isEmpty() {
			return size == 0;
		}

		void addOrUpdateOrIgnore(Node* node, int distance) {
			if (inHeap(node)) {		//���ڶ��У�����Ч
				distanceMap[node] = min(distanceMap[node], distance);	//���¾���
				insertHeapify(node, heapIndexMap[node]);	//�����ѣ�����º��ֵֻ���С������������С�ѣ�����ֻ�������ϵ���
			}
			if (!isEntered(node)) {	//���ڶ���
				nodes[size] = node;		//β���ں���
				heapIndexMap[node] = size;	//��¼�±�λ��
				distanceMap[node] = distance;	//��¼����
				insertHeapify(node, size++);	//������
			}
		}
		

		NodeRecord* pop() {
			NodeRecord* nodeRecord = new NodeRecord(nodes[0], distanceMap[nodes[0]]);
			swapPos(0, --size );
			heapIndexMap[nodes[size]] = -1;	//��Ϊ-1����ʾ����̾�����ȷ��������ٿ���
			distanceMap.erase(nodes[size]);	//ȥ����ȷ���ľ���
			//delete(nodes[size]);	//�����ﲻ��delete��nodesָ�����Դgraph��Node�ڵ㣬�ͷź�ͼ�оͻ�ȱʧһ���ڵ�
			nodes[size] = nullptr;	//�ÿ�
			heapify(0, size);	//���µ�����
			return nodeRecord;
		}
	private:
		//�Ƿ��ڶ���
		bool isEntered(Node* node) {	
			return heapIndexMap.count(node);
		}

		//node�Ƿ��ڶ��У�����Ч���Ƿ���true
		bool inHeap(Node* node) {
			return isEntered(node) && heapIndexMap[node] != -1;
		}

		void swapPos(int index1, int index2) {
			heapIndexMap[nodes[index1]] = index2;
			heapIndexMap[nodes[index2]] = index1;
			swap(nodes[index1], nodes[index2]);
		}

		void insertHeapify(Node* node, int index) {
			//�ӱȸ���ҪС������λ��
			while (distanceMap[nodes[index]] < distanceMap[nodes[(index - 1) / 2]]) {
				swapPos(index, (index - 1) / 2);
				index = (index - 1) / 2;
			}
		}

		void heapify(int index, int size) {
			int left = index * 2 + 1;
			while (left < size) {
				int smallest = left + 1 < size && distanceMap[nodes[left + 1]] < distanceMap[nodes[left]]
					? left + 1 : left;
				smallest = distanceMap[nodes[smallest]] < distanceMap[nodes[index]] ? smallest : index;
				if (smallest == index) {
					break;
				}
				swapPos(smallest, index);
				index = smallest;
				left = index * 2 + 1;
			}

			
		}


		vector<Node*> nodes;
		map<Node*, int> heapIndexMap;	//Node*Ϊkey,Node*�ڶ��ϵ�λ��indexΪvalue
		map<Node*, int> distanceMap;	//Node*��Դ��ľ���
		int size;

	};

	map<Node*, int> dijkstra2(Node* head,int size) {
		NodeHeap nodeHeap(size);
		nodeHeap.addOrUpdateOrIgnore(head, 0);
		map<Node*, int> result;
		while (!nodeHeap.isEmpty()) {
			NodeRecord* record = nodeHeap.pop();
			Node* cur = record->node;
			int distance = record->distance;
			for (auto edge : cur->edges) {
				nodeHeap.addOrUpdateOrIgnore(edge->to, edge->weight + distance);
			}
			result[cur] = distance;
		}
		return result;

	}
};



//��˸�ϰ������
class HeapSort {
public:
	void heapSort1(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		for (int i = 0; i < arr.size(); ++i) {
			heapInsert(arr, i);
		}
		int heapSize = arr.size();
		//mySwap(arr, 0, --heapSize);
		swap(arr[0], arr[--heapSize]);	//���Ѷ�Ԫ�����β�������������������������--heapSize,��ʾ�������Ѿ��źã���С����Χ
		while (heapSize > 0) {	
			heapify(arr, 0, heapSize);	//�������µ�����,O(logN)
			swap(arr[0], arr[--heapSize]);	//ѡ�����
		}
	}
private:
	//ĳ������indexλ���ϣ����ϼ����ƶ�
	void heapInsert(vector<int>& arr, int index) {
		while(arr[index] > arr[(index - 1) / 2]) {
			swap(arr[index], arr[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}

	//ĳ������indexλ�ã��ܷ������ƶ�
	void heapify(vector<int>& arr, int index, int heapSize) {
		int left = index * 2 + 1;	
		while (left < heapSize) {
			//���������У�˭��ֵ�󣬰��±��largest
			int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;

			//���ͺ���֮�䣬˭��ֵ�󣬰��±��largest
			largest = arr[largest] > arr[index] ? largest : index;

			if (largest == index) {
				break;
			}
			swap(arr[largest], arr[index]);
			index = largest;
			left = index * 2 + 1;
		}
	}

public:
	void heapSort2(vector<int>& arr) {		//������һ�ֳ�����д����Ч����1ͬ����ֻ���ڵ�һ��forѭ���б�1�ٰ�ѭ��
		int n = arr.size();
		for (int i = n / 2 - 1; i >= 0; --i) {
			heapify(arr,i,n);
		}
		int end=n;
		while (end > 0) {
			swap(arr[0], arr[--end]);
			heapify(arr, 0,end);
		}
	}

};

void testHeapSort() {
	srand(time(0));
	cout << "test heapSort1:" << endl;
	vector<int> source1;
	for (int i = 0; i < 1000000; ++i) {
		source1.push_back(rand());
	}
	vector<int> source2 = source1;

	HeapSort h;

	int begin1 = clock();
	h.heapSort1(source1);
	int end1 = clock();
	cout << "heapSort1 time:" << end1 - begin1 << endl;
	//for (auto i : source1) {
	//	cout << i << ' ';
	//}
	cout << endl << "test heapSort2:" << endl;
	begin1 = clock();
	h.heapSort2(source2);
	end1 = clock();
	cout << "heapSort2 time:" << end1 - begin1 << endl;
	/*for (auto i : source2) {
		cout << i << ' ';
	}*/
}
int main(void)
{

	//ֱ�Ӵ�ͷ��β��ͼ���鷳
	/*
	Node* head = new Node(0);
	head->out += 2;
	head->nexts.push_back(new Node(1));
	head->nexts.push_back(new Node(2));
	head->edges.push_back(new Edge(1, head, head->nexts[0]));
	head->edges.push_back(new Edge(12, head, head->nexts[1]));

	Node* firstOne = head->nexts[0];
	firstOne->in +=1;
	firstOne->out += 2;
	firstOne->nexts.push_back(new Node(2));
	firstOne->nexts.push_back(new Node(3));
	firstOne->edges.push_back(new Edge(9, firstOne, firstOne->nexts[0]));
	firstOne->edges.push_back(new Edge(3, firstOne, firstOne->nexts[1]));

	Node* firstTwo = head->nexts[1];
	firstTwo->in +=3;
	firstTwo->out += 1;
	firstTwo->nexts.push_back(new Node(4));
	firstTwo->edges.push_back(new Edge(5, firstTwo, firstTwo->nexts[0]));

	Node* secondTwo = firstOne->nexts[1];
	secondTwo->in += 1;
	secondTwo->out += 3;
	secondTwo->nexts.push_back(new Node(2));
	secondTwo->nexts.push_back(new Node(4));
	secondTwo->nexts.push_back(new Node(5));
	secondTwo->edges.push_back(new Edge(4, secondTwo, secondTwo->nexts[0]));
	secondTwo->edges.push_back(new Edge(13, secondTwo, secondTwo->nexts[1]));
	secondTwo->edges.push_back(new Edge(15, secondTwo, secondTwo->nexts[1]));*/

	vector<vector<int>> graphInfo;
	graphInfo.push_back({ 0,1,1 });
	graphInfo.push_back({ 1,3,3 });
	graphInfo.push_back({ 3,15,5 });
	graphInfo.push_back({ 0,12,2 });
	graphInfo.push_back({ 2,5,4 });
	graphInfo.push_back({ 4,4,5 });
	graphInfo.push_back({ 1,9,2 });
	graphInfo.push_back({ 3,4,2 });
	graphInfo.push_back({ 3,13,4 });
	Graph* g= createGraph(graphInfo);
	//������ͼ��ͼ��ʾhttps://pics0.baidu.com/feed/14ce36d3d539b600a9e6969e35de7523c65cb703.jpeg?token=bf554ff0861c36f8327b7d75e6c9e670
	//����֮ͼ��ȷ
	cout << "testBFS:" << endl;
	graBFS(g->nodes[0]);	//���Խ����ȷ
	cout << endl;
	cout << "testDFS:" << endl;
	graDFS(g->nodes[0]);	//���Խ����ȷ
	cout << endl;

	cout << "test dijkstra1:" << endl;
	Dijkstra d;
	auto result=d.dijkstra1(g->nodes[0]);		//���Խ����ȷ
	for (auto res : result) {
		cout << res.first->value << "-->" << res.second << endl;
	}
	cout << "test dijkstra2:" << endl;
	result = d.dijkstra2(g->nodes[0],6);		//���Խ����ȷ
	for (auto res : result) {
		cout << res.first->value << "-->" << res.second << endl;
	}
	Node* cur = g->nodes[0];	//�鿴֪�����Ͽռ��ѱ��ͷ�
	delete(g);
	g = nullptr;

	//testHeapSort();
	
	return 0;
}
