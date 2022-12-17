#include <stdio.h>
#include <math.h>
int no_of_resources,no_of_process;
struct p_info{
    int allocated[20];
    int max[20];
    int need[20];
};

void takeInput(struct p_info process[no_of_process],int available[no_of_resources])
{
    for(int i=0; i<no_of_process; i++)
    {
        printf("enter process[%d] info:",i);
        printf("\nenter allocated resources for this process:");
        for(int j=0; j<no_of_resources; j++){
            scanf("%d",&process[i].allocated[j]);
        }

        printf("\n enter need for this process:");
        for(int j=0; j<no_of_resources; j++){
            scanf("%d",&process[i].max[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j];
        }

        printf("\nenter available resources:");
        for(int j=0; i<no_of_resources; j++){
            scanf("%d",&available[j]);
        }

    }
}

int main(){
    printf("enter no of processes:");
    scanf("%d",&no_of_process);
    printf("enter no of resources:");
    scanf("%d",&no_of_resources);

    struct p_info process[no_of_process];
    int available[no_of_resources];
    

    takeInput(process,available);

}