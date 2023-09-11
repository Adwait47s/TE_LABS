#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <limits.h>

#define MAX_SIZE 1000

// Structure to represent a process
int process[1001];
int time[1001];
int size = 0;
int upto = 0;

struct Process
{
  int id;
  int arrival_time;
  int burst_time;
  int priority;
  int remaining_time;
  int waiting_time;
  int turnaround_time;
  bool completed;
};


// Structure to represent the queue
typedef struct {
  int array[MAX_SIZE];
  int front;
  int rear;
} Queue;

// Function to create a new empty queue
Queue* createQueue() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  if (queue == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  queue->front = -1;
  queue->rear = -1;
  return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
  return (queue->front == -1 && queue->rear == -1);
}

// Function to check if the queue is full
int isFull(Queue* queue) {
  return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// Function to enqueue an element
void push(Queue* queue, int value) {
  if (isFull(queue)) {
    printf("Queue is full. Enqueue operation failed.\n");
    return;
  }
  if (isEmpty(queue)) {
    queue->front = 0;
    queue->rear = 0;
  } else {
    queue->rear = (queue->rear + 1) % MAX_SIZE;
  }
  queue->array[queue->rear] = value;
}

// Function to dequeue an element
int pop(Queue* queue) {
  int value;
  if (isEmpty(queue)) {
    printf("Queue is empty. Dequeue operation failed.\n");
    exit(EXIT_FAILURE);
  }
  value = queue->array[queue->front];
  if (queue->front == queue->rear) {
        // Last element in the queue
    queue->front = -1;
    queue->rear = -1;
  } else {
    queue->front = (queue->front + 1) % MAX_SIZE;
  }
  return value;
}

// Function to get the front element of the queue without removing it
int front(Queue* queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty. Front operation failed.\n");
    exit(EXIT_FAILURE);
  }
  return queue->array[queue->front];
}

void prnt(struct Process processes[])
{
  printf("\n\n");
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
      if (now == processes[i].id)
      {
        printf("Process");
        printf(" %d", now);
        printf(" AT: %d  ", processes[i].arrival_time);
        printf(" BT:  %d ", processes[i].burst_time);
        printf(" TAT: %d  ", processes[i].turnaround_time);
        printf(" WT:  %d \n", processes[i].waiting_time);
        now++;
        break;
      }

    }

  }
}

// Function to find the process with the shortest remaining time
int findShortestJob(struct Process processes[], int n, int current_time, int choice)
{
  int shortest_job_index = -1;
  int shortest_time = INT_MAX;

  if(choice==2||choice==3){
    for (int i = 0; i < n; i++)
    {
      if (!processes[i].completed && processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_time)
      {
        shortest_time = processes[i].remaining_time;
        shortest_job_index = i;
      }
    }
  }
  else if(choice==1){
    for (int i = 0; i < n; i++)
    {
      if (!processes[i].completed && processes[i].arrival_time <= current_time && processes[i].arrival_time< shortest_time )
      {

        shortest_time = processes[i].arrival_time;
        shortest_job_index = i;
      }
    }
  }
  else if(choice==4||choice==5){
    for (int i = 0; i < n; i++)
    {
      if (!processes[i].completed && processes[i].arrival_time <= current_time && processes[i].priority < shortest_time)
      {
        shortest_time = processes[i].priority;
        shortest_job_index = i;
      }
    }
  }
  
  return shortest_job_index;
}

int main()
{
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  struct Process processes[n];

  // Input process details
  for (int i = 0; i < n; i++)
  {
    processes[i].id = i + 1;
    printf("Enter arrival time and burst time for process P%d: ", processes[i].id);
    scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    processes[i].remaining_time = processes[i].burst_time;
    processes[i].completed = false;
  }
  
  int quantum;
  
  printf("Please enter the time quantum\n");
  scanf("%d" , &quantum);

  while (1)
  {
    printf("----------MENU------------\n\n");
    printf("1) First come first serve\n");
    printf("2) SJF Preamptive\n");
    printf("3) SJF Non Preamptive\n");
    printf("4) Priority preeamptive\n");
    printf("5) Priority non preeamptive\n");
    printf("6) Round Robin\n");
    printf("7) Exit\n");
    printf("\n");
    printf("Please make a choice\n");
    int choice;
    scanf("%d", &choice);

    int current_time = 0;
    int completed = 0;
    int timeline[1000];
    int timeline_current_time = 0;

    for (int i = 0; i < n; i++)
    {
      processes[i].remaining_time = processes[i].burst_time;
      processes[i].completed = false;
    }

    if (choice == 1) {

      while(completed < n){
        int shortest_job_index = findShortestJob(processes,n,current_time,1);
        if(shortest_job_index == -1){
          timeline[timeline_current_time] = -1;
          timeline_current_time++;
          current_time++;
        }
        else{

          for(int i=0;i<processes[shortest_job_index].burst_time;i++){
            timeline[timeline_current_time]=processes[shortest_job_index].id;
            timeline_current_time++;
          }

          current_time+= processes[shortest_job_index].burst_time;
          processes[shortest_job_index].completed= 1;
          completed++;
          int completion_time = current_time ;

          processes[shortest_job_index].remaining_time =0;
          processes[shortest_job_index].turnaround_time = completion_time - processes[shortest_job_index].arrival_time;
          processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
          printf("[P%d] -> %d\n", processes[shortest_job_index].id, completion_time);
        }
      }
    }
    else if (choice == 2) {

      while (completed < n) {
        int shortest_job_index = findShortestJob(processes, n, current_time,choice);

        if (shortest_job_index == -1) {
          timeline[timeline_current_time] = -1;
          current_time++;
        } 
        else {
          processes[shortest_job_index].remaining_time--;
          timeline[timeline_current_time] = processes[shortest_job_index].id;

          if (processes[shortest_job_index].remaining_time == 0) {
            completed++;
            processes[shortest_job_index].completed = true;
            int completion_time = current_time + 1;
            processes[shortest_job_index].turnaround_time = completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            printf("[P%d] -> %d\n", processes[shortest_job_index].id, completion_time);
          }

          current_time++;
          timeline_current_time++;
        }
      }
    }
    else if (choice == 3) {
      while(completed < n){
        int shortest_job_index = findShortestJob(processes,n,current_time,choice);
        if(shortest_job_index == -1){
          timeline[timeline_current_time] = -1;
          timeline_current_time++;
          current_time++;
        }
        else{

          for(int i=0;i<processes[shortest_job_index].burst_time;i++){
            timeline[timeline_current_time]=processes[shortest_job_index].id;
            timeline_current_time++;
          }

          current_time+= processes[shortest_job_index].burst_time;
          processes[shortest_job_index].completed= 1;
          completed++;
          int completion_time = current_time ;

          processes[shortest_job_index].remaining_time =0;
          processes[shortest_job_index].turnaround_time = completion_time - processes[shortest_job_index].arrival_time;
          processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
          printf("[P%d] -> %d\n", processes[shortest_job_index].id, completion_time);
        }
      }
    }
    else if (choice == 4) {

      while (completed < n) {
        int shortest_job_index = findShortestJob(processes, n, current_time,choice);

        if (shortest_job_index == -1) {
          timeline[timeline_current_time] = -1;
          current_time++;
        } 
        else {
          processes[shortest_job_index].remaining_time--;
          timeline[timeline_current_time] = processes[shortest_job_index].id;

          if (processes[shortest_job_index].remaining_time == 0) {
            completed++;
            processes[shortest_job_index].completed = true;
            int completion_time = current_time + 1;
            processes[shortest_job_index].turnaround_time = completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            printf("[P%d] -> %d\n", processes[shortest_job_index].id, completion_time);
          }

          current_time++;
          timeline_current_time++;
        }
      }
    }
    else if (choice == 5) {
      while(completed < n){
        int shortest_job_index = findShortestJob(processes,n,current_time,choice);
        if(shortest_job_index == -1){
          timeline[timeline_current_time] = -1;
          timeline_current_time++;
          current_time++;
        }
        else{

          for(int i=0;i<processes[shortest_job_index].burst_time;i++){
            timeline[timeline_current_time]=processes[shortest_job_index].id;
            timeline_current_time++;
          }

          current_time+= processes[shortest_job_index].burst_time;
          processes[shortest_job_index].completed= 1;
          completed++;
          int completion_time = current_time ;

          processes[shortest_job_index].remaining_time =0;
          processes[shortest_job_index].turnaround_time = completion_time - processes[shortest_job_index].arrival_time;
          processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
          printf("[P%d] -> %d\n", processes[shortest_job_index].id, completion_time);
        }
      }
    }
    else if (choice == 6) {
      Queue* rrQueue = createQueue();
      int timeQuantum = quantum;
      int currentTime = 0;
      int completed = 0;
      int* burstTimeCopy = (int*)malloc(n * sizeof(int));

      for (int i = 0; i < n; i++) {
        burstTimeCopy[i] = processes[i].burst_time;
      }

      while (completed < n) {
        for (int i = 0; i < n; i++) {
          if (processes[i].arrival_time <= currentTime && burstTimeCopy[i] > 0) {
            int executeTime = (burstTimeCopy[i] < timeQuantum) ? burstTimeCopy[i] : timeQuantum;

                // Execute the process for the time quantum or until it finishes
            for (int j = 0; j < executeTime; j++) {
              timeline[timeline_current_time] = processes[i].id;
              timeline_current_time++;
            }

            burstTimeCopy[i] -= executeTime;
            currentTime += executeTime;

            if (burstTimeCopy[i] == 0) {
              completed++;
              processes[i].completed = true;
              int completionTime = currentTime;
              processes[i].turnaround_time = completionTime - processes[i].arrival_time;
              processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
              printf("[P%d] -> %d\n", processes[i].id, completionTime);
            } else {
                    push(rrQueue, i);  // Enqueue the process back into the queue
                  }
                }
              }

              if (!isEmpty(rrQueue)) {
                int frontProcessIndex = front(rrQueue);
            pop(rrQueue);  // Dequeue the front process

            // Enqueue it back after processing other ready processes
            push(rrQueue, frontProcessIndex);
          } else {
            timeline[timeline_current_time] = -1;  // Idle time
            timeline_current_time++;
            currentTime++;
          }
        }

        free(burstTimeCopy);
        free(rrQueue);
      }

      else if (choice == 7) {
        break;
      }
      else {
        printf("Wrong choice\n");
      }
      if(choice<=6){
        float avg_waiting_time = 0.0;
        float avg_turnaround_time = 0.0;
        for (int i = 0; i < n; i++) {
          avg_waiting_time += processes[i].waiting_time;
          avg_turnaround_time += processes[i].turnaround_time;
        }



        size=1;
        time[0]=0;
        int cnt=0;
      // for(int i=0;i<timeline_current_time;i++){
      //   printf(" %d", timeline[i]);
      // }

        for(int i=0;i<timeline_current_time;i++){
          cnt++;
          if(timeline[i]!=timeline[i+1]){
            time[size] = cnt;
            process[size-1] = timeline[i];
            size++;
          }
        }
        if(time[size-1]!=timeline[timeline_current_time-1]){
          time[size] = cnt;
          process[size-1] = timeline[size-1];
          size++;
        }
        size--;
        upto = timeline_current_time;

        prnt(processes);

        avg_waiting_time /= n;
        avg_turnaround_time /= n;

        printf("\n\nAverage Waiting Time: %.2f\n", avg_waiting_time);
        printf("Average Turnaround Time: %.2f\n\n", avg_turnaround_time);
      }
    }
  }

// intput
// 5
// 8 4 0 16 10
// 2 7 13 5 15
// 5 3 4 1 2
// 4
// 1
// 2
// 3
