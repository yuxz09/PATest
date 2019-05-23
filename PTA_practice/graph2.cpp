/*
This time let us consider the situation in the movie "Live and Let Die" in which James Bond, 
the world's most famous spy, was captured by a group of drug dealers. 
He was sent to a small piece of land at the center of a lake filled with crocodiles. 
There he performed the most daring action to escape -- he jumped onto the head of the nearest crocodile! 
Before the animal realized what was happening, James jumped again onto the next big head... 
Finally he reached the bank before the last crocodile could bite him (actually the stunt man was caught 
by the big mouth and barely escaped with his extra thick boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) 
and the northeast corner at (50,50). The central island is a disk centered at (0,0) with the diameter of 15. 
A number of crocodiles are in the lake at various positions. Given the coordinates of each crocodile and 
the distance that James could jump, you must tell him whether or not he can escape.

Input Specification:
Each input file contains one test case. Each case starts with a line containing two positive integers N (≤100), 
the number of crocodiles, and D, the maximum distance that James could jump. 
Then N lines follow, each containing the (x,y) location of a crocodile. Note that no two crocodiles are staying at 
the same position.

Output Specification:
For each test case, print in a line "Yes" if James can escape, or "No" if not.
 */

/*
与dfs的区别
第一跳半径不同，所以孤岛需要特殊处理
第一跳里面有几条鳄鱼可以跳，所以要找连通集
 */

#include <iostream>
#include <cmath>
using namespace std;

struct Node
{
    int index;
    int x;
    int y;
    int visited;
}arr[2500];

int issafe(Node v, int D)
{
    if (50 - abs(v.x) <= D || 50 - abs(v.y) <= D)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int jump(Node v, Node w, int dist)
{
    int distx = abs(v.x - w.x);
    int disty = abs(v.y - w.y);
    int distc = pow(distx, 2) + pow(disty, 2);
    if (pow(dist,2) >= distc)
    {
        return 1;
    }
    return 0;
}

int DFS(int size, int dist, int v)
{
    int ans = 0;
    arr[v].visited = 1;
    //能够从这个鳄鱼跳到岸上
    if(issafe(arr[v], dist))
    {
        ans = 1;
        return ans;
    }
    else
    {
        //对于graph里面的所有鳄鱼
        for(int i = 0; i < size; i++)
        {
            //如果这条鳄鱼没有被访问过，并且可以从当前鳄鱼跳上去
            if(arr[i].visited == 0 && jump(arr[v], arr[i], dist))
            {
                ans = DFS(size, dist, i);
            }
            if(ans == 1)
            {
                return ans;
            }
        }
    }
    return ans;
}

int firstjump(Node* arr, int i, int dist)
{
    int x = abs(arr[i].x);
    int y = abs(arr[i].y);

    double d = sqrt(pow(x,2) + pow(y,2));
    if(d <= dist + 7.5)
    {
        return 1;
    }
    return 0;
}



int main()
{
    int N, D;
    scanf("%d %d", &N, &D);
    getchar();
    int tempx, tempy;


    arr[0].x = 0;
    arr[0].y = 0;
    arr[0].visited = 0;
    int result = 0;

    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &tempx, &tempy);
        getchar();
        arr[i].index = i;
        arr[i].x= tempx;
        arr[i].y = tempy;
        arr[i].visited = 0;
    }

    //直接从孤岛调到岸边
    if(D >= 42.5)
    {
        printf("Yes");
        return 0;
    }
    else
    {
        for(int i = 0; i < N; i++)
        {
            if(arr[i].visited == 0 && firstjump(arr, i, D))
            {
                result = DFS(N, D, i);
                arr[0].visited = 1;
            }
            if(result == 1)
            {
                printf("Yes");
                return 0;
            }

        }
    }

    printf("No");

    return 0;
}
