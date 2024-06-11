#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Mcm
{
	int **m;
	int **s;
	int *p;
}MCM;


MCM* matrix_chain_order(MCM *mcm,int n)
{
	int i,j,l,k,q;
	for(i = 1;i<= n;i++)
	{
		mcm->m[i][i]= 0;
	}
	
	for(l = 2;l<= n;l++)
	{
		for(i = 1;i<= n-l+1;i++)
		{
			j = i +l - 1;
			mcm->m[i][j] = INFINITY;
			for(k = i;k<=j-1;k++)
			{
				q = mcm->m[i][k] + mcm->m[k+1][j] + (mcm->p[i - 1])*(mcm->p[k])*(mcm->p[j]);
				if(q < mcm->m[i][j])
				{
					mcm->m[i][j] = q;
					mcm->s[i][j] = k;
				}
			}
		}
	}

	return mcm;
	

}




int main()
{
	FILE *inp = fopen("input_M.txt","r") ;
	FILE *out = fopen("output_M.txt","w");
	
	int k,n,i;
	fscanf(inp,"%d",&n);
	
	MCM mcm;
	
	mcm.m = (int **)malloc((n+1)*sizeof(int *));
	mcm.s = (int **)malloc((n + 1) * sizeof(int *));
	mcm.p = (int*)malloc((n+1) * sizeof(int));
	
	for(i = 0;i<= n;i++)
	{
		mcm.m[i] = (int *)malloc((n+1)*sizeof(int));
		mcm.s[i] = (int *)malloc((n+1)*sizeof(int));
	}
	
	for(i = 0;i<n;i++)
	{
		fscanf(inp,"%d",&(mcm.p[i]));
		fscanf(inp,"%d",&k);
	}
	
	mcm.p[n] = k;
	
	MCM *ans = matrix_chain_order(&mcm,n);
	
	for(i = 1;i<=n;i++)
	{
		for(k = 1;k<=n;k++)
		{
			fprintf(out,"%d ",ans->s[i][k]);
		}
		fprintf(out,"\n");
	}
	
	fprintf(out,"\n");
	for(i = 1;i<=n;i++)
	{
		for(k = 1;k<=n;k++)
		{
			fprintf(out,"%d ",ans->m[i][k]);
		}
		fprintf(out,"\n");
	}
	
		
	return 0;
}
	
