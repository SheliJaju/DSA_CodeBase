void Count_Sort(int n,int *a)
{
    int i,max,j;
    max = a[0];
    for(i = 0;i<n;i++)
    {
        if(a[i]>max)
            max = a[i];
    }

    int b[max+1];
    for(i = 0;i<=max;i++)
    {
        b[i] = 0;
    }

    for(i = 0;i<n;i++)
    {
        b[a[i]] = b[a[i]] + 1;
    }

    i = 0;j = 0;
    while(i < max+1)
    {
        if(b[i] == 0)
            i++;
        else
        {
            while(b[i] != 0)
            {
                a[j] = i;
                b[i]--;
                j++;
            }
            i++;
        }
    }
    return;
}