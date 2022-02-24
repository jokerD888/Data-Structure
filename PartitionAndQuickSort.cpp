
class PartitionAndQuickSort {
public:
	int partition(vector<int>& arr, int L, int R) {
		if (L > R) {
			return -1;
		}
		if (L == R) {
			return L;
		}
		int lessEqual = L - 1;
		int index = L;
		while (index < R) {
			//左边界向右挤
			if (arr[index] <= arr[R]) {
				swap(arr[index], arr[++lessEqual]);
			}
			++index;
		}
		swap(arr[++lessEqual], arr[R]);
		return lessEqual;
	}

	//快排1.0	O(N*2)
	void quickSort1(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		process1(arr, 0, arr.size() - 1);
	}
	void process1(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		int M = partition(arr, L, R);
		process1(arr, L, M - 1);
		process1(arr, M+1, R);
	}

	//快排2.0	按最坏即有序情况下O(N*2)
	void quickSort2(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		process2(arr, 0, arr.size() - 1);
	}
	void process2(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		auto equalArea=equalOnMid(arr, L, R);
		process2(arr, L, equalArea.first-1);
		process2(arr, equalArea.second+1,R);
	}
	//荷兰国旗问题，相等的分割点都一起放在中间 
	//返回相等分割点的左右边界
	pair<int,int> equalOnMid(vector<int>& arr, int L, int R) {
		if (L > R) {
			return { -1,-1 };
		}
		if (L == R) {
			return { L,R };
		}
		int less = L - 1;
		int more = R;
		int index = L;
		while (index < more) {
			if (arr[index] == arr[R]) {
				++index;
			} else if (arr[index] < arr[R]) {
				swap(arr[index++], arr[++less]);
			} else {
				swap(arr[index], arr[--more]);
			}
		}
		swap(arr[more], arr[R]);
		return { less + 1,more };
	}
	

	//快排3.0	时间O(N*logN)	空间O(logN)（好情况下O(logN),坏情况下O(N)）
	void quickSort3(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
 		process3(arr, 0, arr.size() - 1);
	}
	void process3(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return; 
		}
		swap(arr[L + int(rand() % (R - L + 1))], arr[R]);
		auto equalArea = equalOnMid(arr, L, R);
		process2(arr, L, equalArea.first - 1);
		process2(arr, equalArea.second + 1, R);
	}
};

int main() {
	int testTime = 500000;
	int maxValue = 100000;
	bool succeed = true;
	vector<int> ret1;
	srand(time(NULL));

	for (int i = 0; i < testTime; ++i) {
		ret1.push_back(rand() % maxValue);
	}

	PartitionAndQuickSort p;
	vector<int> ret2(ret1.begin(),ret1.end());
	vector<int> ret3(ret1.begin(),ret1.end());
	int begin = clock();
	p.quickSort1(ret1);
	int end = clock();
	cout << "time1:" << end - begin << endl;

	begin = clock();
	p.quickSort2(ret2);
	end = clock();
	cout << "time2:" << end - begin << endl;

	begin = clock();
	p.quickSort3(ret3);
	end = clock();
	cout << "time3:" << end - begin << endl;

	if (ret1 == ret2 && ret2 == ret3) {
		cout << "succeed!" << endl;
	}


	return 0;
}

