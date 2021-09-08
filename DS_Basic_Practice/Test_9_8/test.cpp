//leetcode���ݽṹ����ѵ��

//����
//169. ����Ԫ��
#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<map>
#include<algorithm>
//��һ������ӳ��
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int index = nums.size() / 2;
        if (!index)
            return nums[0];
        map<int, int> m;
        for (auto num : nums)
        {
            if (m.find(num) != m.end())
            {
                m[num]++;
                if (m[num] > index)
                {
                    return num;
                }
               
            }
            else
            {
                m.insert(make_pair(num, 1));
            }
        }
        return -1;
    }
};

//�������Ż�����ʱ����С
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int index = nums.size() / 2;
        if (!index)
            return nums[0];
        map<int, int> m;
        for (auto num : nums)
        {
            ++m[num];//������û��num,��<num,0>���룬�ٶ�ֵ+1
            if (m[num] > index)
            {
                return num;
            }
        }
        return -1;
    }
};

//��������������������������n/2�������±�n/2����Ӧ��Ԫ�ؼ���
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

//���ģ������
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        while (true) {
            int candidate = nums[rand() % nums.size()];
            int count = 0;
            for (int num : nums)
                if (num == candidate)
                    ++count;
            if (count > nums.size() / 2)
                return candidate;
        }
        return -1;
    }
};
//����Ƚ�����˼���������һֱ���õĻ�������һֱ�Ҳ�������ѭ������������ѧ�������㣬����ֵΪ2��˵����������������ǳ�����
//��������ʱ�临�Ӷ�O��N��,�ռ临�Ӷ�O(1)

//���壺�����㷨�ݹ����
class Solution {
    int count_in_range(vector<int>& nums, int target, int lo, int hi) {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }
    int majority_element_rec(vector<int>& nums, int lo, int hi) {
        if (lo == hi)
            return nums[lo];
        int mid = (lo + hi) / 2;
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};

//��������Boyer-Moore ͶƱ�㷨
//������
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = -1;
        int count = 0;
        for (int num : nums) {
            if (num == candidate)
                ++count;
            else if (--count < 0) {
                candidate = num;
                count = 1;
            }
        }
        return candidate;
    }
};

//15. ����֮��
//����˫ָ��
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // ö�� a
        for (int first = 0; first < n; ++first) {
            // ��Ҫ����һ��ö�ٵ�������ͬ
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c ��Ӧ��ָ���ʼָ����������Ҷ�
            int third = n - 1;
            int target = -nums[first];
            // ö�� b
            for (int second = first + 1; second < n; ++second) {
                // ��Ҫ����һ��ö�ٵ�������ͬ
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // ��Ҫ��֤ b ��ָ���� c ��ָ������
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // ���ָ���غϣ����� b ����������
                // �Ͳ��������� a+b+c=0 ���� b<c �� c �ˣ������˳�ѭ��
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({ nums[first], nums[second], nums[third] });
                }
            }
        }
        return ans;
    }
};
