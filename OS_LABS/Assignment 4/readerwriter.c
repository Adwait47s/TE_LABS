#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

int rc=0; // read count
int cnt=1; // critical section
sem_t wrt; // semaphore for critical section
pthread_mutex_t mutex; // mutex lock for protecting rc variable

void *reader(int *i)
{
  // now increament rc variable with help of mutex lock
  pthread_mutex_lock(&mutex);
  rc++;
  // if its 1st reader make sure there is no writer
  if(rc == 1)
  {
    sem_wait(&wrt);
  }
  pthread_mutex_unlock(&mutex);
  
  // print the cnt vaiable
  printf("Reader %d reads the critical section varible as %d\n",*(int*)i,cnt);
  
  
  pthread_mutex_lock(&mutex);
  rc--;
  sleep(rand() % 4); 
  // no readers are there so writer may write now
  if(rc == 0)
  {
     sem_post(&wrt);
  }
  
  pthread_mutex_unlock(&mutex);
  
}

void *writer(int *i)
{
 // write=0 => writer is busy 
 // write=1 => writer is empty 
 sem_wait(&wrt); // write --
 cnt=rand()%10;
 printf("Writer %d changed the critical section variable to  %d\n",*(int*)i,cnt);
 sleep(rand() % 4); 
 sem_post(&wrt);// write ++
 
}

int main()
{

pthread_t wr[10],rd[10];

int a[]={1,2,3,4,5,6,7,8,9,10};
sem_init(&wrt,0,1);
pthread_mutex_init(&mutex,NULL);

for(int i=0; i<10; i++)
{
 pthread_create(&rd[i],NULL,(void *)&reader,(void *)&a[i]);
 sleep(1);
 pthread_create(&wr[i],NULL,(void *)&writer,(void *)&a[i]);
}

for(int i=0; i<10; i++)
{
 pthread_join(rd[i],NULL);
 pthread_join(wr[i],NULL);
}

sem_destroy(&wrt);
pthread_mutex_destroy(&mutex);
return 0;
}


