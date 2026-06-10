#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){
	 int fd = open("test.txt",O_RDONLY);
	if(fd<0){
		perror("open");
		return 1;
	}
	char ch;
	while(read(fd,&ch,1)>0){
		write(STDOUT_FILENO,&ch,1);
	}
	close(fd);
	return 0;
}

