#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

const int N = 1001;
int process[1001];
int time[1001];
int vis[1001];
int sysprocess[1001];
int size = 0;
int arrival_time[N], burst_time[N], priority[N], qt[N];
void prnt()
    {
        for (int i = 0; i < size - 1; i++)
        {
            printf("%d-", time[i]);
            printf("%d  =  ", time[i + 1]);
            printf("%d\n", process[i]);
        }
        printf("\n\n");
        int upto = time[size-1];
        int now=0;
        for(int i=0;i<=upto;i++){
            if(i==0){
                printf("+");
                if(time[now]==i){
                    now++;
                }
            }
            else if(time[now]==i){
                printf("+");
                now++;
            }
            else {
                printf(".");
            }
            
        }
        printf("\n");
        now=0;
        int curr= (time[0]+time[1])/2;
        for(int i=0;i<=upto;i++){
            // +......
            // |
            // +.....
            
            if(i==0){
                printf("|");
                if(time[now]==i){
                    now++;
                    curr = (time[now] + time[now-1])/2;
                }
            }
            else if(time[now]==i){
                printf("|");
                now++;
                curr = (time[now] + time[now-1])/2;
            }
            else if(curr==i){

                printf("%d",process[now-1]);
            }
            else {
                printf(" ");
            }

        }
        printf("\n");
        now=0;
        for(int i=0;i<=upto;i++){
            if(i==0){
                printf("+");
                if(time[now]==i){
                    now++;
                }
            }
            else if(time[now]==i){
                printf("+");
                now++;
            }
            else {
                printf(".");
            }
            
        }
        printf("\n");
        now=0;
        for(int i=0;i<=upto;i++){
            if(time[now]==i){
                printf("%d",i);
                now++;
            }
            else{
                printf(" ");
            }
            
        }
        printf("\n\n");
        now=1;
        for(int j=0;j<size;j++){
            for(int i=0;i<size;i++){
                if(now==process[i]){
                    printf("Process");
                    printf(" %d" ,now);
                    printf("  %d  " , arrival_time[now-1]);
                    printf("  %d  " , burst_time[now-1]);
                    int tat = time[now-1] - time[now-1-1] - arrival_time[now-1];
                    printf("  %d  " , tat);
                    printf("  %d  \n" , tat -burst_time[now-1]);
                    now++;
                    break;
                }
            }
        }
        
    }

int main()
{
    int n;
    printf("Enter the number of processes in the array: ");
    scanf("%d", &n);
    

    printf("Enter the arrival time of each process : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter the burst time of each process : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time[i]);
    }

    printf("Enter the priority of each process : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &priority[i]);
    }

    printf("Enter the quantum time of each process : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &qt[i]);
    }

    
    

    while (1)
    {   printf("----------MENU------------\n\n");
        printf("1.First Come First Serve\n");
        printf("2.Shortest Job First\n");
        printf("\n");
        printf("Please make a choice\n");
        printf("\n\n");
        int choice;
        scanf("%d", &choice);
        int currT = 1, currP = 0;
        time[0] = 0;
        if (choice == 1)
        {
            int cnt = 0;
            while (cnt <= n)
            {
                int ans = N;
                int pr = 0;
                for (int i = 0; i < n; i++)
                {
                    if (ans > arrival_time[i] && vis[i] == 0)
                    {
                        ans = arrival_time[i];
                        pr = i;
                    }
                }

                vis[pr] = 1;

                if (time[currT - 1] >= arrival_time[pr])
                {
                    time[currT] = time[currT - 1] + burst_time[pr];
                    process[currP] = pr + 1;
                    currT++;
                    currP++;
                    size++;
                }
                else
                {
                    time[currT] = arrival_time[pr];
                    process[currP] = -1;
                    currT++;
                    currP++;
                    time[currT] = time[currT - 1] + burst_time[pr];
                    process[currP] = pr + 1;
                    currT++;
                    currP++;
                    size += 2;
                }

                cnt++;
            }
            prnt();
        }
        else if(choice==2){
            memset(process,0,sizeof(process));
            memset(time,0,sizeof(time));
            memset(vis,0,sizeof(vis));
            size=0;
            currT = 1, currP = 0;
            int cnt = 0;
            time[0] = 0;

            while (cnt <= n)
            {
                int timetillnow = time[currT-1];
                int pr = -1;
                int bt = 1001; // burst time of that process
                int mininum_next=1001;
                int prnext =-1;
                for (int i = 0; i < n; i++)
                {
                    if (timetillnow >= arrival_time[i] && vis[i] == 0)
                    {
                        if(burst_time[i]<bt){
                            pr = i;
                            bt = burst_time[i];
                        }
                    }
                    else if(timetillnow < arrival_time[i] && vis[i] == 0){
                        if(mininum_next>arrival_time[i]){
                            prnext = i;
                            mininum_next = arrival_time[i];
                        }
                    }
                }

                vis[pr] = 1;

                if (pr!=-1)
                {
                    time[currT] = time[currT - 1] + burst_time[pr];
                    process[currP] = pr + 1;
                    currT++;
                    currP++;
                    size++;
                }
                else
                {
                    time[currT] = arrival_time[pr];
                    process[currP] = -1;
                    currT++;
                    currP++;
                    time[currT] = time[currT - 1] + burst_time[pr];
                    process[currP] = pr + 1;
                    currT++;
                    currP++;
                    size += 2;
                }

                cnt++;
            }
            size--;
            prnt();
        }
        else if(choice==3){

        }
        else
        {
            break;
        }
        printf("\n\n");
    }
}

// intput 
// 5
// 8 4 0 16 10
// 2 7 13 5 15
// 5 3 4 1 2
// 0 0 0 0 0
// 1
// 3
