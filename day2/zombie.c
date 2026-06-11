#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){
	pid_t pid = fork();
	if(pid<0){
		perror("fork\n");
		exit(1);
	}else if(pid == 0){
	}else{
		sleep(10);
		wait(NULL);
	}
	return 0;
}
