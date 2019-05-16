/*
We have a network of computers and a list of bi-directional connections. Each of these connections allows a file transfer 
from one computer to another. Is it possible to send a file from any computer on the network to any other?

Input Specification:
Each input file contains one test case. For each test case, the first line contains N (2≤N≤10^4), 
the total number of computers in a network. Each computer in the network is then represented by a positive integer between 1 and N. 
Then in the following lines, the input is given in the format:

I c1 c2  
where I stands for inputting a connection between c1 and c2; or

C c1 c2    
where C stands for checking if it is possible to transfer files between c1 and c2; or

S
where S stands for stopping this case.

Output Specification:
For each C case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between c1 and c2, 
respectively. At the end of each case, print in one line "The network is connected." if there is a path between any pair of computers; 
or "There are k components." where k is the number of connected components in this network.
 */

#include <iostream>
#include <math.h>
using namespace std;


void initialization(int arr[], int size)
{
	for(int i = 0; i < size; i++)
	{		
		arr[i] = -1;
	}
}

int find(int arr[], int target)
{
	for(int i = 0; arr[i] >= 0; i = arr[i])
	{
		return i;
	}
}

/*
按秩归并
根据树高归并
根据规模归并
 */
void Union(int arr[], int root1, int root2)
{
	if(abs(arr[root1]) > abs(arr[root2]))
	{
		arr[root2] = root1;
	}
	else
	{
		if(abs(arr[root1]) == abs(arr[root2]))
		{
			arr[root2] = arr[root2] - 1;
		}
		arr[root1] = root2;
	}
}

/*
union + find
先找输入的是否连接过，没有再连接
 */
void input_connection(int arr[])
{
	int c1;
	int c2;
	scanf("%d %d", &c1, &c2);
	c1 = c1 - 1;
	c2 = c2 - 1;
	int root1 = find(arr, c1);
	int root2 = find(arr, c2);
	if (root1 != root2)
	{
		Union(arr, root1, root2);
	}
}

/*
find
 */
void check_connection(int arr[])
{
	int c1;
	int c2;	
	scanf("%d %d", &c1, &c2);
	c1 = c1 - 1;
	c2 = c2 - 1;
	int root1 = find(arr, c1);
	int root2 = find(arr, c2);	
	if(root1 == root2)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
}

/*
数多少个根结点，即多少个连通集
 */
void check_network(int arr[], int size)
{
	int cnt = 0;
	for(int i = 0; i < size; i++)
	{
		if(arr[i] < 0)
		{
			cnt++;
		}
	}
	if(cnt == 1)
	{
		printf("The network is connected.\n");
	}
	else
	{
		printf("There are %d components.\n", cnt);		
	}

}


int main()
{
	int N;
	char c;
	int arr[N];

	scanf("%d", &N);
	initialization(arr, N);
	do
	{
		scanf("%c", &c);
		switch(c)
		{
			case 'I':
				input_connection(arr);
				break;
			case 'C':
				check_connection(arr);
				break;
			case 'S':
				check_network(arr, N);
				break;
		}
	}while(c != 'S');
	return 0;
}

