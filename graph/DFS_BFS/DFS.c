#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}node;

typedef struct graph
{
    int nov;
    node **adj;
    int *visited;
}graph;

node *createNode(int d)
{
    node *p = (node *)malloc(sizeof(node));
    p->data = d;
    p->next = NULL;
    return p;
}

void insertNode(node * s,node *p)
{
    node * temp = s;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = p;
}

void traversal(node *p)
{
    node *t = p;
    while(t)
    {
        printf("%d ",t->data);
        t = t->next;
    }
}

void createGraph(graph *g,FILE *inp)
{
    fscanf(inp,"%d",&g->nov);
    g->adj = (node**)malloc((g->nov + 1) * sizeof(node*));
    g->visited = (int *)malloc((g->nov + 1)*sizeof(int));
    int i,j,temp;
    node *t;
    for(i = 1;i<=g->nov;i++)
    {
        t = createNode(i);
        g->adj[i] = t;
        g->visited[i] = 0;
    }

    for(i = 1;i<=g->nov;i++)
    {
        int p;
        fscanf(inp,"%d",&p);
        for(j = 1;j<=g->nov;j++)
        {
            fscanf(inp,"%d",&temp);
            if(temp == 1)
            {
                t = createNode(j);
                insertNode(g->adj[i],t);
            }
        }
    }

    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i]);
        printf("\n");
    }
}

void DFS_visit(node *u,graph*g,FILE *out)
{
    fprintf(out,"%d ",u->data);
    g->visited[u->data] = 1;
    int i,j,t;
    while(u)
    {
        if(g->visited[u->data] == 0)
        {
            DFS_visit(g->adj[u->data],g,out);
        }
        u = u->next;
    }
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

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    graph g;
    createGraph(&g,inp);
    DFS(&g,out);
    return 0;
}