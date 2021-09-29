#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<numeric>
//字符串

//763. 划分字母区间

//法一：遍历找到前i个元素的相同元素的最大范围end，如果当前元素下标==end，说明，达到了边界，即可将这段长度插入答案数组
//再更新begin，对于只出现一次的元素，要判断此元素下标是否比end小，若比end小，说明此元素包含于当前片段，否则此元素自成一段
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

//法二：官解思路类似，不同的是找区间的最大值，此方式先遍历一遍，记录了各个字母最后出现的下标,
//再遍历，end=当前字母最晚出现的次数与end的最大值。此方法较优于法一，免去fnid查找，与只出现一次的字母的特殊情况
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

//49. 字母异位词分组

//法一：暴力，但超时  
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> ans;
		int length = strs.size();
		//标志数组，对应着strs中的字符串是否记录在列表中
		vector<bool> arr(length, true);

		for (int i = 0; i < length; i++) {
			vector<string> ansSeed;
			if (arr[i]) {      //如果未记录
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

//法二：排序
//以已排序好的了的单词为key，以所有key的字母异位词组成的数组为value,利用所有字母异位词排完序都是同一字串来进行映射
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


//法三：计数

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
        unordered_map<string, int> mp;  //value对应res下标，用用排序后字符串和下标映射
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
        for (int i = res.size() - 1; i >= 0; i--)//去除多余元素
        {
            if (res[i].empty()) res.pop_back();
            else break;
        }
        return res;
    }
};

