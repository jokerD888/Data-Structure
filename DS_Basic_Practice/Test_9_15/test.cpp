//����

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_map>
//240. ������ά���� II

//��һ��
//�����Ͻǿ�ʼ���������������Ŀ�������Ͻ�Ԫ��������������С�������������
//����Ԫ�ر�targetС���������ߣ�����һ�¿��Լ���һ�еĲ��ң����ݴ��ص���ѡ���Բ��ң��������нϴ��ʱ
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
//ʱ�临�Ӷ��O(m*n)
//�ռ临�Ӷ�O(1)

//������
//�Է�һ�Ż�����һ��ȱ���ǵ������Ͻ���������У�һ�����ִ�Ԫ��С�ڵ���ʱ����ֻ�ܶ������󲿷ֵ�Ԫ�ض�����һ�顣
//�Ż�:���ð��е��������е����ص㣬ʹ�������в���ʱ���ִ�Ԫ��>targetʱ���������ߣ����ɱ�����Ч���ң�����O(m+n�����ҳ����
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //�����Ͻǿ�ʼ����ѡ���½ǿ�ʼҲ�У�
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

//ʱ�临�Ӷ�O(m+n)
//�ռ临�Ӷ�O(1)



//435. ���ص�����
//��һ��
//��̬�滮

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


//������
//̰���㷨
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        //���Ҷ˵�����
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


//334. ��������Ԫ������

//��һ������
//���һ�����г�ʱ
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        //nums.size()���ص����޷�������������ֱ��-2���������޷��ţ��з��ź��޷������������������
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


//������
//����if else ����������ԣ�������ж��˴�С��ϵ��˳���ϵ
//two����������Ϣ������֮ǰ�и�����twoС,���Դ�ʱ�ҵ��ĵ��������в���one��two��three��1 5 6������old one��two��three��2 5 6��
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int one = INT_MAX, two = INT_MAX;
        for (int three : nums) {
            if (three > two) return true;
            else if (three <= one) one = three;     //����one����ֵΪ�����С��ֵ��������Ҫ��two, ���൱�ڰ�����������֮����ֵ�two�Ŀ�ѡ��Χ������������֮����ֵ�three�Ŀ�ѡ��Χ��
            else two = three;       //Ӧ����two����ֵΪ�����С��ֵ,���൱�ڰ�����������three�Ŀ�ѡ��Χ�����ٴ�����һ���ȸ��¹���two����������ҵ���
            // if(three > one && three < two) two = three;
        }
        return false;
    }
};



//238. ��������������ĳ˻�
//��һ��ȫ����ʼ��Ϊ����˻���Ȼ�����������Ե�ǰԪ�أ�����0�����⴦��
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

//������
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();

        // L �� R �ֱ��ʾ��������ĳ˻��б�
        vector<int> L(length, 0), R(length, 0);

        vector<int> answer(length);

        // L[i] Ϊ���� i �������Ԫ�صĳ˻�
        // ��������Ϊ '0' ��Ԫ�أ���Ϊ���û��Ԫ�أ����� L[0] = 1
        L[0] = 1;
        for (int i = 1; i < length; i++) {
            L[i] = nums[i - 1] * L[i - 1];
        }

        // R[i] Ϊ���� i �Ҳ�����Ԫ�صĳ˻�
        // ��������Ϊ 'length-1' ��Ԫ�أ���Ϊ�Ҳ�û��Ԫ�أ����� R[length-1] = 1
        R[length - 1] = 1;
        for (int i = length - 2; i >= 0; i--) {
            R[i] = nums[i + 1] * R[i + 1];
        }

        // �������� i���� nums[i] ֮�������Ԫ�صĳ˻������������Ԫ�صĳ˻������Ҳ�����Ԫ�صĳ˻�
        for (int i = 0; i < length; i++) {
            answer[i] = L[i] * R[i];
        }

        return answer;
    }
};

//������
//�Ż��������������������������鼯�ϣ�ʡȥһ������
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> answer(length);

        // answer[i] ��ʾ���� i �������Ԫ�صĳ˻�
        // ��Ϊ����Ϊ '0' ��Ԫ�����û��Ԫ�أ� ���� answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        // R Ϊ�Ҳ�����Ԫ�صĳ˻�
        // �տ�ʼ�ұ�û��Ԫ�أ����� R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) {
            // �������� i����ߵĳ˻�Ϊ answer[i]���ұߵĳ˻�Ϊ R
            answer[i] = answer[i] * R;
            // R ��Ҫ�����ұ����еĳ˻������Լ�����һ�����ʱ��Ҫ����ǰֵ�˵� R ��
            R *= nums[i];
        }
        return answer;
    }
};



//560. ��Ϊ K ��������

//��һ��
//����
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


//������ǰ׺�� + ��ϣ���Ż�
//����ǰ׺���������ۼ����㣬ֻ���Ӧ�±����㼴�ɣ��ֽ��ֻ��ע���������ù�ϣ���Ż�
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
