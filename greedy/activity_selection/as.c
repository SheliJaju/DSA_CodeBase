#include<stdio.h>
#include<stdlib.h>

typedef struct Activity
{
	int act_no;
	int s_t;
	int e_t;
}activity;

void sort(int noa,activity *s)
{
	int i,j;
	activity temp;
	for(i = 1;i<= noa;i++)
	{
		for(j = 1;j<= noa-i-1;j++)
		{
			if(s[j].e_t > s[j+1].e_t)
			{
				temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		}
	}
	
}
	

void A_s(int noa,activity *s,FILE *out)
{
	/*int i = 1;
	int j;
	while(s[i].act_no <= noa)
	{
		fprintf(out,"%d ",s[i].act_no);
		for(j = i+1;j<= noa;j++)
		{
			if(s[j].s_t >= s[i].e_t)
			{
				i = j;
				break;
			}
		}
	}*/
	int j;
	fprintf(out,"%d timing :- %d-%d",s[1].act_no,s[1].s_t,s[1].e_t);
	int temp = s[1].e_t;
	
	for(j = 2;j<= noa;j++)
	{
		if(s[j].s_t >= temp)
		{
			fprintf(out,"\n");
			fprintf(out,"%d timing :- %d-%d",s[j].act_no,s[j].s_t,s[j].e_t);
			temp = s[j].e_t;
		}
	}
}


int main()
{
	FILE *inp = fopen("input.txt","r") ;
	FILE *out = fopen("output.txt","w");
	
	int noa;
	fscanf(inp,"%d",&noa);
	
	activity s[noa+1];
	int i;
	for(i = 1;i<=noa;i++)
	{
		fscanf(inp,"%d",&s[i].act_no);
		fscanf(inp,"%d",&s[i].s_t);
		fscanf(inp,"%d",&s[i].e_t);
	}
	
	fprintf(out,"The activity selected are: \n");
	sort(noa,s);
	A_s(noa,s,out);
	
	
	
	return 0;
}
