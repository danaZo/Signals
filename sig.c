#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int flag = 1;
void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {
        
        case SIGALRM:
            printf("Signal Caught - SIGALRM \n");
            printf("child Procces stoped by SIGSTOP \n");
            raise(SIGSTOP);
            printf("cXXXXX \n");
            fflush(stdout);
            break;
		case SIGCHLD:
			printf("Signal Caught - SIGCHLD\n");
			fflush(stdout);
            flag = 0;
			raise(SIGCONT);
            int k = j /flag;
            
			break;
		case SIGFPE:
			printf("Signal caught - SIGFPE\n");
			
            printf("Performig an illegal instruction to generate SIGILL\nprogram wil be terminated\n");
            fflush(stdout);
            asm(".byte 0x0f, 0x0b");
			exit(1);
            break;
			
        case SIGCONT:
            printf("Signal Caught - SIGCONT \n");
            printf("child Procces resumed by SIGCONT \n");
            fflush(stdout);
            break;



    } 
}

int main()
{
	int status;
    signal (SIGALRM,sig_handler);
    signal (SIGCONT,sig_handler);
	signal (SIGCHLD, sig_handler);
	signal (SIGFPE, sig_handler);
	signal (SIGIO, sig_handler);
	signal (SIGSYS, sig_handler);

    
 
    char ** p;
    pid_t pid;  
    pid = fork();
    int stat;
    switch(pid){

        case 0:{
            
            alarm(3); // generates SIGALRM in 3 seconds

            


            
            printf("Alarm set for 3 seconds\n");
            fflush(stdout);
            
            
            while(flag){
                printf("waiting for the alaram...\n");
                fflush(stdout);
                sleep(1); // The alaram called after 3 seconds and resulted in
                          //Trigering a chain of signals - SIGSTP,SIGCHLD,SIGCONTD,SIGILL and SIGFPE
            }

             
            exit(1);
            }
        case -1:{
            perror("main");
        }

        default:
            
            // printf("%d \n",pid);
            wait(&status);
            

    }
}
