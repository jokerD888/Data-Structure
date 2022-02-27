#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//Ͱ����˼���µ����� ���������򣬻�������
//ʱ�临�Ӷ�ΪO��N)
//�����ڱȽϵ�����

//��������
//���������ݷ�Χ��С�����
//ʱ��O��N��
class CountSort {
public:
	//Ĭ����С���ݴ�0��ʼ�����ȶ���
	void countSortNoStable(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		int maxNum = INT_MIN;
		//Ѱ�����Ԫ��
		for (int i = 0; i < arr.size(); ++i) {
			maxNum = max(maxNum, arr[i]);
		}
		vector<int> bucket(maxNum + 1);
		//����
		for (int i = 0; i < arr.size(); ++i) {
			++bucket[arr[i]];
		}
		int i = 0;//���¸���ԭ����
		for (int j = 0; j < bucket.size(); ++j) {
			while (bucket[j]--) {
				arr[i++] = j;
			}
		}
		return;
	}

	void countSortStable(vector<int>& arr) {
		//�ҳ������Сֵ
		auto minAndMax = minmax_element(arr.begin(), arr.end());
		int minNum = *minAndMax.first;
		int maxNum = *minAndMax.second;

		//������Χ������
		vector<int> count(maxNum - minNum + 1);
		for (auto n : arr) {
			++count[n - minNum];
		}
		//ǰ׺�ۼ�
		for (int i = 1; i < count.size(); ++i) {
			count[i] += count[i - 1];
		}
		//��ʱ��count[i]��ʾС�ڵ���i���м���
		vector<int> sorted(arr.size());
		for (int i = arr.size() - 1; i >= 0; --i) {
			//�±��0��ʼ����-1
			sorted[count[arr[i] - minNum]-1] = arr[i];
			--count[arr[i] - minNum];
		}
		arr = sorted;
	}

};




//��������
//�����ڷǸ�10�������֣�һ�����ֲ���̫��
//ʱ���ϸ���˵O��N*log10M(��10Ϊ��,��MΪ������MΪԪ�����ֵ))	ͨ����ΪO��N��
class RadixSort {
public:
	void radixSort(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		//����radixSortΪ���������ӹ��̣������б�ͬ
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
	//����arr�����ֵ��λ��
	int maxBits(const vector<int>& arr) {
		int maxNum = *max_element(arr.begin(), arr.end());
		int ret = 0;
		while (maxNum) {
			++ret;
			maxNum /= 10;
		}
		return ret;
	}

	//��arr��[L,R]���������ֵ��digitλ
	void radixSort(vector<int>& arr, int L, int R, int digit) {
		int radix = 10;
		int i = 0, j = 0;
		//�ж��ٸ���׼�����ٸ������ռ�
		vector<int> help(R - L + 1);
		for (int d = 1; d <= digit; ++d) {
			vector<int> count(radix);
			for (i = L; i <= R; ++i) {
				//ȡ��arr[i]�������dλ�ϵ����� 
				j = getDigit(arr[i], d);
				++count[j];
			}
			//ǰ׺���ۼ�	����ʱ��cout[i]����dλ����С�ڵ���i�������м���
			for (i = 1; i < radix; ++i) {
				count[i] += count[i - 1];
			}
			//���������������Ϊ����֪��dλ����С�ڵ���i�������м�����������֪��������ʲôλ�ã�
			//ֻ֪�����������������һ�����Ǽ����е����һ��
			for (i = R; i >= L; --i) {
				j = getDigit(arr[i], d);
				help[count[j] - 1] = arr[i];
				--count[j];
			}
			//��help������arr
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
//�ȶ���
//�ȶ������루���ʱ���滻��,ð���������ʱ���滻�����鲢�������ʱ�ȿ�����ߣ����������򣬻�������
//���ȵ㣺ѡ�����򣬿��ţ�patitionʱ)������(����ʱ��

//�ܽ�
//1)�����ڱȽϵ����򣬶������������ϸ�Ҫ�󣬲��׸�д
//2�����ڱȽϵ�����ֻҪ�涨������������ô�ȴ�С�Ϳ���ֱ�Ӹ���
//3�����ڱȽϵ�����ʱ�临�Ӷȵļ�����O(N * logN)
//4)ʱ�临�Ӷ�O(N* logN)������ռ临�Ӷȵ���O(N)�����ȶ��Ļ��ڱȽϵ������ǲ����ڵġ�
//5��Ϊ�˾��Ե��ٶ�ѡ���š�Ϊ��ʡ�ռ�ѡ���š�Ϊ���ȶ���ѡ�鲢

//�����Ŀ�
//1���鲢����Ķ���ռ临�Ӷȿ��Ա��O(1)�����鲢�����ڲ����淨"��������ò����ȶ���
//2)��ԭ�ع鲢����"��������������ʱ�临�Ӷȱ��O(N��2)
//3�����������ȶ��ԸĽ�, ��O1 stable sort"�����ǻ����������Ҫ����ࡣ

//�����������У������������������ߣ�ż�����������ұߣ�Ҫ����������֮��ԭʼ����Դ��򲻱䣬����ż��֮��ԭʼ��Դ��򲻱䡣
//ʱ�临�Ӷ�����O(N)������ռ临�Ӷ�����O(1)
//�����������ڱ�׼��01partition���⣬����������ȶ�������ôΪʲô���Ų��ĳ��ȶ��ģ���Ϊû��Ҫ��
//��Ȼ�������������������������ϸ�Ҫ���������Ļ�Ϊʲô����Ͱ���򣬶��һ��


