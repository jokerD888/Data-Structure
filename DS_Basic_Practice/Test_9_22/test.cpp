
//�ַ���

#include<iostream>
using namespace std;
#include<unordered_map>
//
////415. �ַ������
//
//��һ�����ַ������ã�ģ��ӷ�
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

//������
//��һ�Ż������û����㣬��3��������������������Ԫ���������������к������
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
        // �������Ժ�Ĵ���Ҫ��ת����
        reverse(ans.begin(), ans.end());
        return ans;
    }
};



//409. ����Ĵ�

//��һ��
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char,int> m;
        //��¼Ԫ�س��ָ���
        for (auto c : s) {
            m[c]++;
        }

        
        int ans = 0;
        
        for (auto c : m) {
            //�������������,�ͼ�һ����Ϊ�������м�����������е�Ԫ��Ҫ�ɶԳ��֡�
            if (c.second % 2 ) {
                ans += (c.second - 1);
            } else {
                ans += c.second;
            }
        }
        //�����м�Ԫ�أ���ans==s.size()����s��������ĸ�������˻��ĵĹ���
        if (ans < s.size()) {
            ans ++;
        }
        return ans;

    }
};

//������
//����
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

//���ʹ���
//��һ�������ʷ�������������ù�ϣ���ӳ���ϵ���Ա���pattern����һ������ӳ���ϵ��һֱ�ͷ���false
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



//���������ù�ϣ���¼ÿһ���ַ���Ӧ���ַ������Լ�ÿһ���ַ�����Ӧ���ַ���
//Ȼ������ö��ÿһ���ַ����ַ�������Թ��̣����ϸ��¹�ϣ����������˳�ͻ����˵�����������벻����˫���ϵ��
// ö��  pattern  �е�ÿһ���ַ�������˫ָ������̯���Ե��ҵ����ַ��� str �ж�Ӧ���ַ�����
//ÿ��ȷ��һ���ַ����ַ�������ϣ����Ǿͼ���Ƿ���ֳ�ͻ����������ټ�����ַ����Ƿ�Ƚ���ϼ��ɡ�


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
            //��ӳ���Ѵ��ڣ������ڳ�ͻ
            if (str2ch.count(tmp) && str2ch[tmp] != ch) {
                return false;
            }
            //��ӳ���Ѵ��ڣ������ڳ�ͻ
            if (ch2str.count(ch) && ch2str[ch] != tmp) {
                return false;
            }
            str2ch[tmp] = ch;
            ch2str[ch] = tmp;
            i = j + 1;
        }
        //�Ƚ������ַ����Ƿ��Ѿ��Ƚ����
        return i >= m;
    }
};

//������
//��ͬ�ڷ�����ӳ���ϵ�������valueΪ�����±꣬������ʻ���ĸ���״γ��֣�ֻ��������һ�����ֹ������ɷ���false,
//�������ͬʱ�״γ��֣����¼���±��Ӱ�ӣ�����������״γ���,���жϴ�ʱ�ĵ��ʺ���ĸ��һ�γ��ֵ��±��Ƿ���ͬ��
//������ͬ����ĳ��������˵�������˳�ͻ������false;
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> comp;
        string tmp;
        //�����ʷ���
        for (auto c : s) {
            if (c != ' ') {
                tmp.push_back(c);
            } else {
                comp.push_back(tmp);
                tmp.clear();
            }
        }
        comp.push_back(tmp);
        //�Ƚϳ����Ƿ����Ӧ
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

