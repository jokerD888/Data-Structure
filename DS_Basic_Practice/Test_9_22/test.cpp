
//字符串

#include<iostream>
using namespace std;
#include<unordered_map>
//
////415. 字符串相加
//
//法一：将字符串倒置，模拟加法
class Solution {
public:
    string addStrings(string num1, string num2) {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        string ans;
        int i = 0, sign = 0;
        while (i < num1.size() && i < num2.size()) {
            if (num1[i] + num2[i]-'0' +sign > '9') {
                ans.push_back(num1[i] + num2[i] - 58 + sign);
                sign = 1;
            }
            else {
                ans.push_back(num1[i] + num2[i] - '0' + sign);
                sign = 0;
            }
            i++;
        }
        while (i < num1.size()) {
            if (num1[i] + sign  > '9') {
                ans.push_back(num1[i] + sign-10);
                sign = 1;
            } else {
                ans.push_back(num1[i] + sign);
                sign = 0;
            }
           
            i++;
        }
        while (i < num2.size()) {
            if (num2[i] + sign > '9') {
                ans.push_back(num2[i] + sign - 10);
                sign = 1;
            } else {
                ans.push_back(num2[i] + sign);
                sign = 0;
            }
            i++;
        }
        if (sign) {
            ans.push_back('1');
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

//法二：
//法一优化，巧用或运算，将3个条件串连起来，用三元运算符来对数组进行合理访问
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans.push_back('0' + result % 10);
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        // 计算完以后的答案需要翻转过来
        reverse(ans.begin(), ans.end());
        return ans;
    }
};



//409. 最长回文串

//法一：
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char,int> m;
        //记录元素出现个数
        for (auto c : s) {
            m[c]++;
        }

        
        int ans = 0;
        
        for (auto c : m) {
            //对与个数是奇数,就减一，因为不考虑中间情况，回文中的元素要成对出现。
            if (c.second % 2 ) {
                ans += (c.second - 1);
            } else {
                ans += c.second;
            }
        }
        //补充中间元素，若ans==s.size()，即s中所有字母都参与了回文的构造
        if (ans < s.size()) {
            ans ++;
        }
        return ans;

    }
};

//法二：
//类似
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> count;
        int ans = 0;
        for (char c : s)
            ++count[c];
        for (auto p : count) {
            int v = p.second;
            ans += v / 2 * 2;
            if (v % 2 == 1 and ans % 2 == 0)
                ++ans;
        }
        return ans;
    }
};

//单词规律
//法一：将单词分离出来，再利用哈希表的映射关系，对比着pattern串，一旦发现映射关系不一直就返回false
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> comp;
        string tmp;
        for (auto c : s) {
            if (c!=' ') {
                tmp.push_back(c);
            }
            else {
                comp.push_back(tmp);
                tmp.clear();
            }
        }
        comp.push_back(tmp);
        if (comp.size() != pattern.size()) {
            return false;
        }

        unordered_map<string, char> m;
        for (int i = 0; i < pattern.size(); i++) {
            if (m.find(comp[i]) == m.end()) {
                if (pattern.find(pattern[i]) == i) {
                    m[comp[i]] = pattern[i];
                } else {
                    return false;
                }
            } else {
                if (m[comp[i]] != pattern[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};



//法二：利用哈希表记录每一个字符对应的字符串，以及每一个字符串对应的字符。
//然后我们枚举每一对字符与字符串的配对过程，不断更新哈希表，如果发生了冲突，则说明给定的输入不满足双射关系。
// 枚举  pattern  中的每一个字符，利用双指针来均摊线性地找到该字符在 str 中对应的字符串。
//每次确定一个字符与字符串的组合，我们就检查是否出现冲突，最后我们再检查两字符串是否比较完毕即可。


class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string, char> str2ch;
        unordered_map<char, string> ch2str;
        int m = str.length();
        int i = 0;
        for (auto ch : pattern) {
            if (i >= m) {
                return false;
            }
            int j = i;
            while (j < m && str[j] != ' ') j++;
            const string& tmp = str.substr(i, j - i);
            //当映射已存在，但存在冲突
            if (str2ch.count(tmp) && str2ch[tmp] != ch) {
                return false;
            }
            //当映射已存在，但存在冲突
            if (ch2str.count(ch) && ch2str[ch] != tmp) {
                return false;
            }
            str2ch[tmp] = ch;
            ch2str[ch] = tmp;
            i = j + 1;
        }
        //比较两个字符串是否已经比较完毕
        return i >= m;
    }
};

//法三：
//不同于法二的映射关系，这里的value为数组下标，如果单词或字母是首次出现，只有其中有一个出现过，即可返回false,
//如果两者同时首次出现，则记录和下标的影视，如果都不是首次出现,则判断此时的单词和字母上一次出现的下标是否相同，
//若不相同，按某种意义来说即产生了冲突，返回false;
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> comp;
        string tmp;
        //将单词分离
        for (auto c : s) {
            if (c != ' ') {
                tmp.push_back(c);
            } else {
                comp.push_back(tmp);
                tmp.clear();
            }
        }
        comp.push_back(tmp);
        //比较长度是否相对应
        if (comp.size() != pattern.size()) {
            return false;
        }

        unordered_map<char, size_t> ch;
        unordered_map<string, size_t> str;

        for (size_t i = 0; i < comp.size(); i++) {
            if (ch.find(pattern[i]) == ch.end() || str.find(comp[i]) == str.end()) {
                if (ch.find(pattern[i]) != ch.end() || str.find(comp[i]) != str.end()) {
                    return false;
                }
                ch[pattern[i]] = i;
                str[comp[i]] = i;
            } else if (ch[pattern[i]] != str[comp[i]]) {
                return false;
            }
        }

        return true;
    }
};

