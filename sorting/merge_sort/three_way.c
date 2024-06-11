#include<stdio.h>

void merge(int low,int mid_1,int mid_2,int high,int*a)
{
    int i = low;
    int j = mid_1 + 1;
    int k = mid_2 +1;
    int l = 0;
    int b[high - low +1];

    while(i <= mid_1 && j<= mid_2 && k<= high)
    {
        if(a[i] < a[j] && a[i] < a[k])
        {
            b[l] = a[i];
            i++;
            l++;
        }

        else if(a[j] < a[i] && a[j] < a[k])
        {
            b[l] = a[j];
            j++;
            l++;
        }

        else if(a[k] < a[j] && a[k] < a[i])
        {
            b[l] = a[k];
            k++;
            l++;
        }
    }

    while(i <= mid_1 && j <= mid_2)
    {
        if(a[i] < a[j])
        {
            b[l] = a[i];
            i++;
            l++;
        }
        else
        {
            b[l] = a[j];
            j++;
            l++;
        }
    }

    while(i <= mid_1 && k <= high)
    {
        if(a[i] < a[k])
        {
            b[l] = a[i];
            i++;
            l++;
        }
        else
        {
            b[l] = a[k];
            k++;
            l++;
        }
    }

    while(j <= mid_2 && k <= high)
    {
        if(a[k] < a[j])
        {
            b[l] = a[k];
            k++;
            l++;
        }
        else
        {
            b[l] = a[j];
            j++;
            l++;
        }
    }

    while(i <= mid_1)
    {
        b[l] = a[i];
        i++;
        l++;
    }

    while(j <= mid_2)
    {
        b[l] = a[j];
        j++;
        l++;
    }

    while(k <= high)
    {
        b[l] = a[k];
        k++;
        l++;
    }

    for(i = low;i<=high;i++)
    {
        
        a[i] = b[i - low];
    }

    return;
}

void merge_sort(int low ,int high , int *a)
{
    
    if(low < high)
    {
        
        int mid_1 = low + (high - low)/3;
        int mid_2  = mid_1 + (high + low)/3;
        if(mid_2 > high)
            mid_2 = mid_1 + 1;
        

        merge_sort(low,mid_1 ,a);
        merge_sort(mid_1 + 1,mid_2  ,a);
        merge_sort(mid_2 + 1 ,high,a);
        merge(low,mid_1,mid_2,high,a);
        for(int i = low;i<= high;i++)
            printf("%d ",a[i]);
        printf("\n");
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
    

    fprintf(out,"The sorted array using three way merge sort is:\n");
    for(i = 0;i<size;i++)
    {
        fprintf(out,"%d ",a[i]);
    }

    fprintf(out,"\nProgram ended! Have a nice day! ");
    return 0;
}