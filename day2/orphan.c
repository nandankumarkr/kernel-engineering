#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return 1;
    }

    if(pid == 0)
    {
        /* Child */

        printf("Child started\n");
        printf("Child PID        : %d\n", getpid());
        printf("Original Parent  : %d\n", getppid());

        printf("Sleeping for 5 seconds...\n");
        sleep(5);

        printf("\nAfter parent exits:\n");
        printf("Child PID        : %d\n", getpid());
        printf("New Parent PID   : %d\n", getppid());
    }
    else
    {
        /* Parent */

        printf("Parent PID       : %d\n", getpid());
        printf("Child PID        : %d\n", pid);

        printf("Parent exiting immediately...\n");

        exit(0);  // NO wait()
    }

    return 0;
}
