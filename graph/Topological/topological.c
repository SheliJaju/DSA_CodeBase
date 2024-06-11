#include<stdio.h>
#include<stdlib.h>

typedef struct Node 
{
    int data;
    struct Node *next;
}node;

typedef struct Graph
{
    int nov;
    node **adj;
    int *visited;
}graph;

typedef struct SNode
{
    node *address;
    struct SNode *next;
}snode;


node *createNode(int d)
{
    node *p =(node *)malloc(sizeof(node));
    p->data = d;
    p->next = NULL;
    return p;
}

void insertNode(node *s,node *p)
{
    node *temp = s;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = p;
}

snode *newNode(node *p)
{
    snode *l = (snode*)malloc(sizeof(snode));
    l->address = p;
    l->next = NULL;
    return l;
}

snode *top = NULL;

void push(node *p)
{
    if(top == NULL)
    {
        snode *l = newNode(p);
        top = l;
    }
    else
    {
        snode *l = newNode(p);
        l->next = top;
        top = l;
    }
}

int isempty()
{
    if(top == NULL)
        return 1;
    else return 0;
}

node *pop()
{
    //node *x = NULL;
    if(top == NULL)
        return NULL;
    else
    {
        node *x = top->address;
        top = top->next;
        return x;
    }
}

void createGraph(graph *g,FILE *inp)
{
    //printf("hello ");
    fscanf(inp,"%d",&g->nov);
    g->adj = (node **)malloc((g->nov + 1)*sizeof(node*));
    g->visited = (int *)malloc((g->nov + 1)*sizeof(int));

    int i,j,t;
    node *temp;
    for(i = 1;i<=g->nov;i++)
    {
        temp = createNode(i);
        g->adj[i] = temp;
        g->visited[i] = 0;
    }

    for(i = 1;i<=g->nov;i++)
    {
        int p;
        fscanf(inp,"%d",&p);
        for(j = 1;j<=g->nov;j++)
        {
            fscanf(inp,"%d",&t);
            if(t == 1)
            {
                temp = createNode(j);
                insertNode(g->adj[i],temp);
            }
        }
    }
    //printf("hello ");
}

void DFS_visit(node *u,graph *g,FILE *out)
{
    fprintf(out,"%d ",u->data);
    g->visited[u->data] = 1;
    node *temp = u;
    while(temp)
    {
        if(g->visited[temp->data] == 0)
        {
            DFS_visit(g->adj[temp->data],g,out);
        }
        temp = temp->next;
    }
    push(u);
    //printf("%p ",top->address);
}

void DFS(graph *g,FILE *out)
{
    int i;
    for(i = 1;i<=g->nov;i++)
    {
        if(g->visited[i] == 0)
        {
            DFS_visit(g->adj[i],g,out);
        }
    }
}

void topological(graph *g,FILE *out)
{
    fprintf(out,"\nThe topo sorting is :\n");

    while(top != NULL)
    {
        //printf("%p ",top);
        node *temp = pop();
        fprintf(out,"%d ",temp->data);
       // printf("%p ",temp);
    }

}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output_topo.txt","w");

    graph g;
    createGraph(&g,inp);
    DFS(&g,out);
    topological(&g,out);
    return 0;
}