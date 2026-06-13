#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<err.h>
#include<sys/wait.h>
#include<sys/types.h>
void sigint_handler(int sig){
	printf("\nCaught SIGINT,cleaning up...");
	exit(0);
}
int main(){
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGINT,&sa,NULL) == -1){
		perror("sigaction");
		exit(1);
	}
	while(1){
		printf("running...\n");
		sleep(1);
	}
	return 0;
}
