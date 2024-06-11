#include<stdio.h>
#include<stdlib.h>

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

void insertNode(node *s,node *p)
{
    node *temp = s;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp -> next = p;
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

/******************graph creation****************************/
typedef struct Graph
{
    int nov;
    node **adj;
    int *visited;
}graph;

void createGraph(graph *g,FILE *inp)
{
    fscanf(inp,"%d",&g->nov);
    g->adj = (node**)malloc((g->nov + 1)*sizeof(node*));
    g->visited = (int *)malloc((g->nov+1)*sizeof(int));

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

    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i]);
        printf("\n");
    }
}
/********************QUEUE FUNCTIONS**************************/
typedef struct Queue
{
    int front;
    int rear;
    int size;
    node **Que;
}queue;

void createQueue(graph *g,queue *q)
{
    q->size = g->nov;
    q->front = q->rear = 0;
    q->Que = (node **)malloc((q->size + 1) * sizeof(node*));
}

void enqueue(queue* que,node* n)
{
    if((que->rear+1)%que->size == que->front)
        printf("queue is full!\n");
    else
    {
        que->rear = (que->rear+1)%que->size;
        que->Que[que->rear] = n;
    }
    return;
}

node* dequeue(queue* que)
{
    node* x = NULL;
    if(que->rear == que->front)
        printf("queue is empty!\n");
    else
    {
        que->front = (que->front+1)%que->size;
        x = que->Que[que->front];
    }
    return x;
}

int isempty(queue *que)
{
    if(que->rear == que->front)
        return -1;
    else
        return 1;
}

/**********************BFS****************************/
void BFS(graph *g,queue *que,FILE *out)
{
    
    enqueue(que,g->adj[1]);

    node *temp;
    while(isempty(que) > 0)
    {
        temp = dequeue(que);
        fprintf(out,"%d ",temp->data);
        g->visited[temp->data] = 1;
        while(temp)
        {
            if(g->visited[temp->data] == 0)
                enqueue(que,g->adj[temp->data]);
            temp = temp->next;
        }
    }
}
/*******************MAIN FUNCTION*******************************/
int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output_BFS.txt","w");

    graph g;
    createGraph(&g,inp);

    queue que;
    createQueue(&g,&que);
    //printf("%d",que.size);
    //printf("%d",(g.adj[1])->data);

    BFS(&g,&que,out);

    return 0;
}