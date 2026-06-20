#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(){
	char buf[512];
	while(1){
		printf("myshell> ");
		if(fgets(buf,512,stdin)==NULL){
			printf("exiting\n");
			exit(0);
		}
		if(strcmp(buf,"exit") == 0){
			printf("exiting\n");
			exit(0);
		}
		printf("%s",buf);
	}
	return 0;
}

