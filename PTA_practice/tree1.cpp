/*
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。
例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。
而图2就不是同构的。

输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，
即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，
给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。
如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。
注意：题目保证每个结点中存储的字母是不同的。

8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -

如何存储输入数据？
array of structs

用数组建立tree,不用任何指针

此题由何钦铭老师给出
*/



#include <iostream>
using namespace std;
#define MAXsize 10

struct Node
{
    char id;
    int left;//why not use char, easy to tree[left]
    int right;
}treeA[MAXsize], treeB[MAXsize];


int isSame(int rootA, int rootB)
{

    if(rootA == -1 && rootB == -1)
    {
        return 1;
    }
    else if((rootA == -1 && rootB != -1) || (rootA != -1 && rootB == -1))
    {
        return 0;
    }
    else if(treeA[rootA].id != treeB[rootB].id)
    {
        return 0;
    }
    else
    {
        if(treeA[rootA].left == -1 && treeB[rootB].left == -1)
        {
            return isSame(treeA[rootA].right, treeB[rootB].right);
        }
        else
        {
            if(treeA[treeA[rootA].left].id == treeB[treeB[rootB].left].id)
            {
                return isSame(treeA[rootA].left, treeB[rootB].left) && isSame(treeA[rootA].right, treeB[rootB].right);
            }
            else
            {
                return isSame(treeA[rootA].left, treeB[rootB].right) && isSame(treeA[rootA].right, treeB[rootB].left);
            }
        }
    }
}



//return root of tree, index of array
int createTree(struct Node tree[])
{
    int N;
    scanf("%d", &N);
    getchar();
    char l;
    char r;
    int check[N];
    int root = -1;

    for(int i = 0; i < N; i++)
    {
        check[i] = 0;
        scanf("%c %c %c", &tree[i].id, &l, &r);
        getchar();
        if(l == '-')
        {
            tree[i].left = -1;
        }
        else
        {
            tree[i].left = l - '0';
            check[tree[i].left] = 1;
        }
        if(r == '-')
        {
            tree[i].right = -1;
        }
        else
        {
            tree[i].right = r - '0';
            check[tree[i].right] = 1;
        }
    }
    for(int i = 0; i < N; i++)
    {
        if(check[i] == 0)
        {
            root = i;
            break;
        }
    }
    return root;
}

int main()
{
    int A = createTree(treeA);
    int B = createTree(treeB);
    if(isSame(A, B))
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}


