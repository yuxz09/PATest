/*

	May 6th, 2019

	是否同一棵二叉搜索树
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。
例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。
第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0

Yes
No
No

在查找某个结点时遇到前面没有访问过的结点，则一定不一致。
因为如果没碰到过，当前这个整数不应该插在后面，应该在没有碰到的结点上就查找过。
序列中，前面的数字必定是后面数字的根或者兄弟，但不会是儿子。
所以查找的时候，如果在树中搜索这个查找的结点时，遇到了没有访问过的结点，那么这个结点在序列中必然要出现在查找结点的前面

*/
#include <iostream>
using namespace std;
typedef struct Node* Tree;
struct Node
{
	int val;
	Node* left;
	Node* right;
	int visit;
};

Node* makeNode(int value)
{
	struct Node* newnode = (Node*)malloc(sizeof(struct Node));
	newnode -> val = value;
	newnode -> left = NULL;
	newnode -> right = NULL;
	return newnode;
}

Node* insertNode(Tree tree, int val)
{
	if(tree == NULL)
	{
		tree = makeNode(val);
	}
	else if(val > tree -> val)
	{
		tree -> right = insertNode(tree -> right,val);
	}
	else if(val < tree -> val)
	{
		tree -> left = insertNode(tree -> left,val);		
	}
	return tree;
}


Tree buildTree(int N)
{
	int val;
	scanf("%d", &val);
	Tree tree = makeNode(val);
	for(int i = 1; i < N; i++)
	{
		scanf("%d", &val);
		tree = insertNode(tree, val);
	}
	return tree;
}

int check(Tree tree, int N)
{
	if(tree -> visit == 1)
	{
		if (N < tree -> val)
		{
			return check(tree -> left, N);
		}
		else if(N > tree -> val)
		{
			return check(tree -> right, N);
		}
		//说明N这个结点在树中出现了第二次，那么认为不一致
		else
		{
			return 0;
		}
	}
	else
	{
		if(N == tree -> val)
		{
			tree -> visit = 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int Judge(Tree tree, int N)
{
	int temp;
	int flag = 0;//没有发现矛盾，为1是矛盾，但是接着读数
	scanf("%d", &temp);
	if(temp != tree -> val)
	{
		flag = 1;
	}
	else
	{
		tree -> visit = 1;
	}
	for(int i = 1; i < N; i++)
	{
		scanf("%d", &temp);
		//刚刚出现有矛盾
		if(flag == 0 && check(tree, temp) == 0)
		{
			flag = 1;			
			//return 0;当发现序列中的某个数与T不一致时，必须把序列后面的树都读完. use flag
		}
	}
	if(flag)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void ResetT(Tree tree)
{
	if(tree -> left)
	{
		ResetT(tree -> left);
	}
	if(tree -> right)
	{
		ResetT(tree -> right);
	}
	tree -> visit = 0;	
}

void freeT(Tree tree)
{
	if(tree -> left)
	{
		freeT(tree -> left);
	}
	if(tree -> right)
	{
		freeT(tree -> right);
	}
	free(tree);
}

int main()
{
	int N, L;
	scanf("%d", &N);
	while(N)
	{
		scanf("%d", &L);
		Tree mytree = buildTree(N);
		for(int i = 0; i < L; i++)
		{
			if(Judge(mytree, N))///每个序列有N个
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");				
			}
			ResetT(mytree);////主要是为了不同序列比较，一个树对应多个序列情况
		}
		freeT(mytree);
		scanf("%d", &N);
	}
	return 0;
}




