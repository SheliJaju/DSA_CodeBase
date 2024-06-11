#include<stdio.h>
#include<stdlib.h>

typedef struct Items
{
	float ratio;
	int val;
	int weight;
}item;

int getMax(int noi,item *s)
{
	int max,i;
	max = 1;
	for(i = 1;i<= noi;i++)
	{
		if(s[i].ratio > s[max].ratio)
			max = i;
	}
	return max;
}
	

float f_knapsack(int cap,int noi,item *s,FILE *out)
{
	float max_val = 0;
	int i;
	while(cap > 0)
	{
		i = getMax(noi,s);
		if(cap >= s[i].weight)
		{
			cap = cap - s[i].weight;
			max_val = max_val + s[i].val;
			fprintf(out,"item no %d picked as a whole \n",i);
			s[i].ratio = 0;
		}
		else
		{
			max_val = max_val + (s[i].ratio)*cap;
			cap = 0;
			fprintf(out,"item no %d picked as a fraction\n",i);
		}
	}
	return max_val;
	
}


int main()
{
	FILE *inp = fopen("input.txt","r") ;
	FILE *out = fopen("output.txt","w");
	
	int noi,cap;
	fscanf(inp,"%d",&noi);
	fscanf(inp,"%d",&cap);
	
	item s[noi+1];
	int i;
	for(i = 1;i<=noi;i++)
	{
		fscanf(inp,"%d",&s[i].val);
		fscanf(inp,"%d",&s[i].weight);
		s[i].ratio = (float)(s[i].val)/(s[i].weight);
		printf("%f ",s[i].ratio);
	}
	
	float k = f_knapsack(cap,noi,s,out);
	fprintf(out,"The maximum value obtained is %f",k);
	
	return 0;
}
