/*
	树2 List Leaves

	Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. 
For each case, the first line gives a positive integer N (≤10) 
which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. 
Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, 
and left to right. There must be exactly one space between any adjacent numbers, 
and no extra space at the end of the line.

input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6

output:
4 1 5
 */


#include <iostream>
#include <queue>
using namespace std;
#define MAXsize 10

struct Node
{
    int left;
    int right;
}treeinput[MAXsize];

int buildTree(struct Node tree[])
{
    int N;
    char l;
    char r;

    int root = -1;
    scanf("%d",&N);
    int check[N] = {0};
    getchar();
    for(int i = 0; i < N; i++)
    {
        scanf("%c %c", &l, &r);
        getchar();
        if(l != '-')
        {
            tree[i].left = l - '0';
            check[tree[i].left] = 1;
        }
        else
        {
            tree[i].left = -1;
        }
        if(r != '-')
        {
            tree[i].right = r - '0';
            check[tree[i].right] = 1;
        }
        else
        {
            tree[i].right = -1;
        }
    }
    for(int i = 0; i < N; i++)
    {
        if (check[i] == 0)
        {
            root = i;
            break;
        }
    }
    return root;
}

vector<int> traverse(int root)
{
    queue<int> data;
    vector<int> vect;
    if (root == -1)
    {
        return vect;
    }
    int temp;
    data.push(root);
    while(!data.empty())
    {
        temp = data.front();
        if(treeinput[temp].left == -1 && treeinput[temp].right == -1)
        {
            vect.push_back(temp);
        }
        else
        {
            if(treeinput[temp].left != -1)
            {
                data.push(treeinput[temp].left);
            }
            if(treeinput[temp].right != -1)
            {
                data.push(treeinput[temp].right);
            }

        }
        data.pop();
    }
    return vect;
}


int main()
{
    int tree1 = buildTree(treeinput);
    vector<int> vect = traverse(tree1);
    for(int i = 0; i < vect.size(); i++)
    {
        if(i == 0)
        {
            printf("%d", vect[i]);
        }
        else
        {
            printf(" %d", vect[i]);
        }
    }
}


