//����

#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<list>
#include<algorithm>
//56.�ϲ�����

//��һ��
//�Ȱ����������ʼ�Ÿ�����first��ʾĿ�������ͷ��second��ʾ�����β�����������ͷ<=Ŀ�������β�Ҵ������β>Ŀ�������β��
//��Ŀ������β����Ϊ������β����������ͷ����Ŀ������β��˵������û���ص������ɽ�first,second����ans,
//�ٶ�Ŀ��������и��£�ͬʱ��ֵΪ�������ͷ������i--�������¶Աȴ������Ŀ������
class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> ans;
		int first = intervals[0][0], second =intervals[0][0];
		for (int i = 0; i < intervals.size(); i++) {
				if (intervals[i][0] <= second) {
					if(intervals[i][1]>second)
						second = intervals[i][1];
				} else {
					ans.push_back({ first,second });
					first = second = intervals[i][0];
					i--;
				}
		}
		ans.push_back({ first,second });
		return ans;
	}
};
//�ٽ�����
class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() == 0) {
			return {};
		}
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> merged;
		for (int i = 0; i < intervals.size(); ++i) {
			int L = intervals[i][0], R = intervals[i][1];
			if (!merged.size() || merged.back()[1] < L) {
				merged.push_back({ L, R });
			} else {
				merged.back()[1] = max(merged.back()[1], R);
			}
		}
		return merged;
	}
};

//������
//ͨ��˫ָ�룬tΪ����β��ͨ��j����ѭ�����ҵ���������β
class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> ans;
		for (int i = 0; i < intervals.size();) {
			int t = intervals[i][1];
			int j = i + 1;
			while (j < intervals.size() && intervals[j][0] <= t) {
				t = max(t, intervals[j][1]);
				j++;
			}
			ans.push_back({ intervals[i][0], t });
			i = j;
		}
		return ans;
	}
};

//706. ��ƹ�ϣӳ��
//��һ���򵥵�������һһӳ��
class MyHashMap {
public:
	/** Initialize your data structure here. */
	MyHashMap() {
		for (int i = 0; i <= 1000001; i++) {
			Hash[i] = -1;
		}
		
	}

	/** value will always be non-negative. */
	void put(int key, int value) {
		Hash[key] = value;
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		return Hash[key];
	
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		Hash[key] = -1;
	}
	int Hash[1000001];
};

//�ٽ�
//����ַ����Ҳ��Ϊ��
class MyHashMap {
private:
	vector<list<pair<int, int>>> data;
	static const int base = 769;
	static int hash(int key) {
		return key % base;
	}
public:
	/** Initialize your data structure here. */
	MyHashMap() : data(base) {}

	/** value will always be non-negative. */
	void put(int key, int value) {
		int h = hash(key);
		for (auto it = data[h].begin(); it != data[h].end(); it++) {
			if ((*it).first == key) {
				(*it).second = value;
				return;
			}
		}
		data[h].push_back(make_pair(key, value));
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		int h = hash(key);
		for (auto it = data[h].begin(); it != data[h].end(); it++) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
		return -1;
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		int h = hash(key);
		for (auto it = data[h].begin(); it != data[h].end(); it++) {
			if ((*it).first == key) {
				data[h].erase(it);
				return;
			}
		}
	}
};


