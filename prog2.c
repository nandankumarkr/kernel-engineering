#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
	int src_fd = open(argv[1],O_RDONLY);
	if(src_fd<0){
		perror("open");
		return 1;
	}
	int dest_fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC ,0644);
	if(dest_fd<0){
		perror("open dest");
		return 1;
	}
	char buff[4096];
	ssize_t bytes_read;
	while((bytes_read = read(src_fd,buff,sizeof(buff)))>0){
		ssize_t written = 0;
		while(written<bytes_read){
			ssize_t ret = write(dest_fd,buff+written,bytes_read-written);
			if(ret == -1){
				perror("write");
				close(src_fd);
				close(dest_fd);
				return 1;
			}
			written+=ret;
		}
	}
	if(bytes_read == -1){
		perror("read");
		close(src_fd);
		close(dest_fd);
		return 1;
	}
	return 0;
}
