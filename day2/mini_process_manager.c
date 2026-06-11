#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define NUM_CHILDREN 4

int main()
{
    char *commands[NUM_CHILDREN][5] = {
        {"sleep", "2", NULL},
        {"ls", "/tmp", NULL},
        {"echo", "hello from child", NULL},
        {"cat", "/proc/version", NULL}
    };

    pid_t pids[NUM_CHILDREN];
    struct timeval start[NUM_CHILDREN];
    struct timeval end;

    for(int i = 0; i < NUM_CHILDREN; i++)
    {
        gettimeofday(&start[i], NULL);

        pid_t pid = fork();

        if(pid < 0)
        {
            perror("fork");
            exit(1);
        }

        if(pid == 0)
        {
            execvp(commands[i][0], commands[i]);

            perror("execvp");
            exit(1);
        }

        pids[i] = pid;
    }

    printf("\n=== Process Manager Report ===\n\n");

    for(int i = 0; i < NUM_CHILDREN; i++)
    {
        int status;

        waitpid(pids[i], &status, 0);

        gettimeofday(&end, NULL);

        double elapsed =
            (end.tv_sec - start[i].tv_sec) +
            (end.tv_usec - start[i].tv_usec) / 1000000.0;

        printf("PID: %d\n", pids[i]);

        printf("Command: %s\n", commands[i][0]);

        if(WIFEXITED(status))
        {
            printf("Exit Status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("Did not exit normally\n");
        }

        printf("Runtime: %.3f seconds\n",
               elapsed);

        printf("-------------------------\n");
    }

    return 0;
}
