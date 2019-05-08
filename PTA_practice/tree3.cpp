/*

An inorder binary tree traversal can be implemented in a non-recursive way with a stack. 
For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, 
the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); 
push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated 
from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.

 */

/*
观察题目发现，整个过程push是先序遍历， pop是中序遍历，要求输出是后序遍历

 */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


int preOrder[30];
int inOrder[30];
int postOrder[30];


int push_pop(string str)
{
    if (str.substr(0,3) == "Pop")
    {
        return 1;//return pop
    }
    else
    {
        return -1;//return push
    }
}

int getNum(string str)
{
    int index = str.find(' ');
    if (str.substr(0,3) != "Pop")
    {
        return stoi(str.substr(index+1, str.length()));
    }
    return -1;
}

void posttraversal(int preIndex, int inIndex, int postIndex, int n)
{
    if(n == 0)
    {
        return;
    }
    else if(n == 1)
    {
        postOrder[postIndex] = preOrder[preIndex];
        return;
    }
    int root = preOrder[preIndex];
    postOrder[postIndex + n - 1] = root;
    int i;
    for(i = 0; i < n; i++)
    {
        if(inOrder[inIndex+i] == root)
        {
            break;
        }
    }
    int left = i;
    int right = n - i - 1;
    posttraversal(preIndex+1, inIndex, postIndex, left);
    posttraversal(preIndex+left+1, inIndex+left+1, postIndex+left, right);
}

int main()
{
    int N;
    scanf("%d", &N);
    getchar();

    string str;
    int type;
    int num;
    stack<int> s;
    int precnt = 0;
    int incnt = 0;

    /*
    已经获得pre, in数组
     */
    for(int i = 0; i < N * 2; i++)
    {
        getline(cin, str);
        type = push_pop(str);
        if (type == -1)
        {
            num = getNum(str);
            preOrder[precnt] = num;
            precnt++;
            s.push(num);
        }
        else if(type == 1)
        {
            inOrder[incnt] = s.top();
            incnt++;
            s.pop();
        }
    }

    int preIndex = 0;
    int inIndex = 0;
    int postIndex = 0;
    posttraversal(preIndex, inIndex, postIndex, N);

    for(int i = 0; i < N; i++)
    {
        if(i == 0)
        {
            cout << postOrder[i];
        }
        else
        {
            cout << " " << postOrder[i];
        }
    }
}

/*

		getline(cin, str);
		index = str.find(' ');
		type = str.substr(0, index);
		numstr = str.substr(index+1, str.length());
		num = stoi(numstr);

 */


/*

-----------------------------------FAIL------------------------------

#include <iostream>
#include <string>
#include <vector>
using namespace std;





int main()
{
    int array[30];
    int N;
    string str;
    scanf("%d", &N);
    getchar();

    int index = -1;
    string type = "";
    string numstr = "";
    int num = -1;
    int root = 0;

    //get root
    getline(cin, str);
    index = str.find(' ');
    type = str.substr(0, index);
    numstr = str.substr(index+1, str.length());
    int treeroot = stoi(numstr);
    array[root] = treeroot;

    int ori = -1;//means left, ori = 1, means right


    for(int i = 1; i < N * 2; i++)
    {

        getline(cin, str);
        type = str.substr(0, 3);
        if (type == "Pop")
        {
            root = (root - 1) / 2;
            cout << "current root: " << root << endl;
            ori = 1;
        }
        else//push
        {
            index = str.find(' ');
            numstr = str.substr(index+1, str.length());
            if(ori == -1)
            {
                root = root * 2 + 1;
                array[root] = num;
                cout << "current root: " << root << endl;
            }
            else if(ori == 1)
            {
                root = root * 2 + 2;
                array[root] = num;
                cout << "current root: " << root << endl;
                ori = -1;
            }
        }
    }
}
 */
