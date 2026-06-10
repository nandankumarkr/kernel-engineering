#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd<0){
		perror("open");
		exit(1);
	}
	char msg[] = "hello kernel\n";
	write(fd,msg,13);
	close(fd);
	return 0;
}
