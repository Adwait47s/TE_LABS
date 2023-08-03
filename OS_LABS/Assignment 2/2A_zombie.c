#include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

       int main()
       {
           int pipefd[2];
           pid_t cpid;
           char buf;

           
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
           
               printf("This is a child process \n");
               sleep(1);
               
               int childprocess_id = getpid();
               
               int parentprocess_id = getppid();
               
               printf("The process id  of child is  %d \n" , childprocess_id );
               
               printf("The process id  of parent is  %d \n" , parentprocess_id );
               
           } else if(cpid>0){            /* Parent writes argv[1] to pipe */
           
               printf("This is a parent process \n");
               sleep(10);
               wait(NULL);
           }
           // after 1 second when childprocess id and parent process id is displayed go to second terminal and type ps - elf and second last process will be zombie process
       }

