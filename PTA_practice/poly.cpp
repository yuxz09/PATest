
#include <iostream>
using namespace std;

struct Node
{
    int coefficient;
    int expon;
    struct Node* next;
};


void attach(int co, int exp, Node* &rear)
{
    Node* tempnode = new Node;
    tempnode -> coefficient = co;
    tempnode -> expon = exp;
    tempnode -> next = NULL;////
    rear -> next = tempnode;
    rear = rear -> next;
}

Node* read()
{
    int num;
    int co;
    int expon;

    Node* node_result = new Node;
    node_result -> next = NULL;
    Node* rear = node_result;

    scanf("%d", &num);
    while(num--)
    {
        scanf("%d %d", &co, &expon);
        attach(co, expon, rear);
    }

    Node* tempnode = node_result;
    node_result = node_result -> next;
    free(tempnode);
    return node_result;
}

Node* mult(Node* list1, Node* list2)
{
    //node: used to traverse node in lists
    Node* node1 = list1;
    Node* node2 = list2;
    Node* node_result = new Node;
    Node* rear = node_result;
    Node* tempnode;

    int co;
    int expon;

    if(list1 == NULL || list2 == NULL)
    {
        return NULL;
    }
    else
    {
        while(node2)
        {
            attach(node1 -> coefficient * node2 -> coefficient, node1->expon + node2 -> expon, rear);
            //    cout << rear -> coefficient << " " << rear -> expon << endl;
            node2 = node2 -> next;
        }
        node1 = node1 -> next;
        while(node1)
        {
            node2 = list2;
            rear = node_result;
            while(node2)
            {
                expon = node1 -> expon + node2 -> expon;
                co = node1 -> coefficient * node2 -> coefficient;
                while(rear -> next && rear -> next -> expon > expon)
                {
                    rear = rear -> next;
                    //    cout << rear -> coefficient << " " << rear -> expon << endl;

                }
                if(rear -> next && rear -> next -> expon == expon)
                {
                    if(rear -> next -> coefficient + co != 0)
                    {
                        rear -> next -> coefficient += co;
                    }
                    else
                    {
                        tempnode = rear -> next;
                        rear -> next = tempnode -> next;
                        free(tempnode);
                    }
                }
                else
                {
                    tempnode = new Node;
                    tempnode -> coefficient = co;
                    tempnode -> expon = expon;
                    tempnode -> next = rear -> next;
                    rear -> next = tempnode;
                    rear = tempnode;
                    //     cout << rear -> coefficient << " " << rear -> expon << endl;
                }
                node2 = node2 -> next;
            }
            node1 = node1 -> next;
        }
    }

    tempnode = node_result;
    node_result = node_result -> next;
    free(tempnode);
    return node_result;
}

Node* add(Node* list1, Node* list2)
{
    Node* node_result = new Node;
    Node* node1 = list1;
    Node* node2 = list2;
    Node* rear = node_result;
    int co;
    int expon;

    while(node1 && node2)
    {
        if(node1 -> expon > node2 -> expon)
        {
            attach(node1 -> coefficient, node1 -> expon, rear);
            node1 = node1 -> next;
        }
        else if (node1 -> expon < node2 -> expon)
        {
            attach(node2 -> coefficient, node2 -> expon, rear);
            node2 = node2 -> next;
        }
        else
        {
            if(node1 -> coefficient + node2 -> coefficient != 0)//同类项合并时有抵消
            {
                attach(node1 -> coefficient + node2 -> coefficient, node2 -> expon, rear);
            }
            //抵消也要向前移动，不然运行超时
            node1 = node1 -> next;
            node2 = node2 -> next;
        }
    }
    if(node1)
    {
        attach(node1 -> coefficient, node1 -> expon, rear);
        node1 = node1 -> next;
        //    rear -> next = node1;
        //    node1 = NULL;
    }
    if(node2)
    {
        attach(node2 -> coefficient, node2 -> expon, rear);
        node2 = node2 -> next;
        //    rear -> next = node2;
        //    node2 = NULL;
    }
    rear -> next = NULL;
    Node* tempnode = node_result;
    node_result = node_result -> next;
    free(tempnode);
    return node_result;
}

void print(Node* node)
{
    int flag = 0;
    if(node == NULL)
    {
        printf("0 0");
        return;
    }
    while(node)
    {
        if(flag == 0)
        {
            cout << node -> coefficient << " " << node -> expon;
            flag = 1;
        }
        else
        {
            cout << " " << node -> coefficient << " " << node -> expon;
        }
        node = node->next;
    }
}

int main()
{
    struct Node* list1 = read();
    struct Node* list2 = read();

    Node* result_multiply = mult(list1, list2);
    Node* result_add = add(list1, list2);

    print(result_multiply);
    cout << "\n";
    print(result_add);
    return 0;
}
/*

#include <iostream>
using namespace std;

struct Node
{
    int coefficient;
    int expon;
    struct Node* next;///////
};


void attach(int co, int exp, Node* &rear)
{
	Node* tempnode = new Node;
	tempnode -> coefficient = co;
	tempnode -> expon = exp;
	tempnode -> next = NULL;
	rear -> next = tempnode;
	rear = rear -> next;
}


//	how to return a struct from function, C++?  --return type, do not need a struct
Node* read()
{
    int num;
    int co;
    int expon;

    //initialize first empty node
    Node* node_result = new Node;
    Node* rear = node_result;
    
    scanf("%d", &num);
    while(num--)
    {
        scanf("%d %d", &co, &expon);
        attach(co, expon, rear);
    }

    //delete initial empty node

    Node* tempnode = node_result;
    node_result = node_result -> next;
    free(tempnode);
    return node_result;
    
 
}

int main()
{
    struct Node* list1 = read();
   
    while(list1)
    {
    	cout << list1 -> coefficient <<  " " << list1 -> expon << endl;
    	list1 = list1 -> next;
    }
    return 0;
}
    while(list1)
    {
    	cout << list1 -> coefficient <<  " " << list1 -> expon << endl;
    	list1 = list1 -> next;
    }
 */