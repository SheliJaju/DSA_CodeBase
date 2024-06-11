#include<stdio.h>
#include<stdlib.h>

typedef struct Arrays
{
    int s;
    int *p;
}array;

int *merge(int *a,int *b,int size1,int size2)
{
    int i = 0,j = 0,k = 0;
    int *fin = (int *)malloc((size1 + size2)*sizeof(int));
   
    while(i < size1 && j < size2)
    {
        if(a[i] < b[j])
        {
            fin[k] = a[i];
            i++;
            k++;
        }
        else
        {
            fin[k] = b[j];
            j++;
            k++;
        }
    }

    while(i < size1)
    {
        fin[k] = a[i];
        i++;
        k++;
    }

    while(j < size2)
    {
        fin[k] = b[j];
        j++;
        k++;
    }

    return fin;

}

int main()
{
    FILE *inp = fopen("inp1.txt","r");
    FILE *out = fopen("out1.txt","w");

    int k,i,j;
    fscanf(inp,"%d",&k);

    array arr[k];
    for(i = 0;i<k;i++)
    {
        fscanf(inp,"%d",&arr[i].s);
        arr[i].p = (int*)malloc((arr[i].s) * sizeof(int));
        for(j = 0;j< arr[i].s;j++)
            fscanf(inp,"%d",&arr[i].p[j]);
    }

    int *f,*n;
    f = merge(arr[0].p , arr[1].p , arr[0].s ,arr[1] .s);

    int len = arr[0].s + arr[1].s;

    for(i = 2;i <k;i++)
    {
        n = merge(f,arr[i].p,len,arr[i].s);
        f = n;
        len = len + arr[i].s;
    }

    fprintf(out,"The sorted array after merging k sorted arrays are:\n");
    for(i = 0;i<len;i++)
    {
        
        fprintf(out,"%d ",f[i]);

    }
    return 0;
}