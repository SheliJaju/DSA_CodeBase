#include<stdio.h>
#include<stdlib.h>

typedef struct Items
{
    int val;
    int weight;
}item;

int knaps(int noi,int cap,item *s,FILE *out)
{
    int v[noi + 1][cap + 1];
    int k[noi + 1][cap + 1];
    int i,j;
    for(i = 0;i<= noi;i++)
    {
        for(j = 0;j<=cap;j++)
        {
            v[i][j] = 0;
            k[i][j] = 0;
        }
    }

    for(i = 1;i<= noi;i++)
    {
        for(j = 1;j<= cap;j++)
        {
            if(j >= s[i].weight)
            {
                if(v[i-1][j] > s[i].val + v[i-1][j - s[i].weight])
                    v[i][j] = v[i-1][j];
                else
                {
                    v[i][j] = s[i].val + v[i-1][j - s[i].weight];
                    k[i][j] = 1;
                }
            }
        }
    }

    fprintf(out,"The items picked are: ");
    int key = cap;
    for(i = noi;i>=1;i--)
    {
        if(k[i][key] == 1 && key >= s[i].weight)
        {
            fprintf(out,"%d ",i);
            key = key - s[i].weight;
        }
    }
    return v[noi][cap];
    //return 1;
}


int main()
{
    FILE *inp = fopen("input_k.txt","r");
    FILE *out = fopen("output_k.txt","w");

    int noi,cap;
    fscanf(inp,"%d",&noi);
    fscanf(inp,"%d",&cap);

    item s[noi + 1];
    int i;
    for(i = 1;i<=noi;i++)
    {
        fscanf(inp,"%d",&s[i].val);
        fscanf(inp,"%d",&s[i].weight);
    }

    for(i = 1;i<=noi;i++)
    {
        printf("%d ",s[i].val);
        printf("%d",s[i].weight);
        printf("\n");
    }

    i = knaps(noi,cap,s,out);
    fprintf(out,"\nThe max value obtained is %d",i);
    return 0;
}