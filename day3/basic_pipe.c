#include<stdio.h>
#include<err.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
	int pipefd[2];
	char buf;
	pid_t cpid;
	if(pipe(pipefd) == -1){
		err(EXIT_FAILURE,"pipe");
	}
	cpid = fork();
	if(cpid == -1){
		err(EXIT_FAILURE,"fork");
	}
	if(cpid == 0){
		if(close(pipefd[1])==-1){
			err(EXIT_FAILURE,"close");
		}
		while(read(pipefd[0],&buf,1) > 0){
			if(write(STDOUT_FILENO,&buf,1)!=1){
				err(EXIT_FAILURE,"write");
			}
		}
		if(close(pipefd[0])==-1){
			err(EXIT_FAILURE,"close");
		}
		exit(EXIT_SUCCESS);
	}else{
		if(close(pipefd[0])==-1){
			err(EXIT_FAILURE,"close");
		}
		if(write(pipefd[1],"hello from parent\n",18) != 18){
			err(EXIT_FAILURE,"write");
		}
		if(close(pipefd[1])==-1){
			err(EXIT_FAILURE,"close");
		}
		wait(NULL);
	}
	return 0;
}
