
//����
#include<iostream>
using namespace std;
#include<vector>
//75. ��ɫ����
//��һ����ָ�룬���α�������
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int left = 0, right = 0;
		//�ȶ�0��������
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
		//�ٶ�1 �� 2����
		if (left < n)
		{
			right--;
			while (left <= right)
			{
				while (left < right && nums[left] != 2)//��2
					left++;

				while (left < right && nums[right] != 1)//��1
					right--;

				swap(nums[left], nums[right]);
				left++, right--;
			}
		}

	}
};
//����
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
//ʱ�䣺O��N)
//�ռ䣺O��1��
//������˫ָ��
//p0��������0��p1��������1������0ʱ��p0,p1��Ҫ�����ƣ�����1�ǣ�ֻ�ƶ�p1��
//������0ʱ��p0<p1˵����p0��ָ��Ԫ��Ϊ1��������1�ܵ�����ȡ�ˣ���Ҫ��p1����һ��
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

//ʱ�䣺O��N)
//�ռ䣺O��1��
//������p0������0��p2����2��p0����ʼ��p2���ҿ�ʼ�����������
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
//ʱ�䣺O��N)
//�ռ䣺O��1��

//�������������� partition�����ѭ��������
//��ʽ1
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int size = nums.size();
		if (size < 2) {
			return;
		}

		// all in [0, zero) = 0
		// all in [zero, i) = 1
		// all in ��two, len - 1] = 2

		int zero = 0;       //��ʼʱ��Ҫ���������䶼Ϊ��
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

//��ʽ2
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