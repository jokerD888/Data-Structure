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
};
