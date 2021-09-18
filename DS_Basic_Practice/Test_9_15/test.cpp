//数组

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_map>
//240. 搜索二维矩阵 II

//法一：
//从由上角开始向左遍历，根据题目规则，右上角元素在所在列中最小，在所在行最大，
//若此元素比target小，就往左走，这样一下可以减少一列的查找，根据此特点做选择性查找，但还是有较大耗时
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = matrix[0].size() - 1; i >= 0; i--) {
            if (target >= matrix[0][i]) {
                for (int j = 0; j < matrix.size(); j++) {
                    if (matrix[j][i] == target) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
//时间复杂度最坏O(m*n)
//空间复杂度O(1)

//法二：
//对法一优化，法一的缺陷是当从右上角向左遍历中，一旦发现此元素小于等于时，便只能对整个左部分的元素都遍历一遍。
//优化:利用按行递增，案列递增特点，使得在列中查找时发现此元素>target时，便向左走，即可避免无效查找，可在O(m+n）内找出结果
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //从右上角开始，（选左下角开始也行）
        int row = 0, col = matrix[0].size()-1;
        while (row <= matrix.size() && col >= 0) {
            if (target < matrix[row][col]) {
                col--;
            } else if (target > matrix[row][col]) {
                row++;
            } else {
                return true;
            }
        }
        return false;
    }
};

//时间复杂度O(m+n)
//空间复杂度O(1)



//435. 无重叠区间
//法一：
//动态规划

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[0] < v[0];
            });

        int n = intervals.size();
        vector<int> f(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (intervals[j][1] <= intervals[i][0]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
        }
        return n - *max_element(f.begin(), f.end());
    }
};


//法二：
//贪心算法
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        //按右端点排序
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
            });

        int n = intervals.size();
        int right = intervals[0][1];
        int ans = 1;
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= right) {
                ++ans;
                right = intervals[i][1];
            }
        }
        return n - ans;
    }
};


//334. 递增的三元子序列

//法一：暴力
//最后一个案列超时
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        //nums.size()返回的是无符号整数，若是直接-2，则结果是无符号，有符号和无符号运算会做类型提升
        //有符号跟无符号比较会提升成无符号，所以那个-1时看做无符号会是一个很大的值
        cout << nums.size() - 2;
        for (int i = 0; i < n -2; i++) {
            int count_num = 1;
            int tmp = nums[i], prev = nums[i];  
            for (int j = i+1; j < nums.size(); j++) {
                if (nums[j] > tmp) {
                    count_num++;
                    prev = tmp;
                    tmp = nums[j];
                    if (count_num == 3) {
                        return true;
                    }
                } else if (nums[j] < tmp && nums[j]>prev) {
                    tmp = nums[j];
                }
            }
        }
        return false;
    }
};


//法二：
//利用if else 的相异的特性，巧妙的判断了大小关系和顺序关系
//two附带隐含信息——这之前有个数比two小,所以此时找到的递增子序列不是one、two、three的1 5 6，而是old one、two、three的2 5 6。
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int one = INT_MAX, two = INT_MAX;
        for (int three : nums) {
            if (three > two) return true;
            else if (three <= one) one = three;     //更新one，赋值为这个更小的值。而不需要动two, 这相当于帮我们扩大了之后出现的two的可选择范围。进而扩大了之后出现的three的可选择范围。
            else two = three;       //应更新two，赋值为这个更小的值,这相当于帮我们扩大了three的可选择范围，当再次遇到一个比更新过的two大的数即可找到。
            // if(three > one && three < two) two = three;
        }
        return false;
    }
};



//238. 除自身以外数组的乘积
//法一：全部初始化为数组乘积，然后遍历数组除以当前元素，对于0则特殊处理
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int total = 1;
        for (auto nu : nums) {
            total *= nu;
        }
        vector<int> ans(nums.size(), total);

        for (int i = 0; i < nums.size(); i++) {
            if (!nums[i]) {
                int sum1 = 1;
                for (int j = 0; j < nums.size(); j++) {
                    if (j != i) {
                        sum1 *= nums[j];
                    }
                }
                ans[i] = sum1;
            } else {
                ans[i] /= nums[i];
            }
        }
        return ans;
    }
};

//法二：
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();

        // L 和 R 分别表示左右两侧的乘积列表
        vector<int> L(length, 0), R(length, 0);

        vector<int> answer(length);

        // L[i] 为索引 i 左侧所有元素的乘积
        // 对于索引为 '0' 的元素，因为左侧没有元素，所以 L[0] = 1
        L[0] = 1;
        for (int i = 1; i < length; i++) {
            L[i] = nums[i - 1] * L[i - 1];
        }

        // R[i] 为索引 i 右侧所有元素的乘积
        // 对于索引为 'length-1' 的元素，因为右侧没有元素，所以 R[length-1] = 1
        R[length - 1] = 1;
        for (int i = length - 2; i >= 0; i--) {
            R[i] = nums[i + 1] * R[i + 1];
        }

        // 对于索引 i，除 nums[i] 之外其余各元素的乘积就是左侧所有元素的乘积乘以右侧所有元素的乘积
        for (int i = 0; i < length; i++) {
            answer[i] = L[i] * R[i];
        }

        return answer;
    }
};

//法三：
//优化法二，将答案数组与左索引数组集合，省去一个数组
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> answer(length);

        // answer[i] 表示索引 i 左侧所有元素的乘积
        // 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        // R 为右侧所有元素的乘积
        // 刚开始右边没有元素，所以 R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) {
            // 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
            answer[i] = answer[i] * R;
            // R 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
            R *= nums[i];
        }
        return answer;
    }
};



//560. 和为 K 的子数组

//法一：
//暴力
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0, first = 0, second = 0;
        for (int i = 0; i < nums.size(); i++) {
            int total = 0;
            for (int j = i; j < nums.size(); j++) {
                total += nums[j];
                if (total == k) {
                    ans++;
                } 
            }
        }
        return ans;
    }
};


//法二：前缀和 + 哈希表优化
//利用前缀和来避免累计运算，只需对应下标运算即可，又结果只关注个数，可用哈希表优化
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x : nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};
