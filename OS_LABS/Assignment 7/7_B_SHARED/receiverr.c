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
 
 shmid=shmget((key_t)33158,1024,0666);
 shared_memory=shmat(shmid,NULL,0);
 printf("sender\n%s",(char*)shared_memory);

 fgets(buffer,sizeof(buffer),stdin);
 strcpy(shared_memory,buffer);
 

return 0;
}
