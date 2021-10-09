#define _CRT_SECURE_NO_WARNINGS 1

//栈、队列

#include<iostream>
using namespace std;
#include<vector>
#include<stack>


//155. 最小栈

//法一：利用vector简单实现,但不满足线性时间检索最小值，不满足题意
//class MinStack {
//public:
//	vector<int> data;
//	MinStack() {
//
//	}
//
//	void push(int val) {
//		data.push_back(val);
//	}
//
//	void pop() {
//		data.pop_back();
//	}
//
//	int top() {
//		return data.back();
//	}
//
//	int getMin() {
//		int min = data[0];
//		for (int i : data) {
//			if (i < min)
//				min = i;
//		}
//		return min;
//	}
//};
//
////法二：辅助栈，除了min_stack栈底的元素，min_stack中各位置的元素对应着x_stack对应位置及其下方元素的最小值
////插入时，x_stack直接插入，min_stack插入min(x,min_stack.top())为的是x_stack对应的min_stack即为此时栈中最小值，实现常数查找最小值
//class MinStack {
//	stack<int> x_stack;
//	stack<int> min_stack;
//public:
//	MinStack() {
//		min_stack.push(INT_MAX);
//	}
//
//	void push(int x) {
//		x_stack.push(x);
//		min_stack.push(min(min_stack.top(), x));
//	}
//
//	void pop() {
//		x_stack.pop();
//		min_stack.pop();
//	}
//
//	int top() {
//		return x_stack.top();
//	}
//
//	int getMin() {
//		return min_stack.top();
//	}
//};
//
////法三：只使用一个栈，不再使用辅助栈，那么栈中存储的就不能是原数据了，存的就是差值了
//
////1.若栈为空，特殊考虑，minv=value,push(0)
////2.push时，根据diff=value-minv,插入diff,随后根据的diff的正负，可判断，若diff<0，即说明value小于当前最小值minv,否则，最小值仍为minv
////3.pop时，若栈顶元素diff<0,根据2可知，此次push时minv被修改了，经过minv-=diff即可将minv恢复为其上一个值，否则，minv未被修改不用恢复操作。最后pop即可。
////4.top时，需要把原数据还原，若栈顶元素diff<0,return top即可，否则，return minv + diff来还原数据进行返回
////5.getMin时，直接返回minv即可，因minv就存储着栈中元素的最小值
////6.数据类型使用 long long 是为了防止val-minv数据溢出
////此法巧妙在：pop时，栈中的值若是负数，那么栈顶元素就是最小值，且最小值会发生变化，要用当前的最小值-栈顶元素来更新最小值。
////若是正数，那么栈顶的值就是当前栈顶值 + 最小值。
//class MinStack {
//public:
//	stack<long long> minSt;
//	long long minv;
//
//	MinStack() {  }
//
//	void push(int val) {
//		if (!minSt.size()) {
//			minSt.push(0);
//			minv = val;
//		} else {//这次的值减去已有的最小值
//			long long diff = val - minv;
//			minSt.push(diff);
//			minv = diff < 0 ? val : minv;
//		}
//	}
//
//	void pop() {
//		if (minSt.size()) {
//			long long diff = minSt.top();
//			minSt.pop();
//			if (diff < 0)
//				minv -= diff;
//		}
//	}
//
//	int top() {
//		long long diff = minSt.top();
//		if (diff < 0)
//			return minv;
//		else
//			return minv + diff;
//	}
//
//	int getMin() {
//		return minv;
//	}
//};




//1249. 移除无效的括号

//
////法一：将所有多余的括号的下标入栈，然后在s中删除多余的括号
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		stack<int> bra;
//
//		//将括号入栈，如果要入的和栈顶是一对就弹出栈顶的，否则push
//		//O(N)
//		for (int i = 0; i < s.size(); i++) {
//			if (s[i] == '(' || s[i] == ')') {
//				if (!bra.empty() && s[i] == ')'&& s[bra.top()]=='(')
//					bra.pop();
//				else
//					bra.push(i);
//			}
//		}
//		//O(m*N)m为多余括号，N为s长度
//		while (!bra.empty()) {
//			s.erase(bra.top(), 1);
//			bra.pop();
//		}
//		return s;
//	}
//};
//
//
////法二：来自官方对应的java写法，法一的主要耗时在s.erase上，此法耗时也差不多
//#include<set>
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		set<int> indexToRemove;	//存储多余括号的下标
//		stack<int> st;		//匹配括号
//		//O(N)
//		for (int i = 0; i < s.length(); i++) {
//			if (s[i] == '(') {
//				st.push(i);			//'('直接push
//			} if (s[i] == ')'){
//				if (st.empty()) {	//栈空，')'push进indexToRemove
//					indexToRemove.insert(i);
//				} else {	//匹配成功，pop
//					st.pop();
//				}
//			}
//		}
//
//		//将st中剩余元素全加到indexToRemove
//		//O(N)
//		while (!st.empty()) {
//			indexToRemove.insert(st.top());
//			st.pop();
//		}
//
//		string ans;	//答案数组
//		//O(N)
//		for (int i = 0; i < s.size(); i++) {
//			if (indexToRemove.find(i) == indexToRemove.end())
//				ans += s[i];
//		}
//
//		return ans;
//
//
//	}
//};
//
////法三：
////时间上优于以上两法，空间略逊
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		string ans;
//		int openSeen = 0, balance = 0;	//openSeen存储左括号数量，balance为平衡因子
//		for (int i = 0; i < s.size(); i++) {
//			char c = s[i];
//			if (c == '(') {
//				openSeen++;
//				balance++;
//			} else if (c == ')') {
//				if (balance == 0) continue;	//多余的右括号，去除
//				balance--;
//			}
//			ans += c;
//		}
//
//		string res;
//		int openToKeep = openSeen - balance;	//实际有效的左括号数量
//		for (int i = 0; i < ans.size(); i++) {
//			char c = ans[i];
//			if (c == '(') {
//				openToKeep--;
//				if (openToKeep < 0) continue;	//去除多余的左括号
//			}
//			res += c;
//		}
//
//		return res;
//	}
//};
//


//1823. 找出游戏的获胜者
#include<list>

//法一：利用list来进行快速的删除，当遍历到尾是要注意重新更改迭代器的指向，避免迭代器失效，整体类似一循环链表。
class Solution {
public:
	int findTheWinner(int n, int k) {
		list<int> li;
		//O(N)
		for (int i = 1; i <= n; i++) {
			li.push_back(i);
		}
		int cur = 1;
		auto it = li.begin();
		//O((n-1)*k)
		/*while (li.size() != 1) {
			if (cur == k) {
				auto tmp = ++it;
				li.erase(--it);
				cur = 1;
				it = tmp;
			} else {
				cur++;
				it++;
			}
			if (it == li.end()) {
				it = li.begin();
			}
		}*/
		//或
		//外层循环是要删除的个数即n-1，内存循环k-1次，找到要删除的位置

		for (int i = 0; i < n - 1; i++) {
			cur = (k - 1)%li.size();	//对于k>>n的优化
			while (cur--) {
				if (it == li.end())
					it = li.begin();
				it++;
				
			}
			if (it == li.end())
				it = li.begin();
			auto tmp = ++it;
			li.erase(--it);
			it = tmp;
		}

		return li.front();
	}

};



//法二：利用双端队列,先全部入队，在从头出队，若cur!=k,再从后入队，
//时间空间不如法一
#include<deque>
class Solution {
public:
	int findTheWinner(int n, int k) {
		deque<int> de;

		for (int i = 1; i <= n; i++) {
			de.push_back(i);
		}
		int cur = 1;
		while (de.size() != 1) {
			cur = (k - 1) % de.size();
			while (cur--) {
				de.push_back(de.front());
				de.pop_front();
			}
			de.pop_front();

		}

		return de.front();
	}
};


//法三：vector数组
class Solution {
public:
	int findTheWinner(int n, int k) {
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			v[i] = i + 1;
		}

		int d = k - 1;
		int index = 0;
		while (v.size()>1)
		{
			int pos = (index + d) % v.size();
			v.erase(v.begin() + pos);
			index = pos;

		}
		return v[0];
	}
};
//
////以上三种都是模拟，只是各自使用了不用的数据结构
//
////法四：递归/动态模拟
////思路为：每删除一个数字后，就对这些数字重新编号，难点在于找出删除前和删除后的数字的映射关系，n==1即为递归的出口
////显然此法为最优解 
class Solution {
public:
	int f(int n, int k) {
		if (n == 1) return 0;
		return (f(n - 1, k) + k) % n;	
		//或
		//return n==1? 0:(f(n - 1, k) + k) % n;
	}
	int findTheWinner(int n, int k) {
		return f(n, k) + 1;
	}
};
//递归的迭代写法
class Solution {
public:

	int findTheWinner(int n, int k) {
		int value = 0;
		for (int i = 2; i <= n; i++)
			value = (value + k) % i; 
		return value + 1;
	}
};

int main()
{

	Solution s;
	s.findTheWinner(5, 2);
	return 0;
}