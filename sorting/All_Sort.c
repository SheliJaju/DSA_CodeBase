#include<stdio.h>
#include "bubble_sort.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "count_sort.h"
#include "heap_sort.h"

int main()
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);

    int a[size],i,n = 0,x;

    while(fscanf(inp,"%d",&a[n]) != EOF)
        n++;


    while(1)
    {
        printf("PRESS 1 FOR BUBBLE SORT\n");
        printf("PRESS 2 FOR SELECTION SORT\n");
        printf("PRESS 3 FOR INSERTION SORT\n");
        printf("PRESS 4 FOR COUNT SORT\n");
        printf("PRESS 5 FOR MERGE SORT\n");
        printf("PRESS 6 FOR HEAP SORT\n");
        scanf("%d",&x);

        if(x == 0)
        {
            printf("Program ended\nHave a nice day!");
            break;
        }

        switch(x)
        {
            case 1:
            Bubble_Sort(size,a);
            fprintf(out,"the sorting using bubble sort:\n");
            for(i =0 ;i<size;i++)
            {
                fprintf(out,"%d ",a[i]);
            }

            break;

            case 2:
            Selection_Sort(size,a);
            fprintf(out,"the sorting using selection sort:\n");
            for(i =0 ;i<size;i++)
            {
                fprintf(out,"%d ",a[i]);
            }

            break;

            case 3:
            Insertion_Sort(size,a);
            fprintf(out,"\nthe sorting using insertion sort:\n");
            for(i =0 ;i<size;i++)
            {
                fprintf(out,"%d ",a[i]);
            }

            break;

            case 4:
            Count_Sort(size,a);
            fprintf(out,"\nthe sorting using count sort:\n");
            for(i =0 ;i<size;i++)
            {
                fprintf(out,"%d ",a[i]);
            }

            break;

            case 5:
            Heap_Sort(size,a);
            fprintf(out,"\nthe sorting using heap sort:\n");
            for(i =1 ;i<=size;i++)
            {
                fprintf(out,"%d ",a[i]);
            }

            break;

            

        }
    }
    return 0;
}