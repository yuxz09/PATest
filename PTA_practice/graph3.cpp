/*
06-图3 六度空间 

“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。
这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，
也就是说，最多通过五个人你就能够认识任何一个陌生人。”如图1所示。


图1 六度空间示意图
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，
试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。
随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，
能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。


输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10^4,表示人数）、边数M（≤33×N，表示社交关系数）。
随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号)。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。
每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10

输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

typedef int vertex;//顶点下标表示整型
typedef int weight; //边的权值设为整型

//定义边
typedef struct edgenode* Ptr2edgenode;
struct edgenode
{
    vertex v1;
    vertex v2;
};
typedef Ptr2edgenode edge;

//定义邻接点
typedef struct adjnode* Ptr2adjnode;
struct adjnode
{
    vertex adjindex;//邻接点下标
    adjnode* next;
};

//定义表头顶点结点

typedef struct vertexnode
{
    Ptr2adjnode firstedge; //头顶点结点第一条边指向的邻接点
}AdjList[10000];//一个数组，存放的每个元素都是struct vertexnode, 即指向邻接点的指针


//定义图，用邻接表表示图
typedef struct graphnode* Ptr2graphnode;
struct graphnode
{
    int nv;
    int ne;
    AdjList G;
};
typedef Ptr2graphnode LGraph;

LGraph createGraph(int numv)
{
    vertex v;
    LGraph graph = new graphnode;
    graph -> nv = numv;
    graph -> ne = 0;

    for(v = 0; v < graph->nv; v++)
    {
        graph -> G[v].firstedge = NULL;
    }
    return graph;
}

void insertEdge(LGraph graph, edge e)
{

    //newnode1是指向邻接点的指针
    Ptr2adjnode newnode2 = new adjnode;
    newnode2 -> adjindex = e -> v2;

    //  newnode1 -> w = 1;
    newnode2 -> next = graph -> G[e->v1].firstedge;
    graph -> G[e->v1].firstedge = newnode2;

    //newnode2是指向邻接点的指针
    Ptr2adjnode newnode1 = new adjnode;
    newnode1 -> adjindex = e -> v1;
    //   newnode2 -> w = 1;
    newnode1 -> next = graph -> G[e->v2].firstedge;
    graph -> G[e->v2].firstedge = newnode1;
}

LGraph BuildGraph()
{
    LGraph graph;
    edge e;
    int v;
    int nv;
    scanf("%d", &nv);
    //   getchar();
    graph = createGraph(nv);

    scanf("%d", &(graph->ne));

    getchar();
    if(graph -> ne != 0)
    {
        e = new edgenode;
        for(int i = 0; i < graph -> ne; i++)
        {
            scanf("%d %d", &(e->v1), &(e->v2));

            insertEdge(graph, e);
        }
    }
    return graph;
}


/*
注意！并不是每调用一次BFS，深度就增加一层
例如：
第一次bfs得到层数为1的点，c, e, f
第二次bfs，是以c为起始点bfs, g, h, i
第三次bfs, 是以e为起始点bfs, j, k
但是第二次bfs, 第三次bfs的层数都是2，并不是按照调用bfs次数

 */
int BFS(LGraph graph, vertex i, int visited[])
{
    queue<vertex> q;
    int cnt = 1;//该结点本身就是一个
    int level = 0;
    vertex last = i;
    vertex tail = i;

    visited[i] = 1;
    q.push(i);
    vertex temp;
    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        for(adjnode* w = graph->G[temp].firstedge; w != NULL;  w = w -> next)
        {

            if (visited[w->adjindex] == 0)
            {
                visited[w->adjindex] = 1;
                q.push(w->adjindex);
                cnt++;
                tail = w->adjindex;
            }
        }
        if(temp == last)
        {
            level++;
            last = tail;
        }
        if(level == 6)
        {
            break;
        }


    }
    return cnt;
}

void initVisit(int visited[])
{
    for(int i = 0; i < 10000; i++)
    {
        visited[i] = 0;
    }
}

int main()
{
    LGraph graph = BuildGraph();
    int visited[10000];

    for(vertex i = 1; i <= graph -> nv; i++)
    {
        initVisit(visited);

        int cnt = BFS(graph, i, visited);

        printf("%d: ", i);
        printf("%.2f%%\n", (100.0*cnt)/graph->nv);
    }
}
