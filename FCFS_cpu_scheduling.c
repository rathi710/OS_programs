#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct process{
    int pid;
    int arrival;
    int burst;
    int ct,tat,wt,rt;
    int start_time;
}p[100];       //array of structure to store the info of each process
  
int main(){
    // struct process p[10];
    int n;
    printf("enter no of processes:");
    scanf("%d",&n);
    printf("enter arrival and burst time for processes:\n");

    for(int i=0;i<n;i++){
        scanf("%d %d",&p[i].arrival,&p[i].burst);
        p[i].pid = i+1;
    }

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].arrival > p[j+1].arrival)
            {
                struct process temp  = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    int sum=0;
    float sum_tat=0, sum_wt=0, sum_rt=0, total_idle_time=0, total_time=0;;
    for(int i=0; i<n; i++){
        p[i].start_time = (i==0) ? p[i].arrival : fmax(p[i-1].ct,p[i].arrival);  //imp condition to cal ct
        p[i].ct = p[i].start_time + p[i].burst;  //makes it easy
        p[i].tat = p[i].ct - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;
        p[i].rt = p[i].wt;

        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
        sum_rt += p[i].rt;

        total_idle_time += (i==0) ? 0 : (p[i].start_time - p[i-1].ct);
    }
    
    total_time += p[n-1].ct - p[0].arrival;

    printf("PID->arrival->burst->completion time->turnaround->waiting time->response time\n");
    for(int i=0;i<n;i++){
        printf("%d -> %d -> %d -> %d -> %d -> %d -> %d\n",p[i].pid, p[i].arrival, p[i].burst, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    
    printf("average turn around time = %f\n",sum_tat/n);
    printf("average turn waiting time = %f\n",sum_wt/n);
    printf("average turn response time = %f\n",sum_rt/n);
    printf("CPU Utilization = %f\n",(float)(total_time - total_idle_time) / total_time)*100;
    printf("throughput = %f\n",(n / (float)total_time));  //no of processes completed per unit time(n / ct of last process - arrival time of first process)
    return 0;
}

//cpu utilization = (total cpu utilization/total completion time of all processes)*100