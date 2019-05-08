/*
	reverse linked list
	Date: April 23th, 2019


Each input file contains one test case. For each case, the first line contains the address of the first node, 
a positive N (≤10^5) which is the total number of nodes, 
and a positive K (≤N) which is the length of the sublist to be reversed. 
The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

---------------------
	链表：
	有地方存数据
	有地方存指针

	开一个充分大的结构数组代表内存空间
	一个元素所处的位置就是它的下标index，下标可以用整数表示

	00000	00100   12309   33218   00000  99999   68237
	  4		  1 ->    2  ->   3		  4      5	     6
	99999   12309   33218   00000   99999  68237     -1
	
	00100 -start

	加个头结点
	需要的结果
	头结点指向kth节点，然后kth ->(k-1)th -> (k-2)th...1st 节点
	1st节点指向(k+1)th节点

	需要的指针 * 3
	new已经逆转好的链表的头结点位置，初始时，应该指向start结点
	old还没有逆转的老链表的头结点
	需要操作old -> new
	并且需要记住第三个结点tmp的位置,否则第二个结点转向，后面的链表就被丢弃了
	
	new = old
	old = tmp
	tmp = tmp -> next
	重复k步

	取巧方法：用数组存储，排序，再逆序输出
	但是实际状况中，内存中可能有些结点保存的是其他程序的数据，所以必须使用单链表逆转方法

---------------------
	疑问：
	如何把数组转化成根据地址相连的链表？？？




*/

#include <iostream>
using namespace std;

struct Node
{
    int adrs;
    int data;
    int next;
    struct Node* link;
};


Node* reverselink(struct Node* node, int K)
{
    struct Node* initnode = node;
    struct Node* newnode = node -> link;
    struct Node* oldnode = newnode -> link;
    struct Node* temp;

    int count = 1;

    while(count < K)
    {
        temp = oldnode -> link;
        oldnode -> link = newnode;
        oldnode -> next = newnode -> adrs;
        newnode = oldnode;
        oldnode = temp;
        count++;
    }

    initnode -> link -> link = oldnode;

    if(oldnode != NULL)
    {
        initnode -> link -> next = oldnode -> adrs;
    }
    else
    {
        initnode -> link -> next = -1;
    }

    return newnode;
}

void print(struct Node* initNode)
{
    while(initNode != NULL)
    {
        if(initNode -> link != NULL)
        {
            printf("%05d %d %05d\n", initNode -> adrs, initNode -> data, initNode -> link -> adrs);

        }
        else
        {
            printf("%05d %d %d\n", initNode -> adrs, initNode -> data, -1);
        }

        initNode  = initNode -> link;
    }
}

int main()
{
    int start = 0;
    int N = 0;
    int K = 0;
    scanf("%d %d %d",&start, &N, &K);
    int adrs = -1;
    int cnt = 0;

    int data[100000] = {0};
    int next[100000] = {0};
    while(cnt < N)
    {
        scanf("%d", &adrs);
        scanf("%d", &data[adrs]);
        scanf("%d", &next[adrs]);
        cnt++;
    }
    //解决多余结点
    int actualNum = 0;
    struct Node* initNode = new Node;
    struct Node* prevNode = initNode;
    struct Node* curNode = NULL;

    for(int i = start; i <= 100000 && i != -1; )
    {
        curNode = new Node;
        curNode -> data = data[i];
        curNode -> adrs = i;
        curNode -> next = next[i];
        curNode -> link = NULL;//////
        prevNode -> link = curNode;
        prevNode = curNode;
        i = next[i];
        actualNum++;
    }
    cnt = 0;
    N = actualNum;

    curNode -> link = NULL;


    if(K == 1)//直接输出
    {
        initNode = initNode -> link;
    }
    else if(K == N || (N / K == 1 && N % K != 0))//全反转  有尾巴不反转
    {
        initNode = reverselink(initNode, K);
    }
    else if(N % K == 0 && N / K != 1)
    {
        int count = 1;
        int flag = 0;
        struct Node* markNode = initNode;
        struct Node* firstNode = initNode;
        while(cnt < N / K)
        {
            initNode = reverselink(initNode, K);
            markNode -> link = initNode;
            markNode -> next = initNode -> adrs;
            cnt++;
            while(count < K && cnt < N / K)
            {
                initNode = initNode -> link;
                count++;
            }
            markNode = initNode;
            count = 1;
        }
        initNode = firstNode -> link;
    }
    print(initNode);
    
}



/*
无法通过：
最大N,最后剩K-1不反转

解答
else if(N % K == 0 && N / K != 1)
的N% K==0删除即可
应该说是N%K有余数也需要按照反转多次的办法来

*/


/*
wrong~~~~

Node* reverselink(struct Node* node, int K)
{
	struct Node* initnode = node;
	struct Node* newnode = node -> next;
	struct Node* oldNode = newnode -> next;
	struct Node* temp = oldNode -> next;
	int count = 1;//是否可以更改为temp != NULL，省掉计数器？？？

	while(count < K)//count = 4
	{
		oldnode -> link = newnode;
		newnode = oldnode;
		oldnode = temp;
		temp = temp -> link;
		count++;
	}
	initnode -> link -> link = oldnode;
	initnode -> link = newnode;
	return initnode -> link;
}
 */




























