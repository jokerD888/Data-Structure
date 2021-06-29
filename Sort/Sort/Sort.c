#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#include"stack.h"
//���½�Ϊ����
//��������
// ʱ�临�Ӷ�O(N^2),��������������˳�����O(N)	 �ȶ�
//(����
void InsertSort(int* a, int n)
{
	
	//[0,end]����end+1λ�õ�ֵ����[0,end],ʹ[0,end+1]����
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

		a[end + 1] = tmp;//�����ǲ��뵽��һ���������ˣ����ǲ��뵽�м��ĳ��λ�ö�����ɲ���
	}
}


//ϣ������ֱ�Ӳ�������Ļ����ϵ��Ż���
//1.�Ƚ���Ԥ����������ӽ�����
//2.ֱ�Ӳ�������
//Ԥ���򣺷����ţ����Ϊgap����һ�飬gapԽ�󣬴��������Խ��ĵ�����棬С��������Խ��ĵ���ǰ�棬
//gapԽ��������Խ���ӽ�����gapԽС��Խ�ӽ�����gap=1����ֱ�Ӳ�������

//ʱ�临�Ӷȣ�O((log2N*N))����O((log3N)*N)  ���ȶ�
//ƽ��ʱ�临�Ӷ�ΪO(N^1.3)
void ShellSort(int* a, int n)
{
	int gap=n;

	while (gap > 1)
	{
		//gap /= 2;//ʱ�临�Ӷ�log2N
		gap = gap / 3 + 1;//ʱ�临�Ӷ�log3N


		//gap�ܴ�ʱ��һ������ʱ�临�Ӷ�ΪO��N��
		//gap��Сʱ�������ѽӽ�������ʱ���Ҳ��O(N)
		//�Ѽ��Ϊgap�Ķ�������ͬʱ��

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

//������ 
// ����ʱ�临�Ӷ�O(N*logN)  ���ȶ�
//С�ѶѶ���С����ѶѶ����
//ѡ������ͨ������ѡ��
//�����򣬽���ѻ���С�ѣ�
//�����ǽ�С�ѣ���С���ڶѶ����Ѿ���ѡ�����ˣ���ô��ʣ�µ�������ȥѡ��������ʣ�µ����ṹ�����ˣ���Ҫ���½��Ѳ���ѡ����һ���������ѵ�ʱ�临�Ӷ���O��N����������˶������û��Ч������
//�������򽨴�ѣ�����С��
//�����Ƚ���ѣ��ѵ�һ�������һ�������������Ӷ���ȥ������n--)��ǰn-1�������µ�����ѡ���δ������ٸ������ڶ���λ�ý���
//���������������ڴ����ǰ�������ʽ��ŵ�
void Swap(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}
//���µ�����ʱ�临�Ӷ�ΪO(log2N)
void  AdjustDown(int* a, int n,int root)
{
	int parent = root;
	int child = parent * 2 + 1;//Ĭ������
	//�ӽ�㿪ʼ��ѡ�����Һ�����С����һ���������ױȽϣ����Ǳȸ���С�ͽ�����Ȼ���ټ������µ�������Ҷ�Ӿ���ֹ
	while (child<n)
	{
		if (child+1<n &&a[child + 1] > a[child])//���
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
	//�����齨��С��
	//�����µ����㷨��ǰ�᣺������������С�ѣ�
	//���������������С�ѣ��Ͳ���ֱ��ʹ�����µ����㷨
	//��Ӧ�õ��Ŵ����һ��������ʼ���������һ����Ҷ��������ʼ����
	//����ʱ�临�Ӷ�ΪO(N)  (N-logN)

	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	//�����ѵ�ʱ�临�Ӷ�ΪO(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}

}


//ֱ��ѡ������
//O(N*N) ���ȶ�

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
		//���begin��maxi�ص�����Ҫ����
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);

		++begin;
		--end;

	}
}


//ð������
// �����ֱ�Ӳ�������ֱ�Ӳ����������
// �磬������������1 2 3 5 4 6 ð������N-1+N-2 ֱ�Ӳ������� N
//O(N*N) �ȶ�
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

	//��
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


//��������
//��õ���������֣�O(N*logN)  ���ȶ�
//��������˳��O(N*N),�ٶȼ���������������������󣬽������->����ȡ��
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
//�ڿӷ�
int PartSort1(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//����ȡ��
	Swap(&a[left], &a[index]);
	int begin = left, end = right;
	int pivot = begin;
	int key = a[begin];

	//��������O��N��
	while (begin < end)
	{
		//�ұ���С���ŵ����
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		//С�ķŵ���ߵĿ�λ���Լ��γ��µĿ�λ
		a[pivot] = a[end];
		pivot = end;

		//����Ҵ󣬷ŵ��ұ�
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//��ķŵ���ߵĿ�λ���Լ��γ��µĿ�λ
		a[pivot] = a[begin];
		pivot = begin;
	}

	pivot = begin;
	a[pivot] = key;

	return pivot;
}
//�ڿӷ��ı��Σ�����ָ�뷨��
int PartSort2(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//����ȡ��
	Swap(&a[left], &a[index]);
	int begin = left, end = right;
	int keyi = begin;

	while (begin < end)
	{
		//��С
		while (begin < end && a[end] >= a[keyi])
		{
			--end;
		}

		//�Ҵ�
		while (begin < end && a[begin] <= a[keyi])
		{
			++begin;
		}
	
		Swap(&a[begin], &a[end]);
	}

	Swap(&a[begin], &a[keyi]);//����key��begin end����λ�õ���

	return begin;


}
//ǰ��ָ�뷨
int PartSort3(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);//����ȡ��
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
	
	//int keyIndex = PartSort1(a, left, right);//���ֵ�������Ľ�����ܲ�ͬ
	//int keyIndex = PartSort2(a, left, right);
	int keyIndex = PartSort3(a, left, right);


	//[left,right]
	//[left,keyIndex-1] keyIndex [keyIndex+1,right]
	//���������������������������ˣ����εݹ�

	//С�����Ż�
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

//�ݹ��ȱ�ݣ�ջ֡���̫�ջ�ռ���ܲ����ã����ܻ����
//�ǵݹ飺
//�ݹ�ķǵݹ飺1.ֱ�Ӹ�ѭ����������£�2.�������ݽṹջģ��ݹ���̣��Ը��ӣ�
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
//�鲢���� 
//ʱ�临�Ӷ�O��N*logN) �ȶ�
//������������ �а����������
//�鲢�����ζԱ�ȡС�ķŵ��µ���ʱ����
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;

	int mid = (left + right) >> 1;
	//ʹ[left,mid] [mid,right]����
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);

	//[left,mid] [mid,right]���򣬾Ϳ��Թ鲢

	int begin1 = left, end1 = mid;
	int begin2 = mid+1, end2 = right;
	int index = left;
	//�鲢����ʱ����
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

	//������ԭ����
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

//�鲢�ǵݹ�
//ʱ�临�Ӷ�O��N*logN)
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);

	int gap = 1;//ÿ������ĸ���
	while (gap < n)
	{

		for (int i = 0; i < n; i += 2 * gap)
		{
			//[i,i+gap-1][i+gap,i+2*gap-1]
			//�鲢����ʱ����
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//�鲢�������Ұ�������ܲ�����
			if (begin2 >= n)
				break;
			//�鲢�������Ұ���������ˣ�����һ��
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

			//������ԭ����
			for (int j = i; j <= end2; j++)
			{
				a[j] = tmp[j];
			}
		}

		gap *= 2;
	}
	free(tmp);

}
//�鲢����Ҳ�������򣬻����Զ��ļ��е����ݽ���������Ϊ������ֻ�����ζ����ݣ������ŵ������㷨��Ҫ���������ȡ����˽����鲢��˼�뼴�ɶԴ������ļ����ݽ�������
//��Ҫ�Դ����ļ��е�10G�����ݽ������򣬶��ڴ�ֻ��1G���ã���ô���Էֳ�10��1G�ļ�������1G�ļ������ݽ��п���ʹ������
//���ζ��ļ���ÿ�ζ�1G���ڴ��зŵ�һ�����飬�ÿ��Ŷ���������д��һ���ļ��������ζ�ʣ�µ�9��1G���ݽ�������
//�ٶ������10��1G�����ļ������鲢д��һ���ļ����õ�5��2G���������ļ������ν�������鲢

//��������(ӳ�䣩,�ǱȽ�����
//ʱ�临�Ӷ� O(N+range) ,�����ڷ�Χ���е�һ��������������,������
//�ռ临�Ӷ�O��range)
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
		count[a[i]-min]++;//���ӳ��
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


// ������������ܶԱ�
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
