#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main()
{
 void *shared_memory;
 int shmid;
 char buffer[100];
 
 shmid=shmget((key_t)33158,1024,0666|IPC_CREAT);
 shared_memory=shmat(shmid,NULL,0);
 printf("Memory allocated at %p\n",shared_memory);
 printf("Enter some data to write\n");
 fgets(buffer,sizeof(buffer),stdin);
 strcpy(shared_memory,buffer);
 printf("receiver: %s",(char *)shared_memory);



return 0;
}
