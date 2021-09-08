//leetcode数据结构基础训练

//数组
//169. 多数元素
#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<map>
#include<algorithm>
//法一：利用映射
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

//法二：优化，耗时大大减小
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int index = nums.size() / 2;
        if (!index)
            return nums[0];
        map<int, int> m;
        for (auto num : nums)
        {
            ++m[num];//若表中没有num,则将<num,0>插入，再对值+1
            if (m[num] > index)
            {
                return num;
            }
        }
        return -1;
    }
};

//法三：排序，因众数的数量大于n/2，返回下标n/2所对应的元素即可
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

//法四：随机化
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
//这个比较有意思，如果运气一直不好的话，将会一直找不到进行循环，但进行数学期望运算，期望值为2，说明期望的随机次数是常数。
//即可满足时间复杂度O（N）,空间复杂度O(1)

//法五：分治算法递归求解
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

//方法六：Boyer-Moore 投票算法
//很巧妙
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

//15. 三数之和
//排序，双指针
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
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
