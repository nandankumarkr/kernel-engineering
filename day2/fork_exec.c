#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){
	pid_t pid = fork();
	if(pid<0){
		perror("fork");
		return 1;
	}
	if(pid == 0){
		char*args[] = {"ls","-la",NULL};
		execvp(args[0],args);
		perror("execvp");
		return 1;
	}else{
		int status;
		wait(&status);
		printf("child exited with status %d\n",WEXITSTATUS(status));
	}
	return 0;
}
