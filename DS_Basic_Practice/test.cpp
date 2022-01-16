//21.1.16每日一题
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

//法一：
//时间O（N）
//空间O（N）
class Solution {
public:
	vector<int> arr;
	Solution(ListNode* head) {
		while (head) {
			arr.emplace_back(head->val);
			head = head->next;
		}
	}

	int getRandom() {
		return arr[rand() % arr.size()];
	}
};

//或
//方法二：水塘抽样
//从链表头开始，遍历整个链表，对遍历到的第 i个节点，随机选择区间 [0,i) 内的一个整数，如果其等于 0，则将答案置为该节点值，否则答案不变。
//每个节点被选中的概率即为1/n;

//水塘抽样由于空间小，时间复杂度低，可以用于大数据流中的随机抽样问题。

//使用蓄水池算法，用通俗的语言说一下：
//如果我们池子中只有一个数字，那么拿到第一个数字的概率就是100% 毋庸置疑。
//两个数字50% 三个数字每个数字的几率都是33% 以此类推。。。。
//当我们不知道池子里有多少个数字的时候，就需要用蓄水池的算法思想去计算。

//当链表前行到第一个数字，此时取第一个数字的几率为100% ，那result自然等于这个数字。
//前进到第二个数字，那么此时取这个数字的几率自然就为50% （池子里只有两个数字），那么就是50% 的几率取新数字，50% 的几率保留原本的数字。
//第三个数字的时候，33% 的几率取当前最新的这个数字，66% 的几率保留原本的数字。这66% 中：原本的数字有50% 的几率是1，有50% 的几率是2。也就是此时三个数字的概率都为33% 。 通过这个算法，就能达到取数的概率均摊，从而实现随机。
//之后同理可证
class Solution {
	ListNode* head;

public:
	Solution(ListNode* head) {
		this->head = head;
	}

	int getRandom() {
		int i = 1, ans = 0;
		for (auto node = head; node; node = node->next, ++i) {
			if (rand() % i == 0) { // 1/i 的概率选中（替换为答案）
				ans = node->val;
			}
		}
		return ans;
	}
};

//997. 找到小镇的法官
class Solution {
public:
	int findJudge(int n, vector<vector<int>>& trust) {
		vector<int> people(n + 1, 0);
		vector<bool> judge(n + 1, true);
		for (auto& ts : trust) {
			judge[ts[0]] = false;
			++people[ts[1]];
		}

		for (int i = 1; i < people.size(); ++i) {
			if (people[i] == n - 1 && judge[i]) {
				return i;
			}
		}
		return -1;
	}
};

//进阶
//相信别人，自己--，被相信的人++
class Solution {
public:
	int findJudge(int n, vector<vector<int>>& trust) {
		vector<int> people(n + 1, 0);
		for (auto& ts : trust) {
			people[0]--;
			people[1]++;
		}

		for (int i = 1; i < people.size(); ++i) {
			if (people[i] == n - 1) {
				return i;
			}
		}
		return -1;
	}
};

//官解，理解图的出度和入度的概念，本质和解一类似
class Solution {
public:
	int findJudge(int n, vector<vector<int>>& trust) {
		vector<int> inDegrees(n + 1);
		vector<int> outDegrees(n + 1);
		for (auto& edge : trust) {
			int x = edge[0], y = edge[1];
			++inDegrees[y];
			++outDegrees[x];
		}
		for (int i = 1; i <= n; ++i) {
			if (inDegrees[i] == n - 1 && outDegrees[i] == 0) {
				return i;
			}
		}
		return -1;
	}
};


