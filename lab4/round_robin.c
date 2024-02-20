#include<stdio.h>

int main(){
    int i,n,time,total=0,x,counter=0;
    int wt = 0, tat = 0,at[10],bt[10],temp[10];
    float awt , atat;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    x = n;
    for(i=0; i<n; i++){
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter the burst time of process %d: ", i+1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time);
    printf("\n\nProcess\t\tBurst Time\t\tTurnaround Time\t\tWaiting Time\n\n");
    for(total=0, i=0; x!=0;){
        if(bt[i]<=time && bt[i]>0){
            total = total+bt[i];
            bt[i] = 0;
            counter = 1;
        }
        else if(bt[i]>0){
            bt[i] = bt[i]-time;
            total = total+time;
        }
        if(bt[i]==0 && counter==1){
            x--;
            printf("P[%d]\t\t%d\t\t%d\t\t%d\n", i+1, temp[i], total-at[i], total-at[i]-temp[i]);
            wt = wt+total-at[i]-temp[i];
            tat = tat+total-at[i];
            counter = 0;
        }
        if(i==n-1){
            i=0;
        }
        else if(at[i+1]<=total){
            i++;
        }
        else{
            i=0;
        }
    }
    awt = wt/n;
    atat = tat/n;
    printf("Average waiting time: %f\n", awt);
    printf("Average turn around time: %f\n", atat);
    return 0;
}