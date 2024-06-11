#include<stdio.h>

void merge(int low,int mid,int high,int *a)
{
    int i = low;
    int j = mid + 1;
    int k = 0;

    int b[high - low + 1];

    while(i <= mid && j <= high)
    {
        if(a[i] < a[j])
        {
            b[k] = a[i];
            i++;
            k++;
        }
        else
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }

    while(i <= mid)
    {
        b[k] = a[i];
        i++;
        k++;
    }

    while(j <= high)
    {
        b[k] = a[j];
        j++;
        k++;
    }

    for(i = low; i<= high;i++)
        a[i] = b[i - low];
    
    return;
}

void merge_sort(int low,int high,int *a)
{
    if(low < high)
    {
        
        int mid = low + (high - low)/2;
        merge_sort(low,mid,a);
        merge_sort(mid+1,high,a);
        merge(low,mid,high,a);
    }
    return;
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);

    int a[size],i =0;
    while(fscanf(inp,"%d",&a[i]) != EOF)
        i++;

    merge_sort(0,size-1,a);

    fprintf(out,"The sorted array using merge sort is:\n");
    for(i = 0;i<size;i++)
    {
        fprintf(out,"%d ",a[i]);
    }

    fprintf(out,"\nProgram ended! Have a nice day! ");
    return 0;
}
