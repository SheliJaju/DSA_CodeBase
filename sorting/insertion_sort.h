void Insertion_Sort(int n,int *a)
{
    int i,j,key;
    for(i = 1;i<n;i++)
    {
        j = i-1;
        key = a[i];
        while(j >= 0 && key < a[j])
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
    return;
}