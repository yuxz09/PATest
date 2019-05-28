/*
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，
帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；
M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：
城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。
输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
 */
#include <iostream>
#include <algorithm>
using namespace std;
int length[510][510] = {510};////////
int cost[510][510] = {1000};
int visited[510] = {0};
int dist[510] = {510};//////////这种方式并不能统一初始化为510，必须要在函数里面用for来一个个初始化

int money[510] = {0};


void Dijkstra(int start, int end, int sz)
{
    int v = start;
    for(int i = 0; i < sz; i++)
    {
        dist[i] = 510;
    }
    dist[v] = 0;


    while(v != end)
    {
        visited[v] = 1;
        for(int i = 0; i < sz; i++)
        {
            if(visited[i] == 0)
            {
                if(dist[v] + length[v][i] < dist[i])
                {
                    dist[i] = dist[v] + length[v][i];
                    money[i] = money[v] + cost[v][i];
                }
                else if(dist[v] + length[v][i] == dist[i] && money[v] + cost[v][i] < money[i])
                {
                    money[i] = money[v] + cost[v][i];
                }
            }
        }
        int min = 510;
        for(int j = 0; j < sz; j++)
        {
            if(dist[j] < min && visited[j] == 0)
            {
                v = j;
                min = dist[j];
            }
        }
        visited[v] = 1;

    }
}

int main()
{
    int N;
    int M;
    int S;
    int D;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    getchar();

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            length[i][j] = 510;
        }
    }

    int c1, c2;
    int l;
    int fee;
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d %d %d", &c1, &c2, &l, &fee);
        getchar();
        length[c1][c2] = l;
        length[c2][c1] = l;
        cost[c1][c2] = fee;
        cost[c2][c1] = fee;
    }

    Dijkstra(S, D, N);
    printf("%d %d\n", dist[D], money[D]);
    return 0;

}