#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid==0){
		printf("this is child process,my pid is %d and parent pid is %d\n",getpid(),getppid());
		return 0;
	}else{
		printf("this is parent process,my pid is %d and child pid is %d\n",getpid(),pid);
		wait(NULL);
	}
	return 0;
}
