#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd = open("numbers.bin",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd<0){
		perror("open");
		return 1;
	}
	for(int i=0;i<100;i++){
		if(write(fd,&i,sizeof(int))!=sizeof(int)){
			perror("write");
			close(fd);
			return 1;
		}
	}
	printf("reverse order\n");
	for(int i=99;i>=0;i--){
		int num;
		if(lseek(fd,i*sizeof(int),SEEK_SET) == -1){
			perror("lseek");
			close(fd);
			return 1;
		}
		if(read(fd,&num,sizeof(int))!=sizeof(int)){
			perror("read");
			close(fd);
			return 1;
		}
		printf("%d ",num);
	}
	printf("\n\n");
	int value = 999;
	if(lseek(fd,49*sizeof(int),SEEK_SET)==-1){
		perror("lseek");
		close(fd);
		return 1;
	}
	if(write(fd,&value,sizeof(int))!=sizeof(int)){
		perror("write");
		close(fd);
		return 1;
	}
	if(lseek(fd,0,SEEK_SET)==-1){
		perror("lseek");
		close(fd);
		return 1;
	}
	printf("after modifying 50th element\n");
	int num;
	while(read(fd,&num,sizeof(int))==sizeof(int)){
		printf("%d ",num);
	}
	printf("\n");
	close(fd);
	return 0;
}
