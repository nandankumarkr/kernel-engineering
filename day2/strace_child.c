#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid<0){
		perror("fork");
		return 1;
	}else if(pid == 0){
		char*args[] = {"ls","-la",NULL};
		execvp(args[0],args);
		perror("execvp");
		return 1;
	}else{
		wait(NULL);
	}
	return 0;
}
