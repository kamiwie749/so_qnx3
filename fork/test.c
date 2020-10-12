#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int p, w;
    printf("Proces PID = %d, PPID = %d\n",getpid(), getppid());
    
    if(!fork()){
        printf("Proces potomny PID = %d, PPID = %d\n",getpid(), getppid());
        if(!fork()){
            printf("Proces potomny PID = %d, PPID = %d\n",getpid(), getppid());
        }
    }
    
    
    return 0;
}
