/*
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。
假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，
按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。
随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
8 6
0 7
0 1
2 0
4 1
2 4
3 5

输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
*/



#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define MaxVertexNum 10

typedef struct vertexnode* PtrToVertex;
typedef int Vertex;
typedef int WeightType;
struct vertexnode
{
    int numV;
    int numE;
    WeightType G[MaxVertexNum][MaxVertexNum];
};

typedef struct edgenode* PtrToEdge;
struct edgenode
{
    Vertex v1, v2;
    WeightType weight;
};
typedef PtrToEdge edge;
typedef PtrToVertex Graph;//指向结点的指针，为传参方便


Graph CreateGraph(int numvertex)
{
    Vertex v, w;
    Graph graph = new vertexnode;
    graph -> numV = numvertex;
    graph -> numE = 0;

    for(v = 0; v < numvertex; v++)
    {
        for(w = 0; w < numvertex; w++)
        {
            graph -> G[v][w] = 0;
        }
    }
    return graph;
}

void insertEdge(Graph graph, edge e)
{
    //插入边v1, v2
    graph -> G[e->v1][e->v2] = e -> weight;
    //无向图
    graph -> G[e->v2][e->v1] = e -> weight;
}

Graph buildGraph()
{
    Graph graph;
    int nv;
    int ne;
    scanf("%d %d", &nv, &ne);
    getchar();
    graph = CreateGraph(nv);
    graph -> numE = ne;
    graph -> numV = nv;
    if(graph -> numE != 0)
    {
        edge E = new edgenode;
        for(int i = 0; i < graph -> numE; i++)
        {
            scanf("%d %d", &E->v1, &E->v2);
            getchar();
            E -> weight = 1;
            insertEdge(graph, E);
        }
    }
    return graph;
}


void DFS(Graph graph, int start, int visited[])
{
//    vector<int> vect;
 //   stack<int> s;//reachable nodes
  //  s.push(start);
    int temp = start;
 //   s.pop();

    printf("%d ", temp);


    visited[temp] = 1;
    for(int i = 0; i < graph -> numV; i++)
    {
        if(visited[i] == 0 && graph->G[temp][i] == 1)
        {
            DFS(graph, i, visited);
        }
    }

}

vector<int> BFS(Graph graph, int start, int visited[])
{
    vector<int> vect;
    int temp = start;
    visited[temp] = 1;
    queue<int> q;
    q.push(temp);
    vect.push_back(temp);
    while(!q.empty())
    {
        temp = q.front();
        for(int i = 0; i < graph->numV; i++)
        {
            if (graph->G[temp][i] == 1 && visited[i] == 0)
            {
                q.push(i);
                visited[i] = 1;
                vect.push_back(i);
            }
        }
        q.pop();
    }
    return vect;
}


void print(vector<int> vect)
{
    printf("{ ");
    for(int i = 0; i < vect.size(); i++)
    {
        printf("%d ", vect[i]);
    }
    printf("}");
}

int main()
{
    Graph graph = buildGraph();
    int visited[graph->numV];
    //DFS
    for(int i = 0; i < graph ->numV; i++)
    {
        visited[i] = 0;
    }
    vector<int> temp;
    for(int i = 0; i < graph ->numV; i++)
    {
        if(visited[i] == 0)
        {
            if(i != 0)
            {
                printf("\n");
            }
            printf("{ ");
            DFS(graph, i, visited);
            printf("}");
        }
    }
    printf("\n");


    for(int i = 0; i < graph ->numV; i++)
    {
        visited[i] = 0;
    }
    //BFS
    for(int i = 0; i < graph ->numV; i++)
    {
        if(visited[i] == 0)
        {
            temp = BFS(graph, i, visited);
            if(i == 0)
            {
                print(temp);
            }
            else
            {
                printf("\n");
                print(temp);
            }
        }
    }
}




