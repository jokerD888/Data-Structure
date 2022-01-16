//21.1.16ÿ��һ��
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

//��һ��
//ʱ��O��N��
//�ռ�O��N��
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

//��
//��������ˮ������
//������ͷ��ʼ���������������Ա������ĵ� i���ڵ㣬���ѡ������ [0,i) �ڵ�һ���������������� 0���򽫴���Ϊ�ýڵ�ֵ������𰸲��䡣
//ÿ���ڵ㱻ѡ�еĸ��ʼ�Ϊ1/n;

//ˮ���������ڿռ�С��ʱ�临�Ӷȵͣ��������ڴ��������е�����������⡣

//ʹ����ˮ���㷨����ͨ�׵�����˵һ�£�
//������ǳ�����ֻ��һ�����֣���ô�õ���һ�����ֵĸ��ʾ���100% ��ӹ���ɡ�
//��������50% ��������ÿ�����ֵļ��ʶ���33% �Դ����ơ�������
//�����ǲ�֪���������ж��ٸ����ֵ�ʱ�򣬾���Ҫ����ˮ�ص��㷨˼��ȥ���㡣

//������ǰ�е���һ�����֣���ʱȡ��һ�����ֵļ���Ϊ100% ����result��Ȼ����������֡�
//ǰ�����ڶ������֣���ô��ʱȡ������ֵļ�����Ȼ��Ϊ50% ��������ֻ���������֣�����ô����50% �ļ���ȡ�����֣�50% �ļ��ʱ���ԭ�������֡�
//���������ֵ�ʱ��33% �ļ���ȡ��ǰ���µ�������֣�66% �ļ��ʱ���ԭ�������֡���66% �У�ԭ����������50% �ļ�����1����50% �ļ�����2��Ҳ���Ǵ�ʱ�������ֵĸ��ʶ�Ϊ33% �� ͨ������㷨�����ܴﵽȡ���ĸ��ʾ�̯���Ӷ�ʵ�������
//֮��ͬ���֤
class Solution {
	ListNode* head;

public:
	Solution(ListNode* head) {
		this->head = head;
	}

	int getRandom() {
		int i = 1, ans = 0;
		for (auto node = head; node; node = node->next, ++i) {
			if (rand() % i == 0) { // 1/i �ĸ���ѡ�У��滻Ϊ�𰸣�
				ans = node->val;
			}
		}
		return ans;
	}
};

//997. �ҵ�С��ķ���
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

//����
//���ű��ˣ��Լ�--�������ŵ���++
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

//�ٽ⣬���ͼ�ĳ��Ⱥ���ȵĸ�����ʺͽ�һ����
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


