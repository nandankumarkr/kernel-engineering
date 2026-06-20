#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
char **tokenizer(char*line){
	int capacity = 10;
	int count =0;
	char **argv = malloc(capacity * sizeof(char *));
	if(argv == NULL){
		return NULL;
	}
	char*p = line;
	while(*p){
		while(*p == ' '||*p == '\t'){
			p++;
		}
		if(*p=='\0')
			break;
		argv[count++] = p;
		while(*p && *p!= ' ' && *p!='\t'){
			p++;
		}
		if(*p){
			*p='\0';
			p++;
		}
		if(count>=capacity-1){
			capacity*=2;
			argv = realloc(argv,capacity*sizeof(char*));
			if(argv == NULL){
				return NULL;
			}
		}
	}
	argv[count] = NULL;
	return argv;
}
int main(){
	char buf[1024];
	while(1){
		printf("myshell>\n");
		if(fgets(buf,1024,stdin) == NULL){
			printf("exiting...\n");
			exit(1);
		}
		buf[strcspn(buf, "\n")] = '\0';
		char **argv = tokenizer(buf);
		pid_t pid = fork();
		if(pid == 0){
			execvp(argv[0],argv);
			exit(0);
		}else{
			wait(NULL);
		}
	}
	return 0;
}
