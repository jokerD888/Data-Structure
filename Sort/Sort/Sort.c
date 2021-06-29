#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#include"stack.h"
//以下皆为升序
//插入排序
// 时间复杂度O(N^2),逆序是最坏的情况，顺序最好O(N)	 稳定
//(升序）
void InsertSort(int* a, int n)
{
	
	//[0,end]有序，end+1位置的值插入[0,end],使[0,end+1]有序
	for (int i = 0; i < n - 1; ++i)
	{
		int end = i;
		int tmp = a[end + 1];	
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
		}

		a[end + 1] = tmp;//无论是插入到第一个（走完了）还是插入到中间的某个位置都可完成插入
	}
}


//希尔排序（直接插入排序的基础上的优化）
//1.先进行预排序，让数组接近有序
//2.直接插入排序·
//预排序：分组排，间隔为gap的是一组，gap越大，大的数可以越快的到达后面，小的数可以越快的到达前面，
//gap越大，排序完越不接近有序，gap越小，越接近有序，gap=1就是直接插入排序

//时间复杂度：O((log2N*N))或者O((log3N)*N)  不稳定
//平均时间复杂度为O(N^1.3)
void ShellSort(int* a, int n)
{
	int gap=n;

	while (gap > 1)
	{
		//gap /= 2;//时间复杂度log2N
		gap = gap / 3 + 1;//时间复杂度log3N


		//gap很大时，一次排序时间复杂度为O（N）
		//gap很小时，数组已接近有序，这时差不多也是O(N)
		//把间隔为gap的多组数据同时排

		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}

	}
}

//堆排序 
// 整体时间复杂度O(N*logN)  不稳定
//小堆堆顶最小，大堆堆顶最大
//选择排序，通过堆来选数
//排升序，建大堆还是小堆？
//如是是建小堆，最小数在堆顶，已经被选出来了，那么在剩下的数中再去选数，但是剩下的数结构都乱了，需要重新建堆才能选出下一个数，建堆的时间复杂度是O（N），若是如此堆排序就没有效率优势
//所以升序建大堆，降序建小堆
//升序：先建大堆，把第一个和最后一个交换，把它从堆中去除（即n--)，前n-1个数向下调整，选出次大数，再跟倒数第二个位置交换
//各个数字在物理内存中是按数组形式存放的
void Swap(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}
//向下调整，时间复杂度为O(log2N)
void  AdjustDown(int* a, int n,int root)
{
	int parent = root;
	int child = parent * 2 + 1;//默认左孩子
	//从结点开始，选出左右孩子中小的那一个，跟父亲比较，若是比父亲小就交换，然后再继续往下调，调到叶子就终止
	while (child<n)
	{
		if (child+1<n &&a[child + 1] > a[child])//大堆
		{
			++child;
		}
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}


}
void HeapSort(int* a, int n)
{
	//把数组建成小堆
	//（向下调整算法，前提：左右子树都是小堆）
	//如果左右子树不是小堆，就不能直接使用向下调整算法
	//则应该倒着从最后一颗子树开始调（从最后一个非叶子子树开始调）
	//建堆时间复杂度为O(N)  (N-logN)

	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	//调整堆的时间复杂度为O(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}

}


//直接选择排序
//O(N*N) 不稳定

void SelectSort(int* a,int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = begin;
		for (int i = begin; i <= end; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;
			}

			if (a[i] > a[maxi])
			{
				maxi = i;
			}
		}

		Swap(&a[begin], &a[mini]);
		//如果begin和maxi重叠，需要修正
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);

		++begin;
		--end;

	}
}


//冒牌排序
// 相比与直接插入排序，直接插入排序更好
// 如，部分有序排序，1 2 3 5 4 6 冒泡排序N-1+N-2 直接插入排序 N
//O(N*N) 稳定
void BubbleSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int exchange = 0;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(&a[j], &a[j + 1]);
				exchange = 1;
			}
		}

		if (exchange == 0)
			break;
	}

	//或
	//int end = n;
	//while (end > 0)
	//{
	//	for (int i = 1; i < end; ++i)
	//	{
	//		if (a[i - 1] > a[i])
	//		{
	//			Swap(&a[i - 1], &a[i]);
	//		}
	//	}

	//	--end;
	//}
}


//快速排序
//最好的情况（二分）O(N*logN)  不稳定
//最坏的情况（顺序）O(N*N),速度极慢，与插入排序速率相差不大，解决方法->三数取中
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) >> 1;
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
			return mid;
		else if (a[left] > a[right])
			return left;
		else
			return right;

	}
	else//a[left] > a[mid]
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] < a[right])
			return left;
		else
			return right;
	}
}
//挖坑法
int PartSort1(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//三数取中
	Swap(&a[left], &a[index]);
	int begin = left, end = right;
	int pivot = begin;
	int key = a[begin];

	//单趟排序O（N）
	while (begin < end)
	{
		//右边找小，放到左边
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		//小的放到左边的坑位，自己形成新的坑位
		a[pivot] = a[end];
		pivot = end;

		//左边找大，放到右边
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//大的放到左边的坑位，自己形成新的坑位
		a[pivot] = a[begin];
		pivot = begin;
	}

	pivot = begin;
	a[pivot] = key;

	return pivot;
}
//挖坑法的变形（左右指针法）
int PartSort2(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//三数取中
	Swap(&a[left], &a[index]);
	int begin = left, end = right;
	int keyi = begin;

	while (begin < end)
	{
		//找小
		while (begin < end && a[end] >= a[keyi])
		{
			--end;
		}

		//找大
		while (begin < end && a[begin] <= a[keyi])
		{
			++begin;
		}
	
		Swap(&a[begin], &a[end]);
	}

	Swap(&a[begin], &a[keyi]);//交换key与begin end相遇位置的数

	return begin;


}
//前后指针法
int PartSort3(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//三数取中
	Swap(&a[left], &a[index]);

	int keyi = left;
	int prev = left;
	int cur = left + 1;

	while (cur <= right)
	{
		if (a[cur] < a[keyi] && ++prev!=cur)
		{
			Swap(&a[cur], &a[prev]);
		}

		++cur;
	}

	Swap(&a[keyi], &a[prev]);
	return prev;
}

void QuickSort(int* a, int left, int right)
{
	if (left >= right)
		return;
	
	//int keyIndex = PartSort1(a, left, right);//各种单趟排序的结果可能不同
	//int keyIndex = PartSort2(a, left, right);
	int keyIndex = PartSort3(a, left, right);


	//[left,right]
	//[left,keyIndex-1] keyIndex [keyIndex+1,right]
	//左子区间和右子区间有序就有序了，分治递归

	//小区间优化
	if (keyIndex - 1 - left > 10)
	{
		QuickSort(a, left, keyIndex - 1);
	}
	else
	{
		InsertSort(a + left, keyIndex - 1 - left + 1);
	}

	if (right - (keyIndex + 1) > 10)
	{
		QuickSort(a, keyIndex + 1, right);
	}
	else
	{
		InsertSort(a + keyIndex + 1, right - (keyIndex + 1) + 1);
	}

}

//递归的缺陷：栈帧深度太深，栈空间可能不够用，可能会溢出
//非递归：
//递归改非递归：1.直接改循环（简单情况下）2.借助数据结构栈模拟递归过程（稍复杂）
void QuickSortNonR(int* a, int n)
{
	ST st;
	StackInit(&st);
	StackPush(&st, n - 1);
	StackPush(&st, 0);

	while (!StackEmpty(&st))
	{
		int left = StackTop(&st);
		StackPop(&st);

		int right = StackTop(&st);
		StackPop(&st);

		int keyIndex = PartSort1(a, left, right);
		//[left,keyIndex-1] keyIndex [keyIndex+1,right]

		if (keyIndex + 1 < right)
		{
			StackPush(&st, right);
			StackPush(&st, keyIndex+1);
		}
		if (left < keyIndex - 1)
		{
			StackPush(&st, keyIndex-1);
			StackPush(&st, left);
		}
	}



	StackDestory(&st);
}
//归并排序 
//时间复杂度O（N*logN) 稳定
//左半边区间有序 有半边区间有序
//归并，依次对比取小的放到新的临时数组
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;

	int mid = (left + right) >> 1;
	//使[left,mid] [mid,right]有序
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);

	//[left,mid] [mid,right]有序，就可以归并

	int begin1 = left, end1 = mid;
	int begin2 = mid+1, end2 = right;
	int index = left;
	//归并到临时数组
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];

		}
	}

	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];

	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];

	}

	//拷贝回原数组
	for (int i=left;i <= right; i++)
	{
		a[i] = tmp[i];
	}
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

//归并非递归
//时间复杂度O（N*logN)
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);

	int gap = 1;//每组数组的个数
	while (gap < n)
	{

		for (int i = 0; i < n; i += 2 * gap)
		{
			//[i,i+gap-1][i+gap,i+2*gap-1]
			//归并到临时数组
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//归并过程中右半区间可能不存在
			if (begin2 >= n)
				break;
			//归并过程中右半区间算多了，修正一下
			if (end2 >= n)
				end2 = n - 1;


			int index = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[index++] = a[begin1++];
				}
				else
				{
					tmp[index++] = a[begin2++];

				}
			}

			while (begin1 <= end1)
			{
				tmp[index++] = a[begin1++];

			}
			while (begin2 <= end2)
			{
				tmp[index++] = a[begin2++];

			}

			//拷贝回原数组
			for (int j = i; j <= end2; j++)
			{
				a[j] = tmp[j];
			}
		}

		gap *= 2;
	}
	free(tmp);

}
//归并排序也叫外排序，还可以对文件中的数据进行排序（因为磁盘中只能依次读数据，而快排等排序算法需要进行随机读取，因此借助归并的思想即可对磁盘中文件数据进行排序）
//如要对磁盘文件中的10G的数据进行排序，而内存只有1G可用，那么可以分成10个1G文件，各个1G文件的数据进行快排使其有序，
//依次读文件，每次读1G到内存中放到一个数组，用快排对其排序，再写到一个文件，再依次对剩下的9个1G数据进行排序，
//再对有序的10个1G数据文件两两归并写到一个文件，得到5个2G有序数据文件，依次进行排序归并

//计数排序(映射）,非比较排序
//时间复杂度 O(N+range) ,适用于范围集中的一组整型数据排序,局限性
//空间复杂度O（range)
void CountSort(int* a, int n)
{
	int max = a[0], min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = i;
		}
	}

	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		printf("failed malloc!");
		exit(-1);
	}
	memset(count, 0, sizeof(int) * range);
	for (int i = 0; i < n; i++)
	{
		count[a[i]-min]++;//相对映射
	}
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			a[j++] = i + min;
		}
	}
	free(count);
}
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");
}
void TestInsertSort()
{
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	InsertSort(a, sizeof(a)/sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
void TestShellSort()
{
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	ShellSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));

}

void TestHeapSort()
{
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	HeapSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));

}

void TestSelectSort()
{
	int a[] = { 9,3,5,2,7,8,6,-1,9,4,0 };
	BubbleSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
void TestBubbleSort()
{
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	InsertSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
void TestQuickSort()
{
	//int a[] = { 6,3,5,2,7,8,9,4,1 };
	int a[] = { 49,38,65,97,76,13,27,49,13,27,49 };
	//QuickSort(a, 0,sizeof(a) / sizeof(int)-1);
	QuickSortNonR(a,sizeof(a) / sizeof(int) - 1);
	PrintArray(a, sizeof(a) / sizeof(int)); 
}
TestMergeSort()
{
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	//int a[] = { 49,38,65,97,76,13,27,49,13,27,49 };
	//MergeSort(a,sizeof(a) / sizeof(int) );
	MergeSortNonR(a, sizeof(a) / sizeof(int));

	PrintArray(a, sizeof(a) / sizeof(int));
}
TesetCountSort()
{
	int a[] = {105,102,100,106,104,101,100,105,103,109 };
	CountSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));

}


// 测试排序的性能对比
void TestOP()
{
	srand(time(0));
	const int N = 1000000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];

	}
	/*int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();*/

	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();

	/*int begin3 = clock();
	SelectSort(a3, N);
	int end3 = clock();*/

	int begin4 = clock();
	HeapSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	//QuickSort(a5, 0, N - 1);
	QuickSortNonR(a5, N);
	int end5 = clock();

	int begin6 = clock();
	MergeSortNonR(a6, N);
	//MergeSort(a6, N);
	int end6 = clock();

	/*int begin7 = clock();
	BubbleSort(a7, N);
	int end7 = clock();*/

	//printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	//printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	printf("QuickSort:%d\n", end5 - begin5);
	printf("MergeSort:%d\n", end6 - begin6);
	//printf("BubbleSort:%d\n", end7 - begin7);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);

}

int main(void)
{
	TestOP();
	//TestInsertSort();
	//TestShellSort();
	//TestHeapSort();
	/*TestSelectSort();
	TestBubbleSort();*/
	//TestQuickSort();
	//TestMergeSort();
	TesetCountSort();
	return 0;
}
