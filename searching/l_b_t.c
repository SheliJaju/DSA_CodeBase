#include<stdio.h>

void sort(int n,int *a)
{
	int i,j,temp;
	for(i =0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	return;
}

int BinarySearch(int low,int high,int *a,int ele)
{
	if(low < high)
	{

		int mid = low + (high - low)/2;
		if(a[mid] == ele)
			return mid;
		else if(ele < a[mid])
			return BinarySearch(low,mid - 1,a,ele);
		else if(ele > a[mid])
			return BinarySearch(mid + 1,high,a,ele);
	}
	return -1;
}

int TernerySearch(int low,int high,int *a,int ele)
{
    if(low<high)
    {
        int mid_1 = low + (high - low)/3;
        int mid_2 = mid_1 + (high+low)/3;

        if(a[mid_1] == ele)
            return mid_1;
        else if(a[mid_2] == ele)
            return mid_2;
        else if(a[mid_1] > ele)
            return TernerySearch(low,mid_1 - 1,a,ele);
        else if(a[mid_1] < ele < a[mid_2])
            return TernerySearch(mid_1 + 1,mid_2 - 1,a,ele);
        else if(a[mid_2] < ele)
            return TernerySearch(mid_2 + 1,high,a,ele);
    }
    return -1;
}

int linear_search(int *a,int size,int ele)
{
    int i;
    for(i = 0;i<size;i++)
    {
        if(a[i] == ele)
            return i;
    }
    return -1;
}

int main()
{
    FILE * inp = fopen("input.txt","r");
    FILE * out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);

    int a[size],i=0;
    while(fscanf(inp,"%d",&a[i]) != EOF)
        i++;

    int ele;
    printf("enter the element to be searched: ");
    scanf("%d",&ele);

    int l = linear_search(a,size,ele);
    if(l > 0)
    {
        fprintf(out,"using linear search the element is found at index: %d\n",l);
    }
    else fprintf(out,"element no found\n");

    sort(size,a);

    int b = BinarySearch(0,size-1,a,ele);
    if(b > 0)
    {
        fprintf(out,"using binary search the element is found at index: %d\n",b);
    }
    else fprintf(out,"element no found\n");

    int t = TernerySearch(0,size - 1,a,ele);
    if(t > 0)
    {
        fprintf(out,"using ternery search the element is found at index: %d\n",t);
    }
    else fprintf(out,"element no found\n");

    fprintf(out,"Programm ended!\nHave a nice day");
    return 0;

       
}