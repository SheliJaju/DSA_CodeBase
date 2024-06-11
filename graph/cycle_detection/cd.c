#include<stdio.h>
#include<stdlib.h>

/*************************** Node creation ***************************/
typedef struct Node
{
    int data;
    struct Node *next;
}node;

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

void traversal(node *s,FILE *out)
{
    node *temp = s;
    while(temp)
    {
        fprintf(out,"%d ",temp->data);
        temp = temp->next;
    }
}

/************************** Graph creation **************************/
typedef struct Graph
{
    int nov;
    node **adj;
    int *visited;
}graph;

void createGraph(graph *g,FILE *inp,FILE *out)
{
    fscanf(inp,"%d",&g->nov);
    g->adj = (node **)malloc((g->nov) * sizeof(node*));
    g->visited = (int *)malloc((g->nov) * sizeof(int));

    int i,j,t;
    node *temp;

    for(i = 1;i<=g->nov;i++)
    {
        g->adj[i] = createNode(i);
        g->visited[i] = 0;
    }

    for(i = 1;i<=g->nov;i++)
    {
        for(j = 1;j<=g->nov;j++)
        {
            fscanf(inp,"%d",&t);
            if(t != 0)
            {
                temp = createNode(j);
                insertNode(g->adj[i],temp);
            }
        }
    }

    fprintf(out,"the graph is:\n");
    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i],out);
        fprintf(out,"\n");
    }
}
/******************* Queue Functions **************************/
typedef struct Queue
{
    int size;
    int front;
    int rear;
    node **que;
}queue;

void createQueue(queue *q,graph *g)
{
    q->front = q->rear = 0;
    q->size = g->nov ;
    q->que = (node **)malloc((q->size + 1) * sizeof(node *));
}

void enqueue(node *p,queue *q)
{
    if((q->rear + 1)%q->size == q->front)
        printf("queue is full");
    else
    {
        q->rear = (q->rear + 1)%q->size;
        q->que[q->rear] = p;
    }
}

node *dequeue(queue *q)
{
    node *x = NULL;
    if(q->front == q->rear)
        return NULL;
    q->front = (q->front + 1)%q->size;
    x = q->que[q->front];
    return x;
}

int isempty(queue *q)
{
    if(q->front == q->rear)
        return 1;
    else return 0;
}

/********************** Cylcle detection *********************/
int cd(queue *q,graph *g)
{
    enqueue(g->adj[1],q);

    node *temp;
    while(isempty(q) == 0)
    {
        temp = dequeue(q);
        g->visited[temp->data] = 1;
        temp = temp->next;
        while(temp)
        {
            if(g->visited[temp->data] == 1)
                return 1; 
            //if(g->visited[temp->data] == 0)
                enqueue(g->adj[temp->data],q);
            temp = temp->next;
        }
    }
    return 0;
}

/**************************** Main function **********************/
int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    graph g;
    createGraph(&g,inp,out);
    queue q;
    createQueue(&q,&g);

    int n = cd(&q,&g);
    if(n == 1)
        fprintf(out,"cycle is present in the graph");
    else
        fprintf(out,"No cycle present in the graph");
    return 0;
}