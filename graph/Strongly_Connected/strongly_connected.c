#include<stdio.h>
#include<stdlib.h>
int time = 0;

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
    int *start_t;
    int *end_t;
}graph;

node *createNode(int d)
{
    node *p = (node *)malloc(sizeof(node));
    p->data = d;
    p->next = NULL;
    return p;
}

void insertNode(node *s,node *d)
{
    node *temp = s;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = d;
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
    g->start_t = (int *)malloc((g->nov + 1)*sizeof(int));
    g->end_t = (int *)malloc((g->nov + 1)*sizeof(int));
    int i,j,temp;
    node *t;
    for(i = 1;i<=g->nov;i++)
    {
        t = createNode(i);
        g->adj[i] = t;
        g->visited[i] = 0;
        g->start_t[i] = 0;
        g->end_t[i] = 0;
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

graph * transpose(graph *main_g)
{
    graph *trans_g = (graph*)malloc(sizeof(graph));
    printf("%d",main_g->nov);
    trans_g->nov = main_g->nov;
    //trans_g->nov = n;
    printf("%d",trans_g->nov);
    trans_g->adj = (node **)malloc((trans_g->nov + 1) * sizeof(node*));
    trans_g->visited = (int*)malloc((trans_g->nov + 1) * sizeof(int));
    trans_g->start_t = (int *)malloc((trans_g->nov + 1)*sizeof(int));
    trans_g->end_t = (int *)malloc((trans_g->nov + 1)*sizeof(int));
    

    int i;
    node *temp,*p;
    for(i = 1;i<=trans_g->nov;i++)
    {
        trans_g->adj[i] = createNode(i);
        trans_g->visited[i] = 0;
        trans_g->start_t[i] = 0;
        trans_g->end_t[i] = 0;
    }

    for(i = 1;i<=trans_g->nov;i++)
    {
        temp = main_g->adj[i];
        temp = temp->next;
        while(temp != NULL)
        {
            p = createNode(i);
            insertNode(trans_g->adj[temp->data],p);
            temp = temp->next;
        }
    }
    
    for(i = 1;i<=trans_g->nov;i++)
    {
        traversal(trans_g->adj[i]);
        printf("\n");
    }
    return trans_g;

}

int max(graph *g,int n)
{
    int m = 1;
    int i;
    for(i = 1;i<=n;i++)
    {
        printf("%d ",g->end_t[i]);
        if(g->end_t[i] > g->end_t[m])
            m = i;
    }
    printf("\n");
    g->end_t[m] = 0;
    return m;
}

void DFS_visit(graph *g,node *u,FILE*out)
{
    fprintf(out,"%d->",u->data);
    time ++;
    g->visited[u->data] = 1;
    g->start_t[u->data] = time;
    node *temp = u;
    while(temp)
    {
        if(g->visited[temp->data] == 0)
        {
            DFS_visit(g,g->adj[temp->data],out);
        }
        temp = temp->next;
    }
    time++;
    g->end_t[u->data] = time;
}

void DFS(graph *g,FILE *out)
{
    int i;
    for(i = 1;i<=g->nov;i++)
    {
        if(g->visited[i] == 0)
        {
            DFS_visit(g,g->adj[i],out);
        }
    }
}

void DFS_trans(graph *g,graph *gt,FILE *out)
{
    int i;
    fprintf(out,"\nThe strongly connected components are:\n");
    
    for(i = 1;i<=gt->nov;i++)
    {
        int m = max(g,g->nov);
        if(gt->visited[m] == 0)
        {
            
            DFS_visit(gt,gt->adj[m],out);
            fprintf(out,"\n");
        }
    }
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output_sc.txt","w");

    
    graph g;
    
    createGraph(&g,inp);
    //graph g2;
    

    graph * g2=transpose(&g);

    DFS(&g,out);
    fprintf(out,"\n");
    
    
    //DFS(g2,out);

    DFS_trans(&g,g2,out);

    return 0;
}