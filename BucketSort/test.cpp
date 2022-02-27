#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//桶排序思想下的排序 ：计数排序，基数排序
//时间复杂读为O（N)
//不基于比较的排序

//计数排序
//适用于数据范围较小的情况
//时间O（N）
class CountSort {
public:
	//默认最小数据从0开始且无稳定性
	void countSortNoStable(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		int maxNum = INT_MIN;
		//寻找最大元素
		for (int i = 0; i < arr.size(); ++i) {
			maxNum = max(maxNum, arr[i]);
		}
		vector<int> bucket(maxNum + 1);
		//计数
		for (int i = 0; i < arr.size(); ++i) {
			++bucket[arr[i]];
		}
		int i = 0;//重新覆盖原数组
		for (int j = 0; j < bucket.size(); ++j) {
			while (bucket[j]--) {
				arr[i++] = j;
			}
		}
		return;
	}

	void countSortStable(vector<int>& arr) {
		//找出最大最小值
		auto minAndMax = minmax_element(arr.begin(), arr.end());
		int minNum = *minAndMax.first;
		int maxNum = *minAndMax.second;

		//建立范围计数表
		vector<int> count(maxNum - minNum + 1);
		for (auto n : arr) {
			++count[n - minNum];
		}
		//前缀累加
		for (int i = 1; i < count.size(); ++i) {
			count[i] += count[i - 1];
		}
		//此时的count[i]表示小于等于i的有几个
		vector<int> sorted(arr.size());
		for (int i = arr.size() - 1; i >= 0; --i) {
			//下标从0开始，得-1
			sorted[count[arr[i] - minNum]-1] = arr[i];
			--count[arr[i] - minNum];
		}
		arr = sorted;
	}

};




//基数排序
//适用于非负10进制数字，一般数字不会太大
//时间严格来说O（N*log10M(以10为底,以M为真数，M为元素最大值))	通常称为O（N）
class RadixSort {
public:
	void radixSort(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		//以下radixSort为本函数的子过程，参数列表不同
		radixSort(arr, 0, arr.size() - 1, maxBits(arr));
	}
private:
	int getDigit(int arr, int d) {
		int ret = 0;
		while (d--) {
			ret = arr % 10;
			arr /= 10;
		}
		return ret;
	}
	//计算arr中最大值的位数
	int maxBits(const vector<int>& arr) {
		int maxNum = *max_element(arr.begin(), arr.end());
		int ret = 0;
		while (maxNum) {
			++ret;
			maxNum /= 10;
		}
		return ret;
	}

	//在arr的[L,R]上排序，最大值有digit位
	void radixSort(vector<int>& arr, int L, int R, int digit) {
		int radix = 10;
		int i = 0, j = 0;
		//有多少个数准备多少个辅助空间
		vector<int> help(R - L + 1);
		for (int d = 1; d <= digit; ++d) {
			vector<int> count(radix);
			for (i = L; i <= R; ++i) {
				//取出arr[i]这个数字d位上的数字 
				j = getDigit(arr[i], d);
				++count[j];
			}
			//前缀和累加	，此时的cout[i]代表d位数上小于等于i的数字有几个
			for (i = 1; i < radix; ++i) {
				count[i] += count[i - 1];
			}
			//从右往左遍历，因为我们知道d位数上小于等于i的数字有几个，但并不知道具体在什么位置，
			//只知道从右往左遍历到的一定是那几个中的最后一个
			for (i = R; i >= L; --i) {
				j = getDigit(arr[i], d);
				help[count[j] - 1] = arr[i];
				--count[j];
			}
			//将help拷贝回arr
			for (i = L, j = 0; i <= R; ++i, ++j) {
				arr[i] = help[j];
			}
		}
	}
};


int main()
{
	int testTime = 100000;
	int maxValue = 1000;
	srand(time(NULL));

	vector<int> ret1;
	for (int i = 0; i < testTime; ++i) {
		ret1.push_back(rand() % maxValue);
	}
	//ret1 = { 3,6,1,7,2,8 };
	vector<int> ret2 = ret1;
	vector<int> ret3 = ret1;

	CountSort c;
	RadixSort r;
	c.countSortNoStable(ret1);
	c.countSortStable(ret2);
	r.radixSort(ret3);

	if (ret1 == ret2 && ret2 == ret3) {
		cout << "succeed!" << endl;
	}
	return 0;
}
//稳定性
//稳定：插入（相等时不替换）,冒泡排序（相等时不替换），归并排序（相等时先拷贝左边），计数排序，基数排序
//不稳点：选择排序，快排（patition时)，堆排(建堆时）

//总结
//1)不基于比较的排序，对样本数据有严格要求，不易改写
//2）基于比较的排序，只要规定好两个样本怎么比大小就可以直接复用
//3）基于比较的排序，时间复杂度的极限是O(N * logN)
//4)时间复杂度O(N* logN)、额外空间复杂度低于O(N)、且稳定的基于比较的排序是不存在的。
//5）为了绝对的速度选快排、为了省空间选堆排、为了稳定性选归并

//常见的坑
//1）归并排序的额外空间复杂度可以变成O(1)，“归并排序内部缓存法"，但将变得不再稳定。
//2)“原地归并排序"是垃圾贴，会让时间复杂度变成O(N个2)
//3）快速排序稳定性改进, “O1 stable sort"，但是会对样本数据要求更多。

//在整型数组中，请把奇数放在数组左边，偶数放在数组右边，要求所有奇数之间原始的相对次序不变，所有偶数之间原始相对次序不变。
//时间复杂度做到O(N)，额外空间复杂度做到O(1)
//以上问题属于标准的01partition问题，如果能做到稳定排序，那么为什么快排不改成稳定的，因为没必要，
//虽然可以做到，但对数据样本有严格要求，那这样的话为什么不用桶排序，多此一举


