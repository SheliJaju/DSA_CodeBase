#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct graph
{
    int nov;
    node **adj;
    int **weight;
} graph;

node *createNode(int d)
{
    node *p = (node *)malloc(sizeof(node));
    p->data = d;
    p->next = NULL;
    return p;
}

void insertNode(node *s, node *p)
{
    node *temp = s;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = p;
}

void traversal(node *p)
{
    node *t = p;
    while (t)
    {
        printf("%d ", t->data);
        t = t->next;
    }
}

void createGraph(graph *g, FILE *inp)
{
    fscanf(inp, "%d", &g->nov);
    g->adj = (node **)malloc((g->nov + 1) * sizeof(node *));
    g->weight = (int **)malloc((g->nov + 1) * sizeof(int *));
    int i, j, temp;
    for (i = 1; i <= g->nov; i++)
    {
        g->weight[i] = (int *)malloc((g->nov + 1) * sizeof(int));
    }
    node *t;
    for (i = 1; i <= g->nov; i++)
    {
        t = createNode(i);
        g->adj[i] = t;
    }

    for (i = 1; i <= g->nov; i++)
    {
        for (j = 1; j <= g->nov; j++)
        {
            fscanf(inp, "%d", &temp);
            if (temp != 0)
            {
                g->weight[i][j] = temp;
                t = createNode(j);
                insertNode(g->adj[i], t);
            }
            else if (i != j && temp == 0)
            {
                g->weight[i][j] = 20000;
            }
            else
            {
                g->weight[i][j] = 0;
            }
        }
    }

    // for (i = 1; i <= g->nov; i++)
    // {
    //     traversal(g->adj[i]);
    //     printf("\n");
    // }
    // for (i = 1; i <= g->nov; i++)
    // {
    //     for (j = 1; j <= g->nov; j++)
    //     {
    //         printf("%d ", g->weight[i][j]);
    //     }
    //     printf("\n");
    // }
}

void FW(graph *g, FILE *inp, FILE *out)
{
    int current[g->nov + 1][g->nov + 1];
    int previous[g->nov + 1][g->nov + 1];
    int parent[g->nov + 1][g->nov+1];
    int i, j, k;
    for (i = 1; i <= g->nov; i++)
    {
        for (j = 1; j <= g->nov; j++)
        {
            current[i][j] = 2000;
            previous[i][j] = g->weight[i][j];
            if(g->weight[i][j] != 2000 && g->weight[i][j] != 0)
            {
                parent[i][j] = i;
            }
            else parent[i][j] = 0;
        }
    }
    for (k = 1; k <= g->nov; k++)
    {
        for (i = 1; i <= g->nov; i++)
        {
            for (j = 1; j <= g->nov; j++)
            {
                if (previous[i][j] > previous[i][k] + previous[k][j])
                {
                    current[i][j] = previous[i][k] + previous[k][j];
                    parent[i][j] = k;
                }
                else
                {
                    current[i][j] = previous[i][j];
                }
            }
        }
        // for (i = 1; i <= g->nov; i++)
        // {
        //     for (j = 1; j <= g->nov; j++)
        //     {
        //         printf("%d ", current[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
        for (i = 1; i <= g->nov; i++)
        {
            for (j = 1; j <= g->nov; j++)
            {
                previous[i][j] = current[i][j];
                current[i][j] = 2000;
            }
        }
    }

    fprintf(out,"The shortest path is :\n");
    for (i = 1; i <= g->nov; i++)
    {
        for (j = 1; j <= g->nov; j++)
        {
            fprintf(out, "%d ", previous[i][j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out,"\nThe shortest path is via:\n");
    for (i = 1; i <= g->nov; i++)
    {
        for (j = 1; j <= g->nov; j++)
        {
            fprintf(out, "%d ", parent[i][j]);
        }
        fprintf(out, "\n");
    }
}

int main()
{
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    graph g;
    createGraph(&g, inp);
    FW(&g, inp, out);
    return 0;
}