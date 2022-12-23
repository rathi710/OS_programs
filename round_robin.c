#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct process
{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
    int rt;
    int start_time;
    int bt_remaining;
};

int findmax(int a, int b)
{
    return a>b?a:b;
}
int main()
{
    int n;
    printf("Enter the number of process:");
    scanf("%d", &n);

    struct process p[n];

    bool visited[100]={false};
    int current_time=0 ;
    int completed=0;
    int tq;

    int queue[100] , front =-1 , rear=-1;
    float sum_tat , sum_wt , sum_rt;

    printf("Enter the arrival time of process:");
    for(int i=0;i<n;i++){ 
        scanf("%d",&p[i].at);
        p[i].pid = i;
    }

    printf("Enter the burst time of process:");
    for(int i=0;i<n;i++){
        scanf("%d",&p[i].bt);
        p[i].bt_remaining=p[i].bt;
    }

    printf("\nEnter the time quantum value:"); scanf("%d", &tq);

    //sort according to arrival time of processes
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].at > p[j+1].at)
            {
                struct process temp  = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    //put index of first process into the ready queue and mark visited
    front=rear=0;
    queue[rear]=0;
    visited[0]=true;
    
    int index;
    while(completed !=n)
    {
        index=queue[front];
        front++;

        //process coming first time
        if(p[index].bt_remaining==p[index].bt){
            p[index].start_time=findmax(current_time,p[index].at);
            current_time=p[index].start_time;

        }
        //process not coming first time but still remaining
        if(p[index].bt_remaining-tq>0){
            p[index].bt_remaining -=tq;
            current_time +=tq;
        }
        //process completed
        else{
            current_time += p[index].bt_remaining;  //could be less than tq
            p[index].bt_remaining=0;

            completed++;

            p[index].ct=current_time;
            p[index].tat =p[index].ct-p[index].at;
            p[index].wt =p[index].tat-p[index].bt;
            p[index].rt =p[index].start_time-p[index].at;

            sum_tat +=p[index].tat;
            sum_wt  +=p[index].wt;
            sum_rt  +=p[index].rt;
        }

        //put another process which is within the time limit
        for(int i=1; i<n;i++){
            if(p[i].bt_remaining>0 && p[i].at<=current_time && visited[i]==false) {
                queue[++rear]=i;
                visited[i]=true;
            }
        }

        //if current process still remaining, put into queue again
        if(p[index].bt_remaining>0){
            queue[++rear]=index;
        }

        //when there is idle time
        if(front>rear){
            for(int i=1; i<n;i++){
                if(p[i].bt_remaining>0){
                    queue[rear++]=i;
                    visited[i]=true;
                    break;
                }
            }
        }

    }
    printf("Pid AT BT ST CT TAT WT RT\n");
    for(int i=0;i<n;i++)
    printf("%d   %d   %d   %d   %d   %d   %d   %d\n",p[i].pid,p[i].at,p[i].bt,p[i].start_time,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    printf("\n");    

    printf("\nAverage Turn Around time= %.2f",(float)sum_tat/n);
    printf("\nAverage Waiting Time= %.2f",(float)sum_wt/n);
    printf("\nAverage Response Time= %.2f",(float)sum_rt/n); 
   
  return 0;
}