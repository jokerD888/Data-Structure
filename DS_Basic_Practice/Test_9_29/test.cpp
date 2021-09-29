#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<numeric>
//�ַ���

//763. ������ĸ����

//��һ�������ҵ�ǰi��Ԫ�ص���ͬԪ�ص����Χend�������ǰԪ���±�==end��˵�����ﵽ�˱߽磬���ɽ���γ��Ȳ��������
//�ٸ���begin������ֻ����һ�ε�Ԫ�أ�Ҫ�жϴ�Ԫ���±��Ƿ��endС������endС��˵����Ԫ�ذ����ڵ�ǰƬ�Σ������Ԫ���Գ�һ��
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> ans;

        int end = -1, begin = 0;
        for (int i = 0; i < s.size(); i++) {
            int pos = s.find(s[i], i + 1);
            if (pos == -1 && i > end) {
                ans.push_back(1);
                begin = i + 1;
            } else if (pos > end) {
                end = s.find(s[i], i + 1);
            }
            if (i == end) {
                ans.push_back(end - begin + 1);
                begin = end + 1;
            }
        }

        return ans;
    }
};

//�������ٽ�˼·���ƣ���ͬ��������������ֵ���˷�ʽ�ȱ���һ�飬��¼�˸�����ĸ�����ֵ��±�,
//�ٱ�����end=��ǰ��ĸ������ֵĴ�����end�����ֵ���˷��������ڷ�һ����ȥfnid���ң���ֻ����һ�ε���ĸ���������
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26];
        int length = s.size();
        for (int i = 0; i < length; i++) {
            last[s[i] - 'a'] = i;
        }
        vector<int> partition;
        int start = 0, end = 0;
        for (int i = 0; i < length; i++) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                partition.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return partition;
    }
};

//49. ��ĸ��λ�ʷ���

//��һ������������ʱ  
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> ans;
		int length = strs.size();
		//��־���飬��Ӧ��strs�е��ַ����Ƿ��¼���б���
		vector<bool> arr(length, true);

		for (int i = 0; i < length; i++) {
			vector<string> ansSeed;
			if (arr[i]) {      //���δ��¼
				ansSeed.push_back(strs[i]);
				arr[i] = false;
                string s1 = strs[i];
                sort(s1.begin(), s1.end());
				for (int j = i + 1; j < length; j++) {
                    if (arr[j]) {
                        string s2 = strs[j];
                        if (s1.size() == s2.size()) {
                            sort(s2.begin(), s2.end());
                            if (s1 == s2) {
                                ansSeed.push_back(strs[j]);
                                arr[j] = false;
                            }
                        }
                    }
				}
				ans.push_back(ansSeed);
			}
		}

		return ans;
	}
};

//����������
//��������õ��˵ĵ���Ϊkey��������key����ĸ��λ����ɵ�����Ϊvalue,����������ĸ��λ����������ͬһ�ִ�������ӳ��
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, vector<string>> mp;
		for (string& str : strs) {
			string key = str;
			sort(key.begin(), key.end());
			mp[key].emplace_back(str);
		}
		vector<vector<string>> ans;
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			ans.emplace_back(it->second);
		}
		return ans;
	}
};


//����������

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        unordered_map<string, vector<string>> cache;
        for (string& str : strs)
        {
            string key(26, '0');
            for (char& c : str)
            {
                key[c - 'a']++;
            }
            cache[key].emplace_back(str);
        }
        vector<vector<string>> result;
        auto begin = cache.begin();
        while (begin != cache.end())
        {
            result.emplace_back(begin->second);
            begin++;
        }
        return result;
    }
};



class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string_view, vector<string>> cache;
        vector<array<char, 26>> keys;
        keys.reserve(size(strs));
        for (auto&& str : strs) {
            auto&& key = keys.emplace_back();
            for (auto ch : str) ++key[ch - 'a'];
            cache[{data(key), 26}].emplace_back(move(str));
        }
        vector<vector<string>> ret;
        ret.reserve(size(cache));
        transform(begin(cache), end(cache), back_insert_iterator(ret),
            [](auto&& x) { return move(x.second); });
        return ret;
    }
};
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> mp;  //value��Ӧres�±꣬����������ַ������±�ӳ��
        vector<vector<string>> res(strs.size());
        int index = 0;
        for (int i = 0; i < strs.size(); i++)
        {
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            if (mp.find(temp) != mp.end())
            {
                res[mp[temp]].push_back(strs[i]);
            } else
            {
                mp[temp] = index;   
                res[mp[temp]].push_back(strs[i]);
                index++;
            }
        }
        for (int i = res.size() - 1; i >= 0; i--)//ȥ������Ԫ��
        {
            if (res[i].empty()) res.pop_back();
            else break;
        }
        return res;
    }
};

