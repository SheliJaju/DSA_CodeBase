#include<stdio.h>
#include<stdlib.h>

typedef struct Activity
{
	int s_t;
	int e_t;
}event;

typedef struct Max_Act
{
    int count;
    int finish;
    event** activities;
}L;

void activitySelection(event** eventsArr,int noe,FILE* out)
{

	for(int i=0;i<noe;i++)
    {
        for(int j=0;j<noe -i-1;j++)
        {
            if(eventsArr[j]->s_t > eventsArr[j+1]->s_t)
            {
            event* temp = eventsArr[j];
            eventsArr[j] = eventsArr[j+1];
            eventsArr[j+1] = temp;

            }
        }
    }

    L** non_conf_act = (L**)malloc(noe*sizeof(L*));
    for(int i=0;i<noe;i++)
    {
        non_conf_act[i] = (L*)malloc(sizeof(L));
        non_conf_act[i]->activities = (event**)malloc(noe*sizeof(event*));
        for(int j=0;j<noe;j++)
        {
            non_conf_act[i]->activities[j] = (event*)malloc(sizeof(event));
        }
        non_conf_act[i]->count = 0;
        non_conf_act[i]->finish = 0;
    }

    for(int i=0;i<noe;i++)
    {
        int index = 0;
        for(int j=0;j<i;j++)
        {
            if(non_conf_act[j]->finish <= eventsArr[i]->s_t && non_conf_act[j]->count > non_conf_act[i]->count)
            {
                non_conf_act[i] = non_conf_act[j];
                index = non_conf_act[j]->count;
            }
        }
        non_conf_act[i]->count++;
        non_conf_act[i]->activities[index]->s_t = eventsArr[i]->s_t;
        non_conf_act[i]->activities[index]->e_t = eventsArr[i]->e_t;
        non_conf_act[i]->finish = eventsArr[i]->e_t;

    }

    printf("activities selected are: \n");
    for(int i=0;i<non_conf_act[noe-1]->count;i++)
    {
        printf("{%d,%d} ",non_conf_act[noe-1]->activities[i]->s_t,non_conf_act[noe-1]->activities[i]->e_t);
    }
    printf("\n");

    return;



}


int main()
{
	FILE* inp = fopen("input.txt","r");
	FILE* out = fopen("output.txt","w");
	
	int noa;
	fscanf(inp,"%d",&noa);
	
	event** eventsArr = (event**)malloc(noa*sizeof(event*));
	for(int i=0;i<noa;i++)
	{
		eventsArr[i] = (event*)malloc(sizeof(event));
		eventsArr[i]->s_t = 0;
		eventsArr[i]->e_t = 0;
	}
	
	for(int i=0;i<noa;i++)
	{
		fscanf(inp,"%d ",&eventsArr[i]->s_t);
		fscanf(inp,"%d",&eventsArr[i]->e_t);
	}
	
    activitySelection(eventsArr,noa,out);
	
	
	
	
	return 0;
	
}
