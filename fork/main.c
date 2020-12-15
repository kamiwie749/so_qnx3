#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i, j, status, numer, pid;

    //instrukcje procesu macierzystego
    pid = getpid();

    for (i = 2; i < argc; i++)
    {
        if (!fork())
        {
            for (j = 0; j < atoi(argv[i]); j++)
            {
                printf("Proces potomny PID = %d, PPID = %d\n", getpid(), getppid());
                sleep(1);
            }
            exit(i);
        }
    }
    if (getpid() == pid)
    {
        for (i = 0; i < atoi(argv[1]); i++)
        {
            printf("Proces macierzysty PID = %d, PPID = %d\n", getpid(), getppid());
            sleep(1);
        }
    }

    for (i = 2; i < argc; i++)
    {
        numer = wait(&status);
        printf("Zamknieto proces %d  kodem %d\n", numer, WEXITSTATUS(status));
    }

    return 0;
}

//test