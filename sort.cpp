/* ************************************************************************
 *       Filename:  sort.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年01月15日 14时40分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;
void print_link(int *a, const int len)
{
	for (int i=0;i<len;i++)
		cout << a[i] << " ";
	cout << endl;
}
//寻找数组中最大数的位数作为基数排序循环次数
int getnum(int a[], const int len)
{
	int num = 1;
	int r = 10;
	for(int i=1;i<len;i++)
	{
		while(a[i]/r > 0)
		{
			num++;
			r*=10;
		}
	}
	return num;
}

void radix_sort(int *a, const int len)
{
	int num = getnum(a,len);//获得位数
	vector<vector<int> > radix(10);
	for(int k=0;k<num;k++)
	{
		for(int i=0;i>len;i++)//存放元素
		{
			int t = int(a[i]/pow(10,k))%10;
			radix[t].push_back(a[i]);
		}
		vector<vector<int> >::iterator p;
		vector<int>::iterator q;
		int i=0;
		for(p=radix.begin();p!=radix.end();p++)
		{
			for(q=(*p).begin();q!=(*p).end();q++)
			{
				a[i++] = *q;
			}
		}
		for(int i=0;i<10;i++)
		{
			if(!radix[i].empty())
				radix[i].clear();
		}
	}
}

void count_sort(int *a, const int len)
{
	int low = a[0], high = a[0];
	for(int i=1;i<len;i++)
	{
		low = a[i] < low ? a[i] : low;
		high = a[i] > high ? a[i] : high; 
	}
	int range = high - low + 1;
	int *count = new int[range]();
	for(int i=0;i<len;i++)
	{
		count[a[i]-low]++;
	}
	int j = 0;
	for(int i=0;i<range;i++)
	{
		while(count[i]--)
		{
			a[j++] = i+low;
		}
	}
}

//构造最大堆
void maxheap(int *a, int node, const int len)
{
	int nodecopy = a[node];
	for(int i=2*node+1; i<len;i=2*i+1)//遍历node所有下属节点
	{
		if(i+1 < len && a[i+1] > a[i]) 
			i++;//若右子存在且右大于左，即拿到最大子节点
		if(a[i] > nodecopy){ //若子大于父，交换
			a[node] = a[i];
			node = i;
		}
		else
			break;
	}
	a[node] = nodecopy;
}

//堆排序
void heap_sort(int *a, const int len)
{
	//拿到最后一个父节点，一路遍历到根节点
	for(int node=len/2-1;node>=0;node--)
	{
		maxheap(a, node, len);
	}
	for(int i=len-1;i>0;i--)
	{
		std::swap(a[0],a[i]);
		maxheap(a, 0 ,i);
	}
}

void quick_sort(int *a, const int left, const int right)
{
	if(left > right)
		return;
	
	int temp = a[left];
	int i=left,j=right;

	while(i<j)
	{
		while(a[j] >=temp && i<j)
			j--;
		while(a[i] <= temp && i<j)
			i++;
		if(i<j)
			std::swap(a[i],a[j]);
	}

	if(a[j] < temp)
		std::swap(a[left],a[j]);
		
	quick_sort(a, left, j-1);
	quick_sort(a, j+1, right);
}

template <class T>
void merge(T *a1, const int len1, T *a2, const int len2)
{
	//T temp[len1+len2];
	T *temp = new T[len1+len2];
	int t =0,i=0,j=0,k=0;
	while(i<len1 && j<len2)
	{
		if(a1[i] < a2[j])
			temp[t++] = a1[i++];
		else
			temp[t++] = a2[j++];
	}
	#if 0
	while(i<len1) 
		temp[t++] = a1[i++];
	while(j<len2)
		temp[t++] = a2[j++];
	while(k<t)
		a1[k] = temp[k++];
	#else
	copy(a1+i, a1+len1, temp+t);
	copy(a2+j, a2+len2, temp+t);
	copy(temp, temp+len1+len2, a1);
	#endif
	delete[] temp;
}
template <class T>
void merge_sort(T *a, const int len)
{
	if(len>1)
	{
		int mid = len/2;
		T *a1 = a;
		int len1 = mid;
		T *a2 = a+mid;
		int len2 = len-mid;
		merge_sort(a1, len1);
		merge_sort(a2, len2);
		merge(a1, len1, a2, len2);
	}
}

void shell_sort(int a[], int len)
{
	int gap = len;
	while(gap = gap/2)
	{
		cout << gap << endl;
		for(int i=gap;i<len;i++)
		{
			int key=a[i];
			int j=i-gap;
			for(;j>=0 && a[j]>key;j-=gap)
			{
				a[j+gap] = a[j];	
			}
			a[j+gap] = key;
		}
	}
}

void insert_sort3(int a[], int len)
{
	for(int i=1;i<len;i++)
	{
		if(a[i] < a[i-1])
		{
			int key = a[i];
			int j=i-1;
			for(;j>=0 && a[j]>key;j--)
			{
				a[j+1] = a[j];
			}
			a[j+1] = key;
		}
	}
}

void insert_sort(int a[], int len)
{
	for(int i=1;i<len;i++)
	{
		int key = a[i];
		int j=i-1;
		for(;j>=0;j--)
		{
			if(key < a[j])
				a[j+1] = a[j];
			else 
				break;
		}
		a[j+1] = key;
	}
}

void insert_sort2(int a[], int len)
{
	for(int i=1;i<len;i++)
	{
		int key=a[i];
		int low=0, high = i-1;
		while(low <= high)
		{
			int mid = (low+high)/2;
			if(key < a[mid])
				high = mid-1;
			else
				low = mid+1;
		}
		for(int j=i-1;j>=low;j--)
		{
			a[j+1] = a[j];
		}
		a[low] = key;
	}
}

void select_sort(int a[], int len)
{
	for(int i=0;i<len-1;i++)
	{
		int min_index = i;
		for(int j=i;j<len;j++)
		{
			if(a[j] < a[min_index])
				min_index = j;
		}
		std::swap(a[i],a[min_index]);
	}
}

void bubble_sort(int a[], int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(a[j] > a[j+1])
				std::swap(a[j], a[j+1]);
		}
	}
}

void bubble_sort2(int a[], int len)
{
	int low = 0, high=len-1;
	int flag = 0;

	while(low<high)
	{
		for(int i=low;i<high;i++)
		{
			if(a[i]>a[i+1])
				std::swap(a[i],a[i+1]);
			flag = i;
		}
		high=flag;
		for(int i=high;i>low;i--)
		{
			if(a[i] < a[i-1])
				std::swap(a[i],a[i-1]);
			flag = i;
		}
		low=flag;
	}
}

int main(int argc, char *argv[])
{
	int a[] = {2,4,6,8,0,1,3,5,7,9};
	int len = sizeof(a)/sizeof(a[0]);
	print_link(a,10);
//	bubble_sort2(a, len);
//	select_sort(a, len);
//	insert_sort3(a, len);
//	shell_sort(a, len);
//	merge_sort(a, len);
//	quick_sort(a, 0, len-1);
//	heap_sort(a, len);
//	count_sort(a, len);
	radix_sort(a, len);
	for (int i=0;i<len;i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}


