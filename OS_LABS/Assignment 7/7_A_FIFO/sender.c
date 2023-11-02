#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>



int main()
{
 int fifo1,fifo2,res;
 char buffer[100];
 
 fifo1=open("fifo1",O_WRONLY);
 fifo2=open("fifo2",O_RDONLY);
 printf("%d   %d\n",fifo1,fifo2);
 
 while(1)
 {
   printf("Please Enter the text : \n");
   fgets(buffer,sizeof(buffer),stdin);
   write(fifo1,buffer,strlen(buffer)+1);
   read(fifo2,buffer,sizeof(buffer));
   printf("Messege from receiver%s\n",buffer);
 }
 
 close(fifo1);
 close(fifo2);


return 0;
}
