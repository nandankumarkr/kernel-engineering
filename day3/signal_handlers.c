#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
volatile sig_atomic_t usr1_count = 0;
void signal_handler(int sig){
	if(sig == SIGINT){
		printf("\nSIGINT received, continuing ....\n");
	}else if(sig == SIGTERM){
		printf("\nSIGTERM received, Exiting ....\n");
		exit(0);
	}else if(sig == SIGUSR1){
		usr1_count++;
		printf("\n got SIGUSR1. count = %d\n",usr1_count);
	}
}
int main(){
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT,&sa,NULL);
	sigaction(SIGTERM,&sa,NULL);
	sigaction(SIGUSR1,&sa,NULL);
	printf("PID = %d\n",getpid());
	while(1){
		printf("running\n");
		sleep(2);
	}
	return 0;
}
