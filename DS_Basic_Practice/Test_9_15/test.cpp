//����

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//240. ������ά���� II

//��һ��
//�����Ͻǿ�ʼ���������������Ŀ�������Ͻ�Ԫ��������������С�������������
//����Ԫ�ر�targetС���������ߣ�����һ�¿��Լ���һ�еĲ��ң����ݴ��ص���ѡ���Բ��ң��������нϴ��ʱ
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
////ʱ�临�Ӷ��O(m*n)
////�ռ临�Ӷ�O(1)
//
////������
////�Է�һ�Ż�����һ��ȱ���ǵ������Ͻ���������У�һ�����ִ�Ԫ��С�ڵ���ʱ����ֻ�ܶ������󲿷ֵ�Ԫ�ض�����һ�顣
////�Ż�:���ð��е��������е����ص㣬ʹ�������в���ʱ���ִ�Ԫ��>targetʱ���������ߣ����ɱ�����Ч���ң�����O(m+n�����ҳ����
//class Solution {
//public:
//    bool searchMatrix(vector<vector<int>>& matrix, int target) {
//        //�����Ͻǿ�ʼ����ѡ���½ǿ�ʼҲ�У�
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
////ʱ�临�Ӷ�O(m+n)
////�ռ临�Ӷ�O(1)
//
//
//
////435. ���ص�����
////��һ��
////��̬�滮
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
////������
////̰���㷨
//class Solution {
//public:
//    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
//        if (intervals.empty()) {
//            return 0;
//        }
//        //���Ҷ˵�����
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

//334. ��������Ԫ������

//��һ������
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        //nums.size()���ص����޷�������������ֱ��-2����
        //�з��Ÿ��޷��űȽϻ��������޷��ţ������Ǹ�-1ʱ�����޷��Ż���һ���ܴ��ֵ
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