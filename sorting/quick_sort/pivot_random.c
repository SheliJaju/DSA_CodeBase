#include<stdio.h>
#include<stdlib.h>

int partition(int *a,int low,int high)
{
    int pi = low + (rand()%(high-low + 1));
     
    int pivot = a[pi];

    int i = low - 1;
    int j,temp;
    for(j = low;j<=high;j++)
    {
        if(j == pi && j!=high)
            j++;

        if(a[j] <= pivot)
        {
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i+1];
    a[i+1] = a[pi];
    a[pi] =temp;

    return i+1;
}

void quick_sort(int *a,int low,int high, FILE *out)
{
    if(low < high)
    {
        int part = partition(a,low,high);
        
        static int j = 0;
        fprintf(out,"the array after %d step is:\n",j+1);
        for(int i = low;i<=high;i++)
        {
            fprintf(out,"%d ",a[i]);
        }
        fprintf(out,"\n");
        j++;
        
        quick_sort(a,low,part - 1,out);
        quick_sort(a,part+1,high,out);
    }
    return;
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);

    int a[size];
    int i = 0;
    while(fscanf(inp,"%d",&a[i]) != EOF)
        i++;

    fprintf(out,"The sorted array using quick sort with pivot at random is:\n");
    quick_sort(a,0,size-1,out);
    for(i = 0;i<size;i++)
    {
        fprintf(out,"%d ",a[i]);
    }

    fprintf(out,"\nProgram ended ! Have a nice day!");

    return 0;
}