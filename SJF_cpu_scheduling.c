/*.................C Program to Implement SJF ( Shortest Job First) CPU SCheduling Algorithm.....................
SJF - A Non Preemptive Algorithm*/


#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,start_time;
}ps[100];

int main()
{
    int n;
    printf("Enter total number of processes: ");
    scanf("%d",&n);    

    for(int i=0;i<n;i++){
        scanf("%d %d",&ps[i].at,&ps[i].bt);
        ps[i].pid = i;
    }

    bool is_completed[100]={false};
    int current_time = 0, completed = 0;
    int sum_tat=0, sum_wt=0, sum_rt=0;

    while(completed!=n)
    {
        //find process with min. burst time in ready queue at current time
        int idx = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && is_completed[i] == false) {
                if(ps[i].bt < minimum) {
                    minimum = ps[i].bt;
                    idx = i;
                }
                if(ps[i].bt== minimum) {
                    if(ps[i].at < ps[idx].at) {
                        minimum= ps[i].bt;
                        idx = i;
                    }
                }
            }
        }

        if(idx==-1) current_time++;
        else
        {
            ps[idx].start_time = current_time;
            ps[idx].ct = ps[idx].start_time + ps[idx].bt;
            ps[idx].tat = ps[idx].ct - ps[idx].at;
            ps[idx].wt = ps[idx].tat - ps[idx].bt;
            ps[idx].rt = ps[idx].wt;
            // ps[idx].rt = ps[idx].start_time - ps[idx].at;
                    
            sum_tat +=ps[idx].tat;
            sum_wt += ps[idx].wt;
            sum_rt += ps[idx].rt;
            
            completed++;
            is_completed[idx]=true;
            current_time = ps[idx].ct;  
        }
    }
    

    //Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n",ps[i].pid,ps[i].at,ps[i].bt,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);
    printf("\n");    
    

    printf("\nAverage Turn Around time= %f ",(float)sum_tat/n);
    printf("\nAverage Waiting Time= %f ",(float)sum_wt/n);
    printf("\nAverage Response Time= %f ",(float)sum_rt/n);

    return 0;
}
