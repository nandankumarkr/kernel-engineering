#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<err.h>
#include<sys/wait.h>
int main(){
	int p2c[2];
	int c2p[2];
	if(pipe(p2c) == -1 || pipe(c2p) == -1){
		err(EXIT_FAILURE,"pipe");
	}
	pid_t pid = fork();
	if(pid < 0){
		err(EXIT_FAILURE,"fork");
	}
	if(pid == 0){
		close(p2c[1]);
		close(c2p[0]);
		int num,square;
		for(int i=0;i<5;i++){
			read(p2c[0],&num,sizeof(num));
			square = num*num;
			write(c2p[1],&square,sizeof(square));
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}else{
		close(p2c[0]);
		close(c2p[1]);
		int num,square;
		for(int i=0;i<5;i++){
			printf("Enter number : %d\n",i+1);
			scanf("%d",&num);
			write(p2c[1],&num,sizeof(num));
			read(c2p[0],&square,sizeof(square));
			printf("the square of the number is %d \n",square);
		}
		close(p2c[1]);
		close(c2p[0]);
		wait(NULL);
	}
	return 0;
}
