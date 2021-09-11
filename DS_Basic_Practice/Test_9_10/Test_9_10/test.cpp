
//数组
#include<iostream>
using namespace std;
#include<vector>
//75. 颜色分类
//法一，单指针，两次遍历排序
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int left = 0, right = 0;
		//先对0进行排序
		while (right < n && left < n)
		{
			while (left < n && nums[left] == 0)
				left++;

			right = left + 1;
			while (right < n && nums[right] != 0)
				right++;

			if (right < n && left < n)
			{
				swap(nums[left], nums[right]);
				left++, right++;
			}
		}
		//再对1 和 2排序
		if (left < n)
		{
			right--;
			while (left <= right)
			{
				while (left < right && nums[left] != 2)//找2
					left++;

				while (left < right && nums[right] != 1)//找1
					right--;

				swap(nums[left], nums[right]);
				left++, right--;
			}
		}

	}
};
//类似
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int ptr = 0;
		for (int i = 0; i < n; ++i) {
			if (nums[i] == 0) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
		for (int i = ptr; i < n; ++i) {
			if (nums[i] == 1) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
	}
};
//时间：O（N)
//空间：O（1）
//法二：双指针
//p0用来交换0，p1用来交换1，交换0时，p0,p1都要往后移，交换1是，只移动p1，
//若交换0时，p0<p1说明，p0所指的元素为1，交换后，1跑到后面取了，再要和p1交换一次
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int p0 = 0, p1 = 0;
		for (auto& num : nums)
		{
			if (num == 0)
			{
				swap(num, nums[p0]);
				if (p0 < p1)
					swap(num, nums[p1]);

				p0++, p1++;
			}
			else if (num == 1)
				swap(num, nums[p1++]);

		}
	}
};

//时间：O（N)
//空间：O（1）
//或者用p0来交换0，p2交换2，p0从左开始，p2从右开始，更容易理解
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int p0 = 0, p2 = n - 1;
		for (int i = 0; i <= p2; ++i) {
			while (i <= p2 && nums[i] == 2) {
				swap(nums[i], nums[p2]);
				--p2;
			}
			if (nums[i] == 0) {
				swap(nums[i], nums[p0]);
				++p0;
			}
		}
	}
};
//时间：O（N)
//空间：O（1）

//法三：快速排序 partition，设计循环不变量
//型式1
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int size = nums.size();
		if (size < 2) {
			return;
		}

		// all in [0, zero) = 0
		// all in [zero, i) = 1
		// all in （two, len - 1] = 2

		int zero = 0;       //开始时，要让三个区间都为空
		int two = size-1;
		int i = 0;
		while (i <= two) {
			if (nums[i] == 0) {
				swap(nums[zero], nums[i]);
				zero++;
				i++;
			}
			else if (nums[i] == 1) {
				i++;
			}
			else {
				swap(nums[i], nums[two]);
				two--;
			}
		}
	}
};

//型式2
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int size = nums.size();
		if (size < 2) {
			return;
		}

		//all in (0, zero] = 0
		//all in (zero, i) = 1
		//all in [two, len - 1] = 2

		int zero = -1;
		int two = size;
		int i = 0;  

		while (i < two) {
			if (nums[i] == 0) {
				zero++;
				swap(nums[zero], nums[i]);
				i++;
			}
			else if (nums[i] == 1) {
				i++;
			}
			else {
				two--;
				swap(nums[i], nums[two]);
		
			}
		}
	}
};

int main(void)
{
	return 0;
}