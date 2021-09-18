//数组

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//240. 搜索二维矩阵 II

//法一：
//从由上角开始向左遍历，根据题目规则，右上角元素在所在列中最小，在所在行最大，
//若此元素比target小，就往左走，这样一下可以减少一列的查找，根据此特点做选择性查找，但还是有较大耗时
//class Solution {
//public:
//    bool searchMatrix(vector<vector<int>>& matrix, int target) {
//        for (int i = matrix[0].size() - 1; i >= 0; i--) {
//            if (target >= matrix[0][i]) {
//                for (int j = 0; j < matrix.size(); j++) {
//                    if (matrix[j][i] == target) {
//                        return true;
//                    }
//                }
//            }
//        }
//        return false;
//    }
//};
////时间复杂度最坏O(m*n)
////空间复杂度O(1)
//
////法二：
////对法一优化，法一的缺陷是当从右上角向左遍历中，一旦发现此元素小于等于时，便只能对整个左部分的元素都遍历一遍。
////优化:利用按行递增，案列递增特点，使得在列中查找时发现此元素>target时，便向左走，即可避免无效查找，可在O(m+n）内找出结果
//class Solution {
//public:
//    bool searchMatrix(vector<vector<int>>& matrix, int target) {
//        //从右上角开始，（选左下角开始也行）
//        int row = 0, col = matrix[0].size()-1;
//        while (row <= matrix.size() && col >= 0) {
//            if (target < matrix[row][col]) {
//                col--;
//            } else if (target > matrix[row][col]) {
//                row++;
//            } else {
//                return true;
//            }
//        }
//        return false;
//    }
//};
//
////时间复杂度O(m+n)
////空间复杂度O(1)
//
//
//
////435. 无重叠区间
////法一：
////动态规划
//
//class Solution {
//public:
//    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
//        if (intervals.empty()) {
//            return 0;
//        }
//
//        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
//            return u[0] < v[0];
//            });
//
//        int n = intervals.size();
//        vector<int> f(n, 1);
//        for (int i = 1; i < n; ++i) {
//            for (int j = 0; j < i; ++j) {
//                if (intervals[j][1] <= intervals[i][0]) {
//                    f[i] = max(f[i], f[j] + 1);
//                }
//            }
//        }
//        return n - *max_element(f.begin(), f.end());
//    }
//};
//
//
////法二：
////贪心算法
//class Solution {
//public:
//    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
//        if (intervals.empty()) {
//            return 0;
//        }
//        //按右端点排序
//        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
//            return u[1] < v[1];
//            });
//
//        int n = intervals.size();
//        int right = intervals[0][1];
//        int ans = 1;
//        for (int i = 1; i < n; ++i) {
//            if (intervals[i][0] >= right) {
//                ++ans;
//                right = intervals[i][1];
//            }
//        }
//        return n - ans;
//    }
//};
//

//334. 递增的三元子序列

//法一：暴力
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        //nums.size()返回的是无符号整数，若是直接-2，则
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
int main(void) {
    Solution s;

    vector<int> a = { 1 };
    s.increasingTriplet(a);
    return 0;
}


//class Solution {
//public:
//    bool increasingTriplet(vector<int>& nums) {
//        vector<int> ans(4, 0);
//        ans[0] = 1;
//        ans[1] = nums[0];
//        // 2 1 5 0 4 6
//        for (int i = 1; i < nums.size(); i++) {
//            if (nums[i] > ans[ans[0]]) {
//                ans[0]++;
//                ans[ans[0]] = nums[i];
//                if (ans[0] == 3) {
//                    return true;
//                }
//            } else {
//                if (ans[0] > 1 && nums[i] > ans[ans[0]-1]) {
//                    ans[ans[0]] = nums[i];
//                } else if (ans[0] == 1) {
//                    ans[ans[0]] = nums[i];
//                }
//            }
//        }
//        return false;
//    }
//};