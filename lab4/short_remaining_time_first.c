#include<stdio.h>

int main(){
    int at[10], bt[10], temp[10];
    int i , smallest , time , n , count=0;
    double wt=0, tat=0, end;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("enter the  burst time of process %d: ", i+1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }
    bt[9] = 9999;
    for(time=0; count!=n; time++){
        smallest = 9;
        for(i=0; i<n; i++){
            if(at[i]<=time && bt[i]<bt[smallest] && bt[i]>0){
                smallest = i;
            }
        }
        bt[smallest]--;
        if(bt[smallest]==0){
            count++;
            end = time+1;
            wt = wt+end-at[smallest]-temp[smallest];
            tat = tat+end-at[smallest];
        }
    }

    float awt = wt/n;
    float atat = tat/n;
    printf("Average waiting time: %f\n", awt);
    printf("Average turn around time: %f\n", atat);
    return 0;
}