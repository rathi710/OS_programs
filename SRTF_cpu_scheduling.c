//srtf algo

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct process
{
    int pid;
    int at, bt , ct;
    int tat , wt, rt;
    int start_time ,  bt_remain;
}p[100];

int main()
{
    int n;
    printf("Enter total number of processes: ");
    scanf("%d",&n);    

    for(int i=0;i<n;i++){
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].pid = i;
        p[i].bt_remain = p[i].bt;
    }

    int completed=0;
    int current_time=0;
    bool is_completed[100]={false};
    
    float sum_tat , sum_wt , sum_rt ,avg_tat , avg_wt , avg_rt;

    while(completed !=n){
        int index= -1;
        int minimum = INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at<= current_time && is_completed[i]==false){
                if(p[i].bt_remain < minimum)
                {
                     minimum = p[i].bt_remain;
                     index=i;
                }

                if(p[i].bt_remain == minimum)
{
                      if(p[i].at < p[index].at)
                      {
                         minimum= p[i].bt_remain;
                         index=i;
                      }
                }
            }
        }

        if(index==-1) current_time++;
        else
        {
            if(p[index].bt_remain==p[index].bt){
                p[index].start_time=current_time;
            }
             p[index].bt_remain -=1;
             current_time ++;

             if(p[index].bt_remain == 0)
             {
                p[index].ct = current_time;
                p[index].tat = p[index].ct- p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                p[index].rt = p[index].start_time - p[index].at;

                sum_tat +=p[index].tat;
                sum_wt +=p[index].wt;
                sum_rt +=p[index].rt;

                completed++;
                is_completed[index]=true;
             }

        }
    }
    
    avg_tat=sum_tat/n;
    avg_rt=sum_rt/n;
    avg_wt=sum_wt/n;
  
  printf("Pid AT BT CT TAT WT RT\n");
  for(int i=0;i<n;i++)
  {
    printf("%d  %d  %d  %d  %d  %d  %d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
  }
 printf("Average Turn Around Time: %f\n",avg_tat); 
 printf("Average Waiting Time: %f\n",avg_wt); 
 printf("Average Response Time: %f\n",avg_rt); 

return 0;

}