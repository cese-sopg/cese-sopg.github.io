
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    switch (pid = fork())
    {
        case -1:
            perror("fork"); /* something went wrong */
            exit(1);
            break;

            /* parent exits */
        case 0:
            printf(" CHILD: This is the child process!\n");
            printf(" CHILD: My PID is %d\n", getpid());
            printf(" CHILD: My parent's PID is %d\n", getppid());
            printf(" CHILD: Enter my exit status (make it small): ");
            int rv;
            scanf(" %d", &rv);
            printf(" CHILD: I'm outta here!\n");
            exit(rv);
            break;


        default:
            printf("PARENT: This is the parent process!\n");
            printf("PARENT: My PID is %d\n", getpid());
            printf("PARENT: My childs PID is %d\n", pid);
            int retorno;
            wait(&retorno);
            printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(retorno));
            printf("PARENT: I'm outta here!\n");
    }
}

