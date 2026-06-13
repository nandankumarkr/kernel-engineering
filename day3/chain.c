#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<err.h>
int main(){
	int fd[2];
	if(pipe(fd) == -1){
		err(EXIT_FAILURE,"pipe");
	}
	pid_t pid1 = fork();
	if(pid1<0){
		err(EXIT_FAILURE,"fork");
	}
	if(pid1 == 0){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		char*args[] = {"ls","-la",NULL};
		execvp(args[0],args);
		perror("EXEC");
		exit(1);
	}
	pid_t pid2 = fork();
	if(pid2<0){
		err(EXIT_FAILURE,"fork");
	}
	if(pid2==0){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		char*args[] = {"grep",".c",NULL};
		execvp(args[0],args);
		perror("exec");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return 0;
}
