#include<stdio.h>
#include<stdbool.h>
#include<string.h>
//Function to print the frame contents
//Return nothing
void printFrames(int frames[],int n)
{
    for(int i=0;i<n;i++)
      printf("%d ",frames[i]);
    printf("\n");  
}

int main()
{
    int i,n,no_of_frames,page_fault=0;
    printf("\nEnter the no. of pages:");
    scanf("%d",&n);

    //create reference string array
    int string[n]; 
    printf("\nEnter the reference string(different page numbers) :\n");
    for(int i=0;i<n;i++)
       scanf("%d",&string[i]);

    printf("\nEnter the no. of frames you want to give to the process :");
    scanf("%d",&no_of_frames);

    //create frame array to store the pages at different point of times
    int frames[no_of_frames];
    memset(frames,-1,no_of_frames*sizeof(int));
    
    printf("\n****The Contents inside the Frame array at different time:****\n");
 

    //Index to insert element
    int index=-1;

    //Counters
    int page_miss=0;  //page fault
    int page_hits=0;

    //Traversing each symbol in fifo
    for (int i=0;i<n;i++){
        int flag=0;

        for(int j=0;j<no_of_frames;j++)
        {
            if (string[i]==frames[j]){
                printFrames(frames,no_of_frames);
                flag=1;
                break;
            }
        }

        if(flag==0){
            index = (index+1) % no_of_frames;  //for circular movement in array
            frames[index]=string[i];
            page_fault+=1;
            printFrames(frames,no_of_frames);
        }
    }
    
    printf("\nPage hits: %d",n-page_fault);
    printf("\nPage misses/page faults: %d",page_fault);
    printf("\nPage Fault ratio = %.2f\n",(float)page_fault/n);
}