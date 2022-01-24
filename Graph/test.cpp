#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
//因图的表示方式各种各样，现采用以下结构存储，可将其他结构的图转化为自己常用的这种
//存储结构----------------------------
class Edge {		//边的信息有:权重，出度，入度
public:
	int weight;
	Node* from;
	Node* to;
	Edge(int w,Node* from,Node* to):weight(w),from(from),to(to){}
};
//一个节点信息有：值，出度，入读，下一个节点，指向下一个节点的边
class Node {		
public:
	int value;
	int in;
	int out;
	vector<Node*> nexts;
	vector<Edge*> edges;	//属于“我”的边，即以此节点为起点的边
	Node(int v) :value(v),in(0),out(0){}
};
//图的信息有：点集,nodes节点编号和其节点信息映射，边信息集
class Graph {	
public:
	map<int, Node*> nodes;	//点集
	set<Edge*> edges;	//边集
	Graph() {}
};
//存储结构----------------------------

//N*3的矩阵，[weight,from节点上的值，to节点上的值]
//流程：遍历矩阵，一次提出起点，终点，权重信息，向图点集中添加起点终点信息，提炼出起点Node 、终点Node信息 ,new边Edge,
//		对起点终点进行信息完善，将new出的边加入到边集中
Graph* createGraph(vector<vector<int>> matrix) {
	Graph* graph = new Graph;	//建图
	int len = matrix.size();
	for (int i = 0; i < len; ++i) {
		int weight = matrix[i][0];	//提炼出 边的权重，起点，终点
		int from = matrix[i][1];
		int to = matrix[i][2];
		if (graph->nodes.find(from) != graph->nodes.end()) {	//map中找是否有起点的信息,无则添加
			graph->nodes[from] = new Node(from);
		}
		if (graph->nodes.find(to) != graph->nodes.end()) {	//map中找是否有终点的信息,无则添加
			graph->nodes[to] = new Node(to);
		}
		Node* fromNode = graph->nodes[from];			//找出边的起点节点和终点节点
		Node* toNode = graph->nodes[to];
		Edge* newEdge = new Edge(weight, fromNode, toNode);	//构造边
		fromNode->nexts.push_back(toNode);	//给起点节点的next添加终点节点
		fromNode->out++;		//出度++；
		toNode->in++;		//终点节点入度++
		fromNode->edges.push_back(newEdge);	//给起点添加边信息
		graph->edges.insert(newEdge);	//边信息添加到边集
	}
	return graph;
}



//图的宽度优先遍历----------------------------------------------
//流程：借助队列宽度遍历，set来进行标记，防止遍历成环，原始节点入队，进行循环（队列不为空），pop出对头，进行处理，对队头指向的点进行遍历
//		将没入过队列中的入队，set同步记录
void graBFS(Node* node) {
	if (!node) {
		return;
	}
	queue<Node*> q;
	set<Node*> s;		//避免环形遍历，死递归
	q.push(node);		//当数据范围不大，且用数字表示，为了更快可以使用数组来查找
	s.insert(node);
	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();
		cout << cur->value << ' ';	//对不同的宽度优先遍历要求可进行替换
		for (auto next : cur->nexts) {		//对cur节点的所有终点节点进行遍历，将没入过队列中的入队
			if (!s.count(next))	{
				s.insert(next);	
				q.push(next);
			}
		}
	}

}



//图的广度的优先遍历-------------------------------------------------------
//流程：栈，set,用处同上，进去循环前先处理原始节点，循环内，遍历当前节点指向的节点，若还有节点没进过栈，将当前节点和此节点一同入栈
//		cur先入，next后入，处理cur节点，break;
void graDFS(Node* node) {
	if (!node) {
		return;
	}
	stack<Node*> st;
	set<Node*> se;		//避免环形遍历，死递归//当数据范围不大，且用数字表示，为了更快可以使用数组来查找
	st.push(node);
	se.insert(node);		
	cout << node->value << ' ';		//对不同的深度优先遍历要求可进行替换 处理
	while (!st.empty()) {
		Node* cur = st.top();
		st.pop();
		for (auto next : cur->nexts) {
			if (!se.count(next)) {
				st.push(cur);		//如果当前节点还有指向其他终点，后续还可能需要通过回到cur节点对其他路径进行深度遍历
				st.push(next);
				se.insert(next);
				cout << node->value << ' ';		//对不同的深度优先遍历要求可进行替换 处理
				break;
			}
		}
	}

}


//拓扑排序---------------------------------------------------------
//流程：map，key记录节点，value记录入度，queue记录入度为0的点
//开始先找出第一批入度为0的点，遍历此点指向的终点，将终点入度--
//--后，若是入度为0后也加入queue中
vector<Node*> sortedTopology(Graph* gra) {
	//key:某一个node
	//value:剩余的入度
	map<Node*, int> inMap;
	//起初入度为0的点，入队
	queue<Node*> zeroInQueue;
	for (auto node : gra->nodes) {
		inMap[node.second] = node.second->in;
		if (node.second->in == 0) {
			zeroInQueue.push(node.second);
		}
	}

	//拓扑排序的结果，依次加入result
	vector<Node*> result;
	while (!zeroInQueue.empty()) {
		Node* cur = zeroInQueue.front();
		zeroInQueue.pop();
		result.push_back(cur);
		for (auto next : cur->nexts) {
			inMap[next]--;	//擦除影响
			if (inMap[next] == 0) {
				zeroInQueue.push(next);
			}
		}
	}
	return result;
}


//最小生成树(无向图）
//K算法------------------------------------------------------
//依次考察最小的边，看加上的时候是否成环，若不成环加上，若成环，不加，考虑下一个。
//对于成环的判断，使用并查集来判断，加边的时候，考虑边的两个断点，若两个节点不在同一集合，则合并后不成环
class Kruskal {
public:
	//并查集替代结构
	class MySets {
	public:
		map<Node*, vector<Node*>> setMap;
		MySets(){}
		//初始，先让每个节点各自为一个集合
		MySets(vector<Node*> nodes) {
			for (auto cur : nodes) {
				vector<Node*> set;
				set.push_back(cur);
				setMap[cur] = set; 
			}
		}
		//判断集合是否相同
		bool isSameSet(Node* from, Node* to) {
			vector<Node*> fromSet = setMap[from];
			vector<Node*> toSet = setMap[to];
			return  fromSet == toSet;
		}
		//合并集合  
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
		MySets unionFind(tmp);		//自定义并查集
		priority_queue<Edge*,myCompair()> priorityQueue;	//优先队列，使得按权重有序排序
		for (auto edge : gra->edges) {		//建立优先队列
			priorityQueue.push(edge);	
		}
		vector<Edge*> result;
		while (!priorityQueue.empty()) {	
			Edge* edge = priorityQueue.top();	
			priorityQueue.pop();
			if (!unionFind.isSameSet(edge->from, edge->to)) {	//若两点不在一个集合，合并
				result.push_back(edge);
				unionFind.unionSet(edge->from, edge->to);
			}
		}
		return result;
	}
};


//Prim算法--------------------------------------------------------
// K算法是从边的角度考虑，p算法是从点角度出发
//思路： 先任选一点，解锁相关的边，并在其中挑选一个最小的边，再选出被挑选的最小边的另一断点，解锁相关边， 再在所有解锁的边中选最小边
// 在选最小边的过程中，若边的两个端点已被选过，则跳过此边，看下一条边，依次继续，直到优先队列为空
//流程：首先，选一个节点，将该节点所有相连的边入优先队，进入循环，取出权重最小的边，提出toNode,查找toNode是否已存在set中
//		若不存在，则此点是新点，此边属于result边集，再将toNode相连的边如优先队，循环往复
class Prim {
public:
	class myCompair {
	public:
		bool operator()(Edge* a, Edge* b) {
			return a->weight < b->weight;
		}
	};

	vector<Edge*> primMST(Graph* gra) {
		//解锁的边进入小根堆
		priority_queue<Edge,myCompair> priQueue;
		set<Node*> s;
		vector<Edge*> result;		//依次挑选的边在result里面
		for (auto node : gra->nodes) {		//随便挑了一个点，处理森林的情况，寻找下一颗最小生成树
			//node开始点
			if (!s.count(node.second)) {
				s.insert(node.second);
				for (auto edge : node.second->edges) {//由一个点，解锁所有相连的边
					priQueue.push(edge);
				}
					
				while (!priQueue.empty()) {
					Edge* edge = priQueue.top();	//取出解锁的边中，最小的边
					priQueue.pop();
					Node* toNode = edge->to;	//可能的一个新点
					if (!s.count(toNode)) {		//不含有的时候就是新点
						s.insert(toNode);
						result.push_back(edge);
						for (auto nextEdge : toNode->edges) {	//虽然有边会被重复放入优先队中，但对应的点已被放入set中，会被跳过
							priQueue.push(nextEdge);		//不影响最终结果，但会增大常数时间，若想进一步优化，可建一个边集set
						}
					}
				}
			}
		}
		return result;
	}
};



//Dijkstras单源最短路径算法
//思路：用一表，记录源节点到其他节点的距离，若表中没有某个节点的记录，说明源节点到此结点的距离为无穷，初始时只记录有自己到自己的距离0
//选出最小距离的点，看看从此点出发的边能不能使其得 源点到其他点得距离更小，若可以，则改写距离。当节点的边遍历完后，再也不用该点了。
//依次继续，直到所有点被锁定，即可得出答案，
//适用范围：可以有权值为负数的边，不能有累计值为负数的环

class Dijkstra {
public:
	map<Node*, int> dijkstra(Node* head) {
		//从head出发到所有点的最小距离
		//key:从head出发到达key
		//value:从head出发到达key的最小距离
		//如果在表中，没有T的记录，含义是从head出发到达T这个点的距离为正无穷
		map<Node*, int> distanceMap;
		distanceMap.emplace(head, 0);
		//已经求过距离的节点，存在selectedNodes中，以后再也不碰
		set<Node*> selectedNodes;	//已选择过的节点
		Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);	//找出最小边节点
		while (minNode) {
			int distance = distanceMap[minNode];	//找出源节点到minNode的距离
			for (auto edge : minNode->edges) {		//遍历minNode发出的边
				Node* toNode = edge->to;
				if (!distanceMap.count(toNode)) {		//如果minNode指向的点没有记录在distanceMap中，说明源点到此点距离为无穷
					distanceMap[toNode] = distance + edge->weight;	//加入相关节点
				} else {
					distanceMap[edge->to] = min(distanceMap[toNode], distance + edge->weight);	//更新最短路径
				}
			}
			selectedNodes.insert(minNode);	//将遍历过的相关节点记录，此后不再碰
			minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);	//找出最小边节点 
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
	
	//改进，采用手动调整堆
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
			if (inHeap(node)) {		//若在堆中，且有效
				distanceMap[node] = min(distanceMap[node], distance);	//更新距离
				insertHeapify(node, heapIndexMap[node]);	//调整堆，因更新后的值只会更小，所建堆又是小堆，所以只可能向上调整
			}
			if (!isEntered(node)) {	//不在堆中
				nodes[size] = node;		//尾插在后面
				heapIndexMap[node] = size;	//记录下标位置
				distanceMap[node] = distance;	//记录距离
				insertHeapify(node, size++);	//调整堆
			}
		}
		

		NodeRecord* pop() {
			NodeRecord* nodeRecord = new NodeRecord(nodes[0], distanceMap[nodes[0]]);
			swapPos(0, --size );
			heapIndexMap[nodes[size]] = -1;	//置为-1，表示此最短距离已确定，今后不再考虑
			distanceMap.erase(nodes[size]);	//去除已确定的距离
			//delete(nodes[size]);	//在这里不能delete，nodes指向的是源graph的Node节点，释放后图中就会缺失一个节点
			nodes[size] = nullptr;	//置空
			heapify(0, size);	//向下调整堆
			return nodeRecord;
		}
	private:
		//是否在堆中
		bool isEntered(Node* node) {	
			return heapIndexMap.count(node);
		}

		//node是否在堆中，且有效，是返回true
		bool inHeap(Node* node) {
			return isEntered(node) && heapIndexMap[node] != -1;
		}

		void swapPos(int index1, int index2) {
			heapIndexMap[nodes[index1]] = index2;
			heapIndexMap[nodes[index2]] = index1;
			swap(nodes[index1], nodes[index2]);
		}

		void insertHeapify(Node* node, int index) {
			//子比父还要小，交换位置
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
		map<Node*, int> heapIndexMap;	//Node*为key,Node*在堆上的位置index为value
		map<Node*, int> distanceMap;	//Node*到源点的距离
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



//借此复习堆排序
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
		swap(arr[0], arr[--heapSize]);	//将堆顶元素与堆尾交换，即将最大的数排在了最后，--heapSize,表示最大的数已经排好，缩小排序范围
		while (heapSize > 0) {	
			heapify(arr, 0, heapSize);	//换后，向下调整堆,O(logN)
			swap(arr[0], arr[--heapSize]);	//选出最大
		}
	}
private:
	//某个数在index位置上，往上继续移动
	void heapInsert(vector<int>& arr, int index) {
		while(arr[index] > arr[(index - 1) / 2]) {
			swap(arr[index], arr[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}

	//某个数在index位置，能否往下移动
	void heapify(vector<int>& arr, int index, int heapSize) {
		int left = index * 2 + 1;	
		while (left < heapSize) {
			//两个孩子中，谁的值大，把下标给largest
			int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;

			//父和孩子之间，谁的值大，把下标给largest
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
	void heapSort2(vector<int>& arr) {		//这是另一种常见的写法，效率与1同级，只是在第一次for循环中比1少半循环
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

	//直接从头到尾构图，麻烦
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
	//所生成图如图所示https://pics0.baidu.com/feed/14ce36d3d539b600a9e6969e35de7523c65cb703.jpeg?token=bf554ff0861c36f8327b7d75e6c9e670
	//所建之图正确
	cout << "testBFS:" << endl;
	graBFS(g->nodes[0]);	//测试结果正确
	cout << endl;
	cout << "testDFS:" << endl;
	graDFS(g->nodes[0]);	//测试结果正确
	cout << endl;

	cout << "test dijkstra1:" << endl;
	Dijkstra d;
	auto result=d.dijkstra1(g->nodes[0]);		//测试结果正确
	for (auto res : result) {
		cout << res.first->value << "-->" << res.second << endl;
	}
	cout << "test dijkstra2:" << endl;
	result = d.dijkstra2(g->nodes[0],6);		//测试结果正确
	for (auto res : result) {
		cout << res.first->value << "-->" << res.second << endl;
	}
	Node* cur = g->nodes[0];	//查看知，堆上空间已被释放
	delete(g);
	g = nullptr;

	//testHeapSort();
	
	return 0;
}
