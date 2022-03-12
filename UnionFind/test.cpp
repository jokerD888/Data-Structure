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


//���鼯��ϰ----------------------------------------


//200. ��������
//��һ��DFS
//class Solution {
//public:
//	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
//
//	void BFS(vector<vector<char>>& nums, vector<vector<bool>>& vis, int r, int c) {
//		if (nums[r][c] == '0')
//			return;
//		vis[r][c] = true;
//		int x = r, y = c;
//		int row = nums.size(), col = nums[0].size();
//		for (int i = 0; i < 4; ++i) {
//			x = r + dir[i][0];
//			y = c + dir[i][1];
//			if (x < 0 || x == row || y < 0 || y == col || vis[x][y]) {
//				continue;
//			}
//			BFS(nums, vis, x, y);
//		}
//	}
//	int numIslands(vector<vector<char>>& grid) {
//		int ret = 0;
//		int row = grid.size(), col = grid[0].size();
//		vector<vector<bool>> vis(row, vector<bool>(col));
//		for (int i = 0; i < row; ++i) {
//			for (int j = 0; j < col; ++j) {
//				if (!vis[i][j] && grid[i][j]=='1') {
//					BFS(grid, vis, i, j);
//					++ret;
//				}
//			}
//		}
//		return ret;
//	}
//};

//���߲�ʹ��vis������Ƿ�����������ֱ�����������ġ�1�����±��Ϊ��0��
//class Solution {
//public:
//	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
//
//	void DFS(vector<vector<char>>& nums, int r, int c) {
//		if (nums[r][c] == '0')
//			return;
//		nums[r][c] = '0';
//		int x = r, y = c;
//		int row = nums.size(), col = nums[0].size();
//		for (int i = 0; i < 4; ++i) {
//			x = r + dir[i][0];
//			y = c + dir[i][1];
//			if (x < 0 || x == row || y < 0 || y == col ) {
//				continue;
//			}
//			BFS(nums, x, y);
//		}
//	}
//	int numIslands(vector<vector<char>>& grid) {
//		int ret = 0;
//		int row = grid.size(), col = grid[0].size();
//		for (int i = 0; i < row; ++i) {
//			for (int j = 0; j < col; ++j) {
//				if (grid[i][j]=='1') {
//					DFS(grid,  i, j);
//					++ret;
//				}
//			}
//		}
//		return ret;
//	}
//};
//��ࣺ
//class Solution {
//public:
//
//	void DFS(vector<vector<char>>& nums, int r, int c) {
//		if (r < 0 || r == nums.size() || c < 0 || c == nums[0].size() || nums[r][c] != '1') {
//			return;
//		}
//		nums[r][c] = '0';
//		DFS(nums, r-1, c);
//		DFS(nums, r+1, c);
//		DFS(nums, r, c-1);
//		DFS(nums, r, c+1);
//	}
//	int numIslands(vector<vector<char>>& grid) {
//		int ret = 0;
//		int row = grid.size(), col = grid[0].size();
//		for (int i = 0; i < row; ++i) {
//			for (int j = 0; j < col; ++j) {
//				if (grid[i][j]=='1') {
//					DFS(grid,  i, j);
//					++ret;
//				}
//			}
//		}
//		return ret;
//	}
//};

//������BFS
//class Solution {
//public:
//	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
//
//	void BFS(vector<vector<char>>& nums, int r, int c) {
//		queue<pair<int, int>> q;
//		q.emplace(r, c);
//		int row = nums.size(), col = nums[0].size();
//		nums[r][c] = '0';	
//		while (!q.empty()) {
//			auto pairRet = q.front();
//			nums[pairRet.first][pairRet.second] = '0';
//			q.pop();
//			for (int i = 0; i < 4; ++i) {
//				int x = pairRet.first + dir[i][0];
//				int y = pairRet.second + dir[i][1];
//				if (x < 0 || y < 0 || x == row || y == col || nums[x][y]=='0') {
//					continue;
//				}
//				q.emplace(x, y);
//				//Ҫ�������ǡ�0��������ÿ�γ�����ʱ�ٱ��0�Ļ������ܻ���ѭ�������ߣ��ڴ�λ�ñ�ǡ�0�����ӷ��Ϲ�����ȱ�����˼��
//				nums[x][y]='0';		
//			}
//		}
//	}
//	int numIslands(vector<vector<char>>& grid) {
//		int row = grid.size(), col = grid[0].size();
//		int ret = 0;
//		for (int i = 0; i < row; ++i) {
//			for (int j = 0; j < col; ++j) {
//				if (grid[i][j] == '1') {
//					BFS(grid, i, j);
//					++ret;
//				}
//			}
//		}
//		return ret;
//	}
//};


//���������鼯
class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                } else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;		//��¼���ڵ��������
    int count;
};
//
//class Solution {
//public:
//    int numIslands(vector<vector<char>>& grid) {
//        int nr = grid.size();
//        if (!nr) return 0;
//        int nc = grid[0].size();
//
//        UnionFind uf(grid);
//        int num_islands = 0;
//        for (int r = 0; r < nr; ++r) {
//            for (int c = 0; c < nc; ++c) {
//                if (grid[r][c] == '1') {
//                    grid[r][c] = '0';
//                    if (r - 1 >= 0 && grid[r - 1][c] == '1') uf.unite(r * nc + c, (r - 1) * nc + c);
//                    if (r + 1 < nr && grid[r + 1][c] == '1') uf.unite(r * nc + c, (r + 1) * nc + c);
//                    if (c - 1 >= 0 && grid[r][c - 1] == '1') uf.unite(r * nc + c, r * nc + c - 1);
//                    if (c + 1 < nc && grid[r][c + 1] == '1') uf.unite(r * nc + c, r * nc + c + 1);
//                }
//            }
//        }
//
//        return uf.getCount();
//    }
//};
// �򻯳���ʱ��
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        UnionFind uf(grid);
        int num_islands = 0;
		// ֻͨ���ϲ����ϼ��������Ƭ����ĺϲ���ʡȥÿ�εı߽��ж�
		for (int j = 1; j < nc; ++j) {
			if (grid[0][j - 1] == '1' && grid[0][j] == '1') {
				uf.unite(j - 1, j);
			}
		}
		for (int i = 1; i < nr; ++i) {
			if (grid[i - 1][0] == '1' && grid[i][0] == '1') {
				uf.unite((i - 1) * nc, i * nc);
			}
		}
		for (int i = 1; i < nr; ++i) {
			for (int j = 1; j < nc; ++j) {
				if (grid[i][j] == '1') {
					if (grid[i][j - 1] == '1') {
						uf.unite(i * nc + j - 1, i * nc + j);
					}
					if (grid[i - 1][j] == '1') {
						uf.unite((i - 1) * nc + j, i * nc + j);
					}
				}
			}
		}
        return uf.getCount();
    }
};



//547. ʡ������
class FriendCircles {
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int N = isConnected.size();
		UnionFind unionFind(N);
		for (int i = 0; i < N; ++i) {
			for (int j = i + 1; j < N; ++j) {
				if (isConnected[i][j] == 1) {
					unionFind.unionSet(i, j);
				}
			}
		}
		return unionFind.setCount();

	}
	class UnionFind {
	private:
		//parent[i]=k  : i�ĸ�����k
		vector<int> parent;
		// size[i]=k  :  ���i�Ǵ����㣬size[i]�������壬���������壬������i���ڵļ��ϵĴ�С
		vector<int> size;
		//�����ṹ��������ƽ��·
		vector<int> help;
		//���ϵĸ���
		int sets;

		//��i��ʼһֱ���ϣ����ϵ����������ϣ������㣬����
		//�˹���Ҫ��·��ѹ��
		int find(int i) {
			int hi = 0;
			while (i != parent[i]) {
				help[hi++] = i;
				i = parent[i];
			}
			//��ʱ��i�ѳ�Ϊ������
			for (--hi; hi >= 0; --hi) {
				parent[help[hi]] = i;
			}
			return i;
		}

	public:
		int setCount() {
			return this->sets;
		}

		UnionFind(int N) {
			parent.resize(N);
			size.resize(N);
			help.resize(N);
			sets = N;
			for (int i = 0; i < N; ++i) {
				parent[i] = i;
				size[i] = 1;
			}
		}

		void unionSet(int i, int j) {
			int f1 = find(i);
			int f2 = find(j);
			if (f1 != f2) {
				if (size[f1] >= size[f2]) {
					size[f1] += size[f2];
					parent[f2] = f1;
				} else {
					size[f2] += size[f1];
					parent[f1] = f2;
				}
				sets--;
			}
		}
	};
};


//305. ��������||
class Solution {
public:
	vector<int> numIslands2(int m,int n,vector<vector<int>>& positions) {
		UnionFind uf(m, n);
		vector<int> ans;
		for (auto pos : positions) {
			ans.push_back(uf.connect(pos[0], pos[1]));
		}
		return ans;
	}

	class UnionFind {
	private:
		vector<int> parent;
		vector<int> size;
		vector<int> help;
		int row, col, sets;
	public:
		UnionFind(int m, int n) :row(m),col(n),sets(0){
			int len = m * n;
			parent.resize(len);
			size.resize(len);
			help.resize(len);
		}
		int connect(int r, int c) {
			int idx = index(r, c);
			if (size[idx] == 0) {
				parent[idx] = idx;
				size[idx] = 1;
				sets++;
				unionSet(r-1, c, r, c);
				unionSet(r+1, c, r, c);
				unionSet(r, c-1, r, c);
				unionSet(r, c+1, r, c);
			}
			return sets;
		}

	private:
		int index(int r, int c) {
			return r * col + c;
		}

		int find(int i) {
			int hi = 0;
			while (i != parent[i]) {
				help[hi++] = i;
				i = parent[i];
			}
			for (hi--; hi >= 0; --hi) {
				parent[help[hi]] = i;
			}
			return i;
		}

		void unionSet(int r1, int c1, int r2, int c2) {
			if (r1 < 0 || r2 < 0 || r1 == row || r2 == row || c1 == col || c2 == col || c1 < 0 || c2 < 0) {
				return;
			}
			int i1 = index(r1, c1);
			int i2 = index(r2, c2);
			if (size[i1] == 0 || size[i2] == 0) {
				return;
			}

			int f1 = find(i1);
			int f2 = find(i2);
			if (f1 != f2) {
				if (size[f1] > size[f2]) {
					size[f1] += size[f2];
					parent[f2] = f1;
				} else {
					size[f2] += size[f1];
					parent[f1] = f2;
				}
				--sets;
			}
		}
	};
};

//����1�����У�������grid�ܴ��ҿ������ö�cpu�������У���μ���
//���Σ����Խ���ֱ���иͬʱ�Ը���������и�Ⱦ��ͬʱ��¼ÿ����ĸ�ȾԴͷ�����������Ⱦ��󣬱����и��ߵ����Σ��Ƚϸ�Ⱦ���Դͷ�Ƿ���ͬ
//����ͬ���ϲ�����ÿ���и��߶��������У���󲢲鼯�м��ϵĸ�����Ϊ���������
