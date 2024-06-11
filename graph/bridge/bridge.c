#include<stdio.h>
#include<stdlib.h>
int time = 0;

typedef struct Node
{
    int data;
    struct Node *next;
}node;

typedef struct edge
{
    node *s;
    node *d;
}edge;

typedef struct Graph
{
    int nov;
    node **adj;
    edge **E;
    int noe;
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
    int c = 0;
    while(temp->next != NULL)
    {
    	if(temp->data != d->data)
    	{
        	temp = temp->next;
        }
        else
        {
        	c = 1;
        	break;
        }
    }
    if(c == 0 && temp->data != d->data)
    	temp->next = d;
    
    /*temp = d;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = s;*/
    
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

edge *makedge(node *src,node *des)
{
    edge *e = (edge *)malloc(sizeof(edge));
    e->s = src;
    e->d = des;
    return e;
}

void createGraph(graph *g,FILE *inp)
{
    fscanf(inp,"%d",&g->nov);
    g->adj = (node**)malloc((g->nov + 1) * sizeof(node*));
    g->visited = (int *)malloc((g->nov + 1)*sizeof(int));
    g->start_t = (int *)malloc((g->nov + 1)*sizeof(int));
    g->end_t = (int *)malloc((g->nov + 1)*sizeof(int));

    g->noe = 1;
    g->E = (edge **)malloc((g->noe)*sizeof(edge*));
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
        /*int p;
        fscanf(inp,"%d",&p);*/
        for(j = 1;j<=g->nov;j++)
        {
            fscanf(inp,"%d",&temp);
            if(temp == 1)
            {
                t = createNode(j);
                insertNode(g->adj[i],t);
                t = createNode(i);
                insertNode(g->adj[j],t);

                g->noe ++;
                g->E = (edge **)realloc(g->E,(g->noe)*sizeof(edge*));
                g->E[g->noe - 1] = makedge(t,g->adj[j]);
            }
        }
    }

    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i]);
        printf("\n");
    }
}

void DFS_visit(graph *g,node *u,edge *del_e,FILE*out)
{
    //fprintf(out,"%d->",u->data);
    time ++;
    g->visited[u->data] = 1;
    g->start_t[u->data] = time;
    node *temp = u;
    while(temp)
    {
        if(g->visited[temp->data] == 0 && ((u->data != del_e->s->data || temp->data != del_e->d->data) && (u->data != del_e->d->data || temp->data != del_e->s->data)))
        {
            DFS_visit(g,g->adj[temp->data],del_e,out);
        }
        temp = temp->next;
    }
    time++;
    g->end_t[u->data] = time;
}

void DFS(graph *g,FILE *out)
{
    int i,j,k;
    
   /*for(i = 1;i<=g->nov;i++)
    {
     	g->visited[i] = 0;
    }*/
    for(i = 1;i<=g->noe - 1;i++)
    {
    	
    	int count = 0;
    	for(k = 1;k<=g->nov;k++)
    	{
     		g->visited[k] = 0;
    	}
    	for(j = 1;j<=g->nov;j++)
    	{
		    if(g->visited[j] == 0)
		    {
		    	count ++;
		        DFS_visit(g,g->adj[j],g->E[i],out);
		        printf("deleted edge is : %d -> %d",g->E[i]->s->data,g->E[i]->d->data);
                printf("\n");
		    }
        }
        if(count > 1)
    		fprintf(out,"%d->%d ",g->E[i]->s->data,g->E[i]->d->data);
    }
    
    
}


int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    
    graph g;
    
    createGraph(&g,inp);
    
    fprintf(out,"The bridges in the graph: ");
    DFS(&g,out);
    
    return 0;
 }
