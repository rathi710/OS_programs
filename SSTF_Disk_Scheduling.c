#include<stdio.h>
#include<stdlib.h>
int main()
{
    int RQ[100],i,n,TotalHeadMoment=0,initial,count=0;
    printf("Enter the number of Requests\n");
    scanf("%d",&n);
    printf("Enter the Requests sequence\n");
    for(i=0;i<n;i++)
     scanf("%d",&RQ[i]);
    printf("Enter initial head position\n");
    scanf("%d",&initial);
    
    // logic for sstf disk scheduling
        /* loop will execute until all process is completed*/
    while(count!=n)
    {
        int min=1000,d,index;
        for(i=0;i<n;i++)
        {
           if(RQ[i]==-1) continue;

           d=abs(RQ[i]-initial);
           if(min>d)
           {
               min=d;
               index=i;
           }
           
        }
        TotalHeadMoment=TotalHeadMoment+min;
        initial=RQ[index];
        //to not choose same element again
        RQ[index] = -1;
        count++;
    }
    
    printf("Total head movement is %d",TotalHeadMoment);
    return 0;
}



//sample I/O:-
// Enter the number of Request
// 8
// Enter Request Sequence
// 95 180 34 119 11 123 62 64
// Enter initial head Position
// 50
// Total head movement is 236