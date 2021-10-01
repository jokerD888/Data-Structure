#define _CRT_SECURE_NO_WARNINGS 1

//字符串

#include<iostream>
using namespace std;
#include<vector>
#include<unordered_set>
//43. 字符串相乘

//法一：将其中一个乘数每一位单独与另一个乘数相乘再相加
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
			//不同位数，补零，后续再翻转
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
			//翻转
			reverse(curr.begin(), curr.end());
			//将数字变为对应字符
			for (auto& c : curr) {
				c += '0';
			}
			ans = addStrings(ans, curr);
		}
		return ans;
	}

	//字符串相加
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


//法二： 法一中频繁字符串相加导致效率不高，可以利用数组来代替字符串存储结果，就可大大减少对字符串的操作
//m位数和n位数相乘，结果可能是m+n-1位或m+n位，两个数同时取最小最大只即可证明
//先将每一位与另一个数字的其他位相乘再与对应数组元素相加存储到数组，先不考虑进位，待相乘操作完毕后再对进位进行操作
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

//187. 重复的DNA序列

//法一：暴力查找，最后一个用例超时
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


//法二：
//法一的不足在于在查找s中是否有相同字串的耗时，在此，不在s中进行字串的查找，而是利用集合seen来判断字串是否出现过
//若出现过则说明，这是一个重复字串，否则插入seen

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


//5. 最长回文子串

//法一：找出所有的回文字串，记录最长的，外层循环是找的是以s[i]为开头的最长回文字串，
//再进一层是从后往前遍历，先找到与s[i]想等的字符，再检测是否是回文，直到left>right
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


//法二：动态规划,此法虽然耗时较法一小，但空间复杂度高于法一
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2) {
			return s;
		}

		int maxLen = 1;
		int begin = 0;
		// dp[i][j] 表示 s[i..j] 是否是回文串
		vector<vector<bool>> dp(n, vector<bool>(n));
		// 初始化：所有长度为 1 的子串都是回文串
		for (int i = 0; i < n; i++) {
			dp[i][i] = true;
		}
		// 递推开始
		// 先枚举子串长度
		for (int L = 2; L <= n; L++) {
			// 枚举左边界，左边界的上限设置可以宽松一些
			for (int i = 0; i < n; i++) {
				// 由 L 和 i 可以确定右边界，即 j - i + 1 = L 得
				int j = L + i - 1;
				// 如果右边界越界，就可以退出当前循环
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

				// 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
				if (dp[i][j] && j - i + 1 > maxLen) {
					maxLen = j - i + 1;
					begin = i;
				}
			}
		}
		return s.substr(begin, maxLen);
	}
};

//法三：中心扩展算法
//法一优于空间，法二优于时间，此法中时间空间都比较优秀
//此法，从源回文串中间向两边扩展，若两边元素相等则有更大回文串，再扩展，若不相等了，则以此源回文串为中心的回文串达到了最长
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
			//以s[i]为源回文串，奇数
			auto [left1, right1] = expandAroundCenter(s, i, i);
			//以s[i]s[i+1]为源回文串，偶数
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


//法四：Manacher 算法（扩展内容）
//时间复杂度达到O（N），从法一的耗时950ms到法四的4ms,可见算法的魅力
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

