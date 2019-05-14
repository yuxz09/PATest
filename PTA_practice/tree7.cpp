/*
05-树7 堆中的路径 

将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。
下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10
 */

#include <iostream>
using namespace std;

struct Dynarr
{
	int* data;
	int size;
	int capacity;
};

void initDynarr(struct Dynarr* arr, int capacity)
{
	arr -> data = new int[capacity];
	arr -> size = 0;
	arr -> capacity = capacity;
}

int sizeDynarr(struct Dynarr* arr)
{
	return arr -> size;
}


void swap(struct Dynarr* heap, int i, int j)
{
	int temp = heap -> data[i];
	heap -> data[i] = heap -> data[j];
	heap -> data[j] = temp;
}

int findminIndex(struct Dynarr* heap, int left, int right)
{
	if(heap -> data[left] > heap -> data[right])
	{
		return right;
	}
	return left;
}

void adjustheap(struct Dynarr* heap, int size, int pos)
{
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if(right < size)
	{
		int min = findminIndex(heap, left, right);
		if(heap -> data[pos] > heap -> data[min])
		{
			swap(heap, pos, min);
			adjustheap(heap, size, min);
		}
	}
	else if(left < size)
	{
		if(heap -> data[pos] > heap -> data[left])
		{
			swap(heap, pos, left);
			adjustheap(heap, size, left);
		}
	}

}

void buildheap(struct Dynarr*& heap)
{
	int max = sizeDynarr(heap);
	for(int i = max/2 - 1; i >= 0; i--)
	{
		adjustheap(heap, max, i);
	}
}

void printheap(struct Dynarr* heap, int pos)
{
	for(int i = pos; i >= 0;)
	{
		if(i == pos)
		{
			printf("%d", heap->data[i]);

		}
		else
		{
			printf(" %d", heap->data[i]);			
		}
		if(i % 2 == 0)
		{
			i = (i - 2) / 2;
		}
		else
		{
			i = (i - 1) / 2;
		}
	}
}		


int main()
{
	int N, M;
	scanf("%d %d\n", &N, &M);
	Dynarr* myheap = new Dynarr;////如果没有这句，initDynarr动态数组会bad access
	initDynarr(myheap, N);
	myheap -> size = N;
	int temp;


	for(int i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		myheap -> data[i] = temp;
		for(int j = (1+i)/2 - 1; j >= 0; j--)
		{
			adjustheap(myheap, i+1, j);
		}
	}
	/*
	
	每加入一个结点，就对当前的树进行调整，从当前树的倒数第一个有叶结点的结点往跟调整，依次向下调整直至每次都是合适的位置
	 */



	for(int i = 0; i < M; i++)
	{
		scanf("%d", &temp);
		printheap(myheap, temp-1);	
		if(i != M-1)
		{
			printf("\n");
		}	
	}
}
