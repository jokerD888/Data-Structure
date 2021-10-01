#define _CRT_SECURE_NO_WARNINGS 1

//�ַ���

#include<iostream>
using namespace std;
#include<vector>
#include<unordered_set>
//43. �ַ������

//��һ��������һ������ÿһλ��������һ��������������
class Solution {
public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		string ans = "0";
		int m = num1.size(), n = num2.size();
		for (int i = n - 1; i >= 0; i--) {
			string curr;
			int add = 0;
			//��ͬλ�������㣬�����ٷ�ת
			for (int j = n - 1; j > i; j--) {
				curr.push_back(0);
			}
			int y = num2.at(i) - '0';
			for (int j = m - 1; j >= 0; j--) {
				int x = num1.at(j) - '0';
				int product = x * y + add;
				curr.push_back(product % 10);
				add = product / 10;
			}
			while (add != 0) {
				curr.push_back(add % 10);
				add /= 10;
			}
			//��ת
			reverse(curr.begin(), curr.end());
			//�����ֱ�Ϊ��Ӧ�ַ�
			for (auto& c : curr) {
				c += '0';
			}
			ans = addStrings(ans, curr);
		}
		return ans;
	}

	//�ַ������
	string addStrings(string& num1, string& num2) {
		int i = num1.size() - 1, j = num2.size() - 1, add = 0;
		string ans;
		while (i >= 0 || j >= 0 || add != 0) {
			int x = i >= 0 ? num1.at(i) - '0' : 0;
			int y = j >= 0 ? num2.at(j) - '0' : 0;
			int result = x + y + add;
			ans.push_back(result % 10);
			add = result / 10;
			i--;
			j--;
		}
		reverse(ans.begin(), ans.end());
		for (auto& c : ans) {
			c += '0';
		}
		return ans;
	}
};


//������ ��һ��Ƶ���ַ�����ӵ���Ч�ʲ��ߣ��������������������ַ����洢������Ϳɴ����ٶ��ַ����Ĳ���
//mλ����nλ����ˣ����������m+n-1λ��m+nλ��������ͬʱȡ��С���ֻ����֤��
//�Ƚ�ÿһλ����һ�����ֵ�����λ��������Ӧ����Ԫ����Ӵ洢�����飬�Ȳ����ǽ�λ������˲�����Ϻ��ٶԽ�λ���в���
class Solution {
public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		int m = num1.size(), n = num2.size();
		vector<int> ansArr(m + n, 0);

		for (int i = m - 1; i >= 0; i--) {
			int x = num1[i] - '0';
			for (int j = n - 1; j >= 0; j--) {
				int y = num2[j] - '0';
				ansArr[i + j + 1] += x * y;
			}
		}

		for (int i = m + n - 1; i > 0; i--) {
			ansArr[i - 1] += ansArr[i] / 10;
			ansArr[i] %= 10;
		}

		int index = ansArr[0] == 0 ? 1 : 0;
		string ans;
		while (index < m + n) {
			ans.push_back(ansArr[index++] + '0');
		}

		return ans;
	}
};

//187. �ظ���DNA����

//��һ���������ң����һ��������ʱ
class Solution {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		if (s.size() <= 10) {
			return {};
		}

		unordered_set<string> ans;
		for (int begin=0; begin < s.size()-10; begin++) {
			string str = s.substr(begin, 10);
			if (ans.find(str)==ans.end()) {
				if (s.find(str, begin + 1) != s.npos) {
					ans.insert(str);
				}
			}
		}
		vector<string> res;
		for (auto s : ans) {
			res.push_back(s);
		}

		return res;
	}

};


//������
//��һ�Ĳ��������ڲ���s���Ƿ�����ͬ�ִ��ĺ�ʱ���ڴˣ�����s�н����ִ��Ĳ��ң��������ü���seen���ж��ִ��Ƿ���ֹ�
//�����ֹ���˵��������һ���ظ��ִ����������seen

class Solution {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		if (s.size() <= 10) {
			return {};
		}
		int L = 10, n = s.size();
		unordered_set<string> seen, ans;
		vector<string> res;
		for (int start = 0; start < n - L + 1; start++) {
			string tmp = s.substr(start, L);
			if (seen.find(tmp) != seen.end()) {
				ans.insert(tmp);
			} else {
				seen.insert(tmp);
			}

		}

		for (auto s : ans) {
			res.push_back(s);
		}
		return res;

	}
};


//5. ������Ӵ�

//��һ���ҳ����еĻ����ִ�����¼��ģ����ѭ�����ҵ�����s[i]Ϊ��ͷ��������ִ���
//�ٽ�һ���ǴӺ���ǰ���������ҵ���s[i]��ȵ��ַ����ټ���Ƿ��ǻ��ģ�ֱ��left>right
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		int ans;
		int maxlength = 0;
		for (int i = 0; i < n - maxlength; i++) {
			int left=i,right = n;
			int time = 1;
			while (left <= right) {
				left = i,right = n;
				for (int k = 0; k < time; k++) {
					--right;
					while (s[right] != s[left]) --right;
				}
				int length = 0;
				time++;
				while (left<=right && s[left] == s[right]) {
					length+=2;
					left++;
					right--;
				}
				if (left - right == 2) length--;
				if (left > right&& length>maxlength) {
					maxlength = length;
					ans = i;
				}
			}
		}
		string res = s.substr(ans, maxlength);
		return res;
	}
};


//��������̬�滮,�˷���Ȼ��ʱ�Ϸ�һС�����ռ临�Ӷȸ��ڷ�һ
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2) {
			return s;
		}

		int maxLen = 1;
		int begin = 0;
		// dp[i][j] ��ʾ s[i..j] �Ƿ��ǻ��Ĵ�
		vector<vector<bool>> dp(n, vector<bool>(n));
		// ��ʼ�������г���Ϊ 1 ���Ӵ����ǻ��Ĵ�
		for (int i = 0; i < n; i++) {
			dp[i][i] = true;
		}
		// ���ƿ�ʼ
		// ��ö���Ӵ�����
		for (int L = 2; L <= n; L++) {
			// ö����߽磬��߽���������ÿ��Կ���һЩ
			for (int i = 0; i < n; i++) {
				// �� L �� i ����ȷ���ұ߽磬�� j - i + 1 = L ��
				int j = L + i - 1;
				// ����ұ߽�Խ�磬�Ϳ����˳���ǰѭ��
				if (j >= n) {
					break;
				}

				if (s[i] != s[j]) {
					dp[i][j] = false;
				} else {
					if (j - i < 3) {
						dp[i][j] = true;
					} else {
						dp[i][j] = dp[i + 1][j - 1];
					}
				}

				// ֻҪ dp[i][L] == true �������ͱ�ʾ�Ӵ� s[i..L] �ǻ��ģ���ʱ��¼���ĳ��Ⱥ���ʼλ��
				if (dp[i][j] && j - i + 1 > maxLen) {
					maxLen = j - i + 1;
					begin = i;
				}
			}
		}
		return s.substr(begin, maxLen);
	}
};

//������������չ�㷨
//��һ���ڿռ䣬��������ʱ�䣬�˷���ʱ��ռ䶼�Ƚ�����
//�˷�����Դ���Ĵ��м���������չ��������Ԫ��������и�����Ĵ�������չ����������ˣ����Դ�Դ���Ĵ�Ϊ���ĵĻ��Ĵ��ﵽ���
class Solution {
public:
	pair<int, int> expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		return { left + 1, right - 1 };
	}

	string longestPalindrome(string s) {
		int start = 0, end = 0;
		for (int i = 0; i < s.size(); ++i) {
			//��s[i]ΪԴ���Ĵ�������
			auto [left1, right1] = expandAroundCenter(s, i, i);
			//��s[i]s[i+1]ΪԴ���Ĵ���ż��
			auto [left2, right2] = expandAroundCenter(s, i, i + 1);
			if (right1 - left1 > end - start) {
				start = left1;
				end = right1;
			}
			if (right2 - left2 > end - start) {
				start = left2;
				end = right2;
			}
		}
		return s.substr(start, end - start + 1);
	}
};


//���ģ�Manacher �㷨����չ���ݣ�
//ʱ�临�ӶȴﵽO��N�����ӷ�һ�ĺ�ʱ950ms�����ĵ�4ms,�ɼ��㷨������
class Solution {
public:
	int expand(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		return (right - left - 2) / 2;
	}

	string longestPalindrome(string s) {
		int start = 0, end = -1;
		string t = "#";
		for (char c : s) {
			t += c;
			t += '#';
		}
		t += '#';
		s = t;

		vector<int> arm_len;
		int right = -1, j = -1;
		for (int i = 0; i < s.size(); ++i) {
			int cur_arm_len;
			if (right >= i) {
				int i_sym = j * 2 - i;
				int min_arm_len = min(arm_len[i_sym], right - i);
				cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
			} else {
				cur_arm_len = expand(s, i, i);
			}
			arm_len.push_back(cur_arm_len);
			if (i + cur_arm_len > right) {
				j = i;
				right = i + cur_arm_len;
			}
			if (cur_arm_len * 2 + 1 > end - start) {
				start = i - cur_arm_len;
				end = i + cur_arm_len;
			}
		}

		string ans;
		for (int i = start; i <= end; ++i) {
			if (s[i] != '#') {
				ans += s[i];
			}
		}
		return ans;
	}
};

