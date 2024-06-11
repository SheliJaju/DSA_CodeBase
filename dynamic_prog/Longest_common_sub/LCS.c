#include<stdio.h>
#include<stdlib.h>

// 1- upper
// -1 - diagonal
// 2 - side

int LCS(int m,int *x,int n,int *y,FILE *out)
{
    int i,j;
    int c[m+1][n+1];
    int track[m+1][n+1];

    for(i = 1;i<= m;i++)
    {
        c[i][0] = 0;
        track[i][0] = 0;
    }

    for(i = 1;i<= n;i++)
    {
        c[0][i] = 0;
        track[0][i] = 0;
    }

    for(i = 1;i<=m;i++)
    {
        for(j = 1;j<=n;j++)
        {
            if(x[i] == y[j])
            {
                c[i][j] = c[i-1][j-1] + 1;
                track[i][j] = -1;
            }
            else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                track[i][j] = 1;
            }
            else{
                c[i][j] = c[i][j-1];
                track[i][j] = 2;
            }
        }
    }

    for(i = 1;i<=m;i++)
    {
        for(j = 1;j<=n;j++)
        {
            printf("%d ",track[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(i = 0;i<=m;i++)
    {
        for(j = 0;j<=n;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    //int p[c[m][n]];

    fprintf(out,"The common items are : ");
    i = m;
    j = n;
    int tm,tn;
    while(i != 0 && j != 0)
    {
        tm = i;
        tn = j;
        if(track[i][j] == -1)
        {
            i = i-1;
            j = j-1;
            
        }
        if(track[i][j] == 1)
        {
            i = i-1;
            j = j;
        }
        if(track[i][j] == 2)
        {
            i = i;
            j = j-1;
        }
        if(track[tm][tn] == -1)
        {
            fprintf(out,"%d ",x[tm]);
        }
    }
    return c[m][n];

}

int main()
{
    FILE *inp = fopen("input_lcs.txt","r");
    FILE *out = fopen("output_lcs.txt","w");

    int m,n,i;
    fscanf(inp,"%d",&m);
    int x[m+1];
    for(i = 1;i<= m;i++)
    {
        fscanf(inp,"%d",&x[i]);
    }

    fscanf(inp,"%d",&n);
    int y[n+1];
    for(i = 1;i<= n;i++)
    {
        fscanf(inp,"%d",&y[i]);
    }
    
    i = LCS(m,x,n,y,out);
    fprintf(out,"\nThe length of longest common subsequemce is : %d",i);

    return 0;
}
