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
int arrival_time[N], burst_time[N], priority[N];
void prnt()
{
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d-", time[i]);
        printf("%d  =  ", time[i + 1]);
        printf("%d\n", process[i]);
    }

    printf("\n\n");
    int upto = time[size - 1];
    int now = 0;
    for (int i = 0; i <= upto; i++)
    {
        if (i == 0)
        {
            printf("+");
            if (time[now] == i)
            {
                now++;
            }
        }
        else if (time[now] == i)
        {
            printf("+");
            now++;
        }
        else
        {
            printf(".");
        }
    }

    printf("\n");
    now = 0;
    int curr = (time[0] + time[1]) / 2;
    for (int i = 0; i <= upto; i++)
    {
        // +......
        // |
        // +.....

        if (i == 0)
        {
            printf("|");
            if (time[now] == i)
            {
                now++;
                curr = (time[now] + time[now - 1]) / 2;
            }
        }
        else if (time[now] == i)
        {
            printf("|");
            now++;
            curr = (time[now] + time[now - 1]) / 2;
        }
        else if (curr == i)
        {
            printf("%d", process[now - 1]);
        }
        else
        {
            printf(" ");
        }
    }

    printf("\n");
    now = 0;
    for (int i = 0; i <= upto; i++)
    {
        if (i == 0)
        {
            printf("+");
            if (time[now] == i)
            {
                now++;
            }
        }
        else if (time[now] == i)
        {
            printf("+");
            now++;
        }
        else
        {
            printf(".");
        }
    }

    printf("\n");
    now = 0;
    for (int i = 0; i <= upto; i++)
    {
        if (time[now] == i)
        {
            printf("%d", i);
            now++;
        }
        else
        {
            printf(" ");
        }
    }

    printf("\n\n");
    now = 1;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            if (now == process[i])
            {
                printf("Process");
                printf(" %d", now);
                printf(" AT: %d  ", arrival_time[j]);
                printf(" BT:  %d ", burst_time[j]);
                int tat = time[i + 1] - arrival_time[j];
                printf(" TAT: %d  ", tat);
                printf(" WT:  %d \n", tat - burst_time[j]);
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

    printf("Enter the quantum time  : ");

    int qt;

    scanf("%d", &qt);

    while (1)
    {
        printf("----------MENU------------\n\n");
        printf("1.First Come First Serve\n");
        printf("2.Shortest Job First\n");
        printf("3.Round Robin \n");
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
        else if (choice == 2)
        {
            memset(process, 0, sizeof(process));
            memset(time, 0, sizeof(time));
            memset(vis, 0, sizeof(vis));
            size = 0;
            currT = 1, currP = 0;
            int cnt = 0;
            time[0] = 0;

            while (cnt <= n)
            {
                int timetillnow = time[currT - 1];
                int pr = -1;
                int bt = 1001;  // burst time of that process
                int mininum_next = 1001;
                int prnext = -1;
                for (int i = 0; i < n; i++)
                {
                    if (timetillnow >= arrival_time[i] && vis[i] == 0)
                    {
                        if (burst_time[i] < bt)
                        {
                            pr = i;
                            bt = burst_time[i];
                        }
                    }
                    else if (timetillnow < arrival_time[i] && vis[i] == 0)
                    {
                        if (mininum_next > arrival_time[i])
                        {
                            prnext = i;
                            mininum_next = arrival_time[i];
                        }
                    }
                }

                vis[pr] = 1;

                if (pr != -1)
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
        else if (choice == 3)
{
    memset(process, 0, sizeof(process));
    memset(time, 0, sizeof(time));
    memset(vis, 0, sizeof(vis));
    size = 0;
    currT = 1, currP = 0;
    int cnt = 0;
    int remaining_burst_time[N];
    int current_processes[N]; // Array to store currently executing processes
    int current_count = 0; // Count of currently executing processes

    for (int i = 0; i < n; i++)
    {
        remaining_burst_time[i] = burst_time[i];
    }

    time[0] = 0;

    while (cnt < n)
    {   
        int flag=0;
        

        // Add new arriving processes to the current_processes array
        for (int i = 0; i < n; i++)
        {
            if (remaining_burst_time[i] > 0 && arrival_time[i] <= time[currT - 1])
            {
                int exists = 0;
                for (int j = 0; j < current_count; j++)
                {
                    if (current_processes[j] == i)
                    {
                        exists = 1;
                        break;
                    }
                }
                if (!exists)
                {
                    current_processes[current_count] = i;
                    current_count++;
                }
            }
        }
        int prr = current_processes[0];
         for (int i = 0; i < current_count - 1; i++)
            {
                current_processes[i] = current_processes[i + 1];
            }
            current_processes[current_count - 1] = prr;

        // Remove completed processes from the current_processes array
        for (int i = 0; i < current_count; i++)
        {
            if (remaining_burst_time[current_processes[i]] == 0)
            {
                flag=1;
                for (int j = i; j < current_count - 1; j++)
                {
                    current_processes[j] = current_processes[j + 1];
                }
                current_count--;
                i--;
            }
        }

        if (current_count == 0)
        {
            time[currT] = arrival_time[currP];
            process[currP] = -1;
            currT++;
            currP++;
        }
        else
        {
            int pr = current_processes[0];
        process[currP]=pr+1;
        currP++;
            printf("burst time of cp : %d %d \n",pr+1,remaining_burst_time[pr]);
            if (remaining_burst_time[pr] <= qt)
            {
                time[currT] = time[currT - 1] + remaining_burst_time[pr];
                size++;
                currT++;
                remaining_burst_time[pr] = 0;
                cnt++;
            }
            else
            {
                time[currT] = time[currT - 1] + qt;
                size++;
                currT++;
                remaining_burst_time[pr] -= qt;
            }
            printf("burst time of cp : %d %d \n",pr+1,remaining_burst_time[pr]);
            // Move the executed process to the end of the array
           
            
        }
        
        for(int i=0;i<current_count;i++){
                printf("%d " , current_processes[i]+1);
            }
            printf("\n");
        
    }

    prnt();
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
