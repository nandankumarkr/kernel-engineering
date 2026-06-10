#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
int main(int argc,char*argv[]){
	struct stat st;
	int ret = stat(argv[1],&st);
	if(ret<0){
		perror("stat");
		exit(1);
	}
	printf("size of the file is %ld\n",st.st_size);
	printf("permissions :\n");
	printf((st.st_mode & S_IRUSR)?"r":"-");
	printf((st.st_mode & S_IWUSR)?"w":"-");
	printf((st.st_mode & S_IXUSR)?"x":"-");
	printf((st.st_mode & S_IRUSR)?"r":"-");
	printf((st.st_mode & S_IWUSR)?"w":"-");
	printf((st.st_mode & S_IXUSR)?"x":"-");
	printf((st.st_mode & S_IRUSR)?"r":"-");
	printf((st.st_mode & S_IWUSR)?"w":"-");
	printf((st.st_mode & S_IXUSR)?"x":"-");
	printf("\n");
	printf("Inode number %lu\n",st.st_ino);
	printf("hard links %ld \n",st.st_nlink);
	printf("last access %s\n",ctime(&st.st_atime));
	printf("last modified %s",ctime(&st.st_mtime));
	printf("block size : %ld bytes\n",st.st_blksize);
	printf("blocks allowed :%ld bytes\n",st.st_blocks);
	return 0;
}
