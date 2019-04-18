#include<stdio.h>
#include<stdlib.h>
#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int currenttime=3,runningtime=0,ALLEXIT=0,TimeQuantum,CT=1,n;
struct Proc 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect;
	struct Proc *prev;
	struct Proc *next;
} *pa;
int chpp;
struct Queue
{
	struct Proc *front ,*rear;
}*ReadyQueue;

void enqueue(struct Proc *p)
{
	if(ReadyQueue->rear==NULL)
	{
		ReadyQueue->rear=p;
		ReadyQueue->front=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->timeleft<ReadyQueue->front->timeleft)
		{
			p->next=ReadyQueue->front;
			ReadyQueue->front->prev=p;
			ReadyQueue->front=p;
		}
               else if(p->timeleft==ReadyQueue->front->timeleft)
		{
			p->next=ReadyQueue->front->next;
			p->prev=ReadyQueue->front;
			ReadyQueue->front->next=p;
                         if(p->next!=NULL)
                      {
                        p->next->prev=p;
                      }
		}
		else if(p->timeleft>ReadyQueue->rear->timeleft)
		{
			p->next=NULL;
			ReadyQueue->rear->next=p;
			p->prev=ReadyQueue->rear;
			ReadyQueue->rear=p;
		}
		else
		{
                   struct Proc *start=ReadyQueue->front->next;
		   while(start->timeleft<p->timeleft)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& p->timeleft==start->timeleft)
                   {
                          p->next=start->next;
                          start->next=p;
                          p->prev=start;
                      
                   }
                  else
               {
		   (start->prev)->next=p;
		   p->next=start;
		   p->prev=start->prev;
		   start->prev=p;
                }

		}
	}
}
struct Proc *  deQueue()
{
     if(ReadyQueue->front==NULL)
     {
	     return NULL;
     }
     struct Proc * temp=ReadyQueue->front;
     ReadyQueue->front=ReadyQueue->front->next;
     temp->next=NULL;
     if(ReadyQueue->front==NULL)
     {
	     ReadyQueue->rear=NULL;
     }
     return temp;
}
void checkqueue()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(pa[i].state == NEW && currenttime>=pa[i].at)
		   {      
			   
			   enqueue(&pa[i]);
			   pa[i].state=READY;
			   
                    }
                  if(pa[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  ALLEXIT=1; 
		  
	   }
}
int main()
{


ReadyQueue =(struct Queue*) malloc(sizeof(struct Queue));
	printf("Please enter No of processes to schedule");
	scanf("%d",&n);
	printf("\n Please Enter Time qunatum");
	scanf("%d",&TimeQuantum);
	pa=(struct Proc *)malloc(sizeof(struct Proc)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process",(i+1));
	     scanf("%d",&(pa[i].pid));
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(pa[i].at));
	     printf("\n Enter Execution time For %d Process",(i+1));
	     scanf("%d",&(pa[i].timeleft)); 
	     
            pa[i].exect=pa[i].timeleft;
	    pa[i].state=NEW;
	        
	}
 struct Proc key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = pa[i]; 
        j = i - 1; 
  
        while (j >= 0 && pa[j].at > key.at) { 
            pa[j + 1] = pa[j]; 
            j = j - 1; 
        } 
        pa[j + 1] = key; 
    } 

struct Proc *pr;
while(1)
{
        checkqueue();
        if(ALLEXIT==1)
        {

                    break;      
        }
        
        if(ReadyQueue->front!=NULL && CT==1)
	{
             runningtime=1;
	     pr=deQueue();
             pr->state=RUNNING;
             pr->timeleft--;
	     currenttime++;
             if(runningtime==pr->exect)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               CT=0;
              }
	}
        else if(CT==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             runningtime++;
             pr->timeleft--;
            currenttime++;

             if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
             else if(runningtime==TimeQuantum)
             {
                pr->state=READY;
                enqueue(pr);
                CT=1;
              }
            else
          { 
              CT=0;
	  }

          
             
          
	}
else
{
currenttime++;
}
}
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\nct=%d\ntat=%d\nwt=%d",pa[i].pid,pa[i].ct,pa[i].tat,pa[i].wt);
           sumwt+=pa[i].wt;
           sumtat+=pa[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \n Average WT=%f",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
