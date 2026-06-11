#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5

int main()
{
    pid_t pids[NUM_CHILDREN];
    int status;

    /* Create 5 children */
    for(int i = 0; i < NUM_CHILDREN; i++)
    {
        pid_t pid = fork();

        if(pid < 0)
        {
            perror("fork");
            return 1;
        }

        if(pid == 0)
        {
            printf("Child %d started (PID=%d)\n",
                   i, getpid());

            sleep(i + 1);  // simulate some work

            printf("Child %d exiting with status %d\n",
                   i, i);

            exit(i);
        }

        pids[i] = pid;
    }

    /* Parent collects exit status of each child */
    for(int i = 0; i < NUM_CHILDREN; i++)
    {
        pid_t child_pid = waitpid(pids[i], &status, 0);

        if(child_pid == -1)
        {
            perror("waitpid");
            continue;
        }

        if(WIFEXITED(status))
        {
            printf("Child PID %d exited with status %d\n",
                   child_pid,
                   WEXITSTATUS(status));
        }
        else
        {
            printf("Child PID %d did not exit normally\n",
                   child_pid);
        }
    }

    return 0;
}
