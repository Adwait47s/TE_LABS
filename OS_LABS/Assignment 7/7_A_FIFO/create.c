#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
 int res1,res2;
 res1=mkfifo("fifo1",0666);
 printf("%d\n",res1);
 res2=mkfifo("fifo2",0666);
 printf("%d\n",res2);

return 0;
}
