#include<stdio.h>
#include<math.h>

void merge(int low,int high,int *a)
{
    int mid = (low + high)/2;
    int i = low;
    int j = mid + 1;
    int k = 0;

    printf("%d %d\n",low,high);
    //printf("%d %d",i,j);
    int b[high - low + 1];
    while(i <= mid && j <= high)
    {
        //printf("im in while of merge\n");
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

    while(i  <= mid)
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

    for(i = low;i<=high;i++)
    {
        printf("\n%d ",b[i-low]);
        a[i] = b[i-low];
    }
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);
    int a[size];

    int i = 0,j = 1,count = 0;
    while(fscanf(inp,"%d",&a[i]) != EOF){i++;}

    do
    {
        //printf("hello\n");
        i = 0;
        count ++;
        while(i<size)
        {
            if(i+j < size)
            {
                merge(i,i+j,a);
                i = i+j+1;
            }
            else
            {
                merge(i,size-1,a);
                i = size;
            }
        }
        j = j+pow(2,count);
    }while(j<size);


    fprintf(out,"the sorted array is:\n");
    for(i = 0;i<size;i++)
    {
        fprintf(out,"%d ",a[i]);
    }
    return 0;
}