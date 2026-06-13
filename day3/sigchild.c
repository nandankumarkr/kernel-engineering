#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<sys/wait.h>
void sigchld_handler(int sig){
	int status;
	pid_t pid;
	while((pid = waitpid(-1,&status,WNOHANG)) > 0){
		printf("reaped child %d\n",getpid());
	}
}
int main(){
	struct sigaction sa;
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags =0;
	if(sigaction(SIGCHLD,&sa,NULL) == -1){
		perror("sigaction");
		exit(1);
	}
	srand(time(NULL));
	for(int i=0;i<5;i++){
		pid_t pid = fork();
		if(pid<0){
			perror("fork");
			exit(1);
		}
		if(pid ==0){
			int t = rand()%3 + 1;
			printf("child %d sleeping for %d seconds\n",getpid(),t);
			sleep(t);
			printf("child %d exiting\n",getpid());
			exit(0);
		}
	}
	printf("Parent pid = %d\n",getpid());
	while(1){
		sleep(1);
	}
	return 0;
}
