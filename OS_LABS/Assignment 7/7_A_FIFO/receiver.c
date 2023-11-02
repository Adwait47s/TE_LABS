#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>



int main()
{
 int fifo1,fifo2,res;
 char buffer[100];

 fifo1=open("fifo1",O_RDONLY);
 fifo2=open("fifo2",O_WRONLY);
 
 while(1)
 {
   read(fifo1,buffer,sizeof(buffer));
   printf("Received from sender\n%s",buffer);
   int chcnt=0;
   int wcnt=0;
   int lcnt=0;
   for(int i=0; i<strlen(buffer); i++)
   {
     chcnt++;
     if(buffer[i] == ' ' || buffer[i] == '\n')
     {
       wcnt++;
     }
     
     if(buffer[i] == '\n')
     {
      lcnt++;
     }
   }
   
   sprintf(buffer,"Charecters : %d , Words : %d, Lines : %d",chcnt,wcnt,lcnt);
   write(fifo2,buffer,sizeof(buffer));
 }
 
 close(fifo1);
 close(fifo2);
 
return 0;
}
