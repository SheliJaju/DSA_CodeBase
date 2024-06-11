#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Node
{
    int data;
    struct Node *next;
}node;

typedef struct Edge
{
    node *s;
    node *d;
    int w;
}edge;

typedef struct graph
{
    int nov;
    int noe;
    node **adj;
    int *visited;
    int *distance;
    node **parent;
    edge **E;
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

edge *makedge(node *src,node*des,int wei)
{
    edge *e = (edge *)malloc(sizeof(edge));
    e->s = src;
    e->d = des;
    e->w = wei;
    return e;
}


void createGraph(graph *g,FILE *inp)
{
    fscanf(inp,"%d",&g->nov);
    g->adj = (node**)malloc((g->nov + 1) * sizeof(node*));
    g->visited = (int *)malloc((g->nov + 1)*sizeof(int));
    g->distance = (int *)malloc((g->nov + 1)*sizeof(int));
    g->parent = (node**)malloc((g->nov + 1) * sizeof(node*));
    g->noe = 1;
    g->E = (edge**)malloc((g->noe)*sizeof(edge*));
    int i,j,temp;
    node *t;
    for(i = 1;i<=g->nov;i++)
    {
        t = createNode(i);
        g->adj[i] = t;
        g->visited[i] = 0;
        g->distance[i] = 10000;
        g->parent[i] = NULL;
    }

    for(i = 1;i<=g->nov;i++)
    {
        for(j = 1;j<=g->nov;j++)
        {
            fscanf(inp,"%d",&temp);
            if(temp != 0)
            {
                t = createNode(j);
                insertNode(g->adj[i],t);
                g->noe ++;
                g->E = (edge **)realloc(g->E,(g->noe)*sizeof(edge*));
                g->E[g->noe - 1] = makedge(g->adj[i],t,temp);
            }
        }
    }

    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i]);
        printf("\n");
    }

    // for(i = 1;i<=g->noe - 1;i++)
    // {
    //     printf("%d %d %d",g->E[i]->s->data,g->E[i]->d->data,g->E[i]->w);
    //     printf("\n");
    // }
    printf("\n%d ",g->noe -1);
}

void relax(graph *g,edge *e)
{
    if(g->distance[e->d->data] > g->distance[e->s->data] + e->w)
    {
        g->distance[e->d->data] = g->distance[e->s->data] + e->w;
        g->parent[e->d->data] = e->s;
    }
}

void Bellman(graph *g,int s)
{
    g->distance[s] = 0;
    int i,j;
    for(i = 1;i<=g->nov - 1;i++)
    {
        for(j = 1;j<=g->noe - 1;j++)
        {
            relax(g,g->E[j]);
        }

        // for(j = 1;j<=g->nov;j++)
        // {
        //     printf("%d ",g->distance[j]);
        //     printf("\n");
        // }
    }
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    graph g;
    createGraph(&g,inp);

    Bellman(&g,1);
    int i;
    fprintf(out,"The shortest distance to all vertices measured from vertex 1 are:\n");
    for(i = 1;i<=g.nov;i++)
    {
        fprintf(out,"%d ",g.distance[i]);
    }

    fprintf(out,"\nThe shortest path is to all the vertices is:\n");
    
    for(i = 2;i<=g.nov;i++)
    {
        fprintf(out,"%d ",g.parent[i]->data);
    }

    return 0;
}