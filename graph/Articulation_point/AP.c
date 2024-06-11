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
                
                
            }
        }
    }

    for(i = 1;i<=g->nov;i++)
    {
        traversal(g->adj[i]);
        printf("\n");
    }
}

void DFS_visit(graph *g,node *u,int deleted,FILE*out)
{
    //fprintf(out,"%d->",u->data);
    time ++;
    g->visited[u->data] = 1;
    g->start_t[u->data] = time;
    node *temp = u;
    while(temp)
    {
        if(g->visited[temp->data] == 0 && temp->data != deleted)
        {
            DFS_visit(g,g->adj[temp->data],deleted,out);
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
    for(i = 1;i<=g->nov;i++)
    {
    	
    	int count = 0;
    	for(k = 1;k<=g->nov;k++)
    	{
     		g->visited[k] = 0;
    	}
    	for(j = 1;j<=g->nov;j++)
    	{
		    if((g->visited[j] == 0) && j != i)
		    {
		    	count ++;
		        DFS_visit(g,g->adj[j],i,out);
		        printf("count of %d is %d",i,count);
		    }
        }
        if(count > 1)
    		fprintf(out,"%d ",i);
    }
    
    
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    
    graph g;
    
    createGraph(&g,inp);
    
    fprintf(out,"The articulation point is: ");
    DFS(&g,out);
    
    return 0;
 }

