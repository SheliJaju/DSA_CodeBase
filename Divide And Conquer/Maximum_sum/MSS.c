#include<stdio.h>
#include<stdlib.h>

typedef struct MAX_SUM
{
    int l;
    int h;
    int no;
}maxSum;

maxSum* MCS(int low,int mid,int high,int *a)
{
    int lSum = -1000;
    int sum = 0,i,max_right,max_left;
    for(i = mid;i>=0;i--)
    {
        sum = sum + a[i];
        if(sum > lSum)
        {
            lSum = sum;
            max_left = i;
        }
    }

    int rSum = -1000;
    sum = 0;
    for(i = mid + 1;i<=high;i++)
    {
        sum = sum + a[i];
        if(sum > rSum)
        {
            rSum = sum;
            max_right = i;
        }
    }
    maxSum *p = (maxSum *)malloc(sizeof(maxSum));
    p->l = max_left;
    p->h = max_right;
    p->no = lSum + rSum;
    return p;
}

maxSum* MSS(int low,int high,int *a)
{
   maxSum *s = (maxSum *)malloc(sizeof(maxSum));

    if(high == low)
    {
        s->l = low;
        s->h = high;
        s->no = a[low];
        return s;
    }
        
    else
    {
        int mid = (low + high)/2;

        maxSum *t = MSS(low,mid,a);
        int left_low = t->l;
        int left_high = t->h;
        int left_sum = t->no;

        t = MSS(mid+1,high,a);
        int right_low = t->l;
        int right_high = t->h;
        int right_sum = t->no;

        t = MCS(low,mid,high,a);
        int cross_low = t->l;
        int cross_high = t->h;
        int cross_sum = t->no;

        if(left_sum >= right_sum && left_sum >= cross_sum)
        {
            s->l = left_low;
            s->h = left_high;
            s->no = left_sum;
            return s;
        }

        else if(right_sum >= left_sum && right_sum >= cross_sum)
        {
            s->l = right_low;
            s->h = right_high;
            s->no = right_sum;
            return s;
        }

        else
        {
            s->l = cross_low;
            s->h = cross_high;
            s->no = cross_sum;
            return s;
        }
    }
}

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);
    int a[size];

    int n = 0;
    while(fscanf(inp,"%d",&a[n]) != EOF){n++;}

    maxSum *p = MSS(0,size-1,a);
    fprintf(out,"The maximum sum subarray is found between %d and %d index\nThe maximum sum is %d.",p->l,p->h,p->no);

    return 0;
}