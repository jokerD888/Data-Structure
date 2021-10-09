#define _CRT_SECURE_NO_WARNINGS 1

//ջ������

#include<iostream>
using namespace std;
#include<vector>
#include<stack>


//155. ��Сջ

//��һ������vector��ʵ��,������������ʱ�������Сֵ������������
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
////����������ջ������min_stackջ�׵�Ԫ�أ�min_stack�и�λ�õ�Ԫ�ض�Ӧ��x_stack��Ӧλ�ü����·�Ԫ�ص���Сֵ
////����ʱ��x_stackֱ�Ӳ��룬min_stack����min(x,min_stack.top())Ϊ����x_stack��Ӧ��min_stack��Ϊ��ʱջ����Сֵ��ʵ�ֳ���������Сֵ
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
////������ֻʹ��һ��ջ������ʹ�ø���ջ����ôջ�д洢�ľͲ�����ԭ�����ˣ���ľ��ǲ�ֵ��
//
////1.��ջΪ�գ����⿼�ǣ�minv=value,push(0)
////2.pushʱ������diff=value-minv,����diff,�����ݵ�diff�����������жϣ���diff<0����˵��valueС�ڵ�ǰ��Сֵminv,������Сֵ��Ϊminv
////3.popʱ����ջ��Ԫ��diff<0,����2��֪���˴�pushʱminv���޸��ˣ�����minv-=diff���ɽ�minv�ָ�Ϊ����һ��ֵ������minvδ���޸Ĳ��ûָ����������pop���ɡ�
////4.topʱ����Ҫ��ԭ���ݻ�ԭ����ջ��Ԫ��diff<0,return top���ɣ�����return minv + diff����ԭ���ݽ��з���
////5.getMinʱ��ֱ�ӷ���minv���ɣ���minv�ʹ洢��ջ��Ԫ�ص���Сֵ
////6.��������ʹ�� long long ��Ϊ�˷�ֹval-minv�������
////�˷������ڣ�popʱ��ջ�е�ֵ���Ǹ�������ôջ��Ԫ�ؾ�����Сֵ������Сֵ�ᷢ���仯��Ҫ�õ�ǰ����Сֵ-ջ��Ԫ����������Сֵ��
////������������ôջ����ֵ���ǵ�ǰջ��ֵ + ��Сֵ��
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
//		} else {//��ε�ֵ��ȥ���е���Сֵ
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




//1249. �Ƴ���Ч������

//
////��һ�������ж�������ŵ��±���ջ��Ȼ����s��ɾ�����������
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		stack<int> bra;
//
//		//��������ջ�����Ҫ��ĺ�ջ����һ�Ծ͵���ջ���ģ�����push
//		//O(N)
//		for (int i = 0; i < s.size(); i++) {
//			if (s[i] == '(' || s[i] == ')') {
//				if (!bra.empty() && s[i] == ')'&& s[bra.top()]=='(')
//					bra.pop();
//				else
//					bra.push(i);
//			}
//		}
//		//O(m*N)mΪ�������ţ�NΪs����
//		while (!bra.empty()) {
//			s.erase(bra.top(), 1);
//			bra.pop();
//		}
//		return s;
//	}
//};
//
//
////���������Թٷ���Ӧ��javaд������һ����Ҫ��ʱ��s.erase�ϣ��˷���ʱҲ���
//#include<set>
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		set<int> indexToRemove;	//�洢�������ŵ��±�
//		stack<int> st;		//ƥ������
//		//O(N)
//		for (int i = 0; i < s.length(); i++) {
//			if (s[i] == '(') {
//				st.push(i);			//'('ֱ��push
//			} if (s[i] == ')'){
//				if (st.empty()) {	//ջ�գ�')'push��indexToRemove
//					indexToRemove.insert(i);
//				} else {	//ƥ��ɹ���pop
//					st.pop();
//				}
//			}
//		}
//
//		//��st��ʣ��Ԫ��ȫ�ӵ�indexToRemove
//		//O(N)
//		while (!st.empty()) {
//			indexToRemove.insert(st.top());
//			st.pop();
//		}
//
//		string ans;	//������
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
////������
////ʱ�������������������ռ���ѷ
//class Solution {
//public:
//	string minRemoveToMakeValid(string s) {
//		string ans;
//		int openSeen = 0, balance = 0;	//openSeen�洢������������balanceΪƽ������
//		for (int i = 0; i < s.size(); i++) {
//			char c = s[i];
//			if (c == '(') {
//				openSeen++;
//				balance++;
//			} else if (c == ')') {
//				if (balance == 0) continue;	//����������ţ�ȥ��
//				balance--;
//			}
//			ans += c;
//		}
//
//		string res;
//		int openToKeep = openSeen - balance;	//ʵ����Ч������������
//		for (int i = 0; i < ans.size(); i++) {
//			char c = ans[i];
//			if (c == '(') {
//				openToKeep--;
//				if (openToKeep < 0) continue;	//ȥ�������������
//			}
//			res += c;
//		}
//
//		return res;
//	}
//};
//


//1823. �ҳ���Ϸ�Ļ�ʤ��
#include<list>

//��һ������list�����п��ٵ�ɾ������������β��Ҫע�����¸��ĵ�������ָ�򣬱��������ʧЧ����������һѭ������
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
		//��
		//���ѭ����Ҫɾ���ĸ�����n-1���ڴ�ѭ��k-1�Σ��ҵ�Ҫɾ����λ��

		for (int i = 0; i < n - 1; i++) {
			cur = (k - 1)%li.size();	//����k>>n���Ż�
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



//����������˫�˶���,��ȫ����ӣ��ڴ�ͷ���ӣ���cur!=k,�ٴӺ���ӣ�
//ʱ��ռ䲻�編һ
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


//������vector����
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
////�������ֶ���ģ�⣬ֻ�Ǹ���ʹ���˲��õ����ݽṹ
//
////���ģ��ݹ�/��̬ģ��
////˼·Ϊ��ÿɾ��һ�����ֺ󣬾Ͷ���Щ�������±�ţ��ѵ������ҳ�ɾ��ǰ��ɾ��������ֵ�ӳ���ϵ��n==1��Ϊ�ݹ�ĳ���
////��Ȼ�˷�Ϊ���Ž� 
class Solution {
public:
	int f(int n, int k) {
		if (n == 1) return 0;
		return (f(n - 1, k) + k) % n;	
		//��
		//return n==1? 0:(f(n - 1, k) + k) % n;
	}
	int findTheWinner(int n, int k) {
		return f(n, k) + 1;
	}
};
//�ݹ�ĵ���д��
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