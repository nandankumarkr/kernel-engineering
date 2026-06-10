#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(){
	int fd = open("fork.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
	pid_t pid = fork();
	if(pid == 0){
		write(fd,"child\n",6);
	}else{
		write(fd,"parent\n",7);
		wait(NULL);
	}
	close(fd);
	return 0;
}

