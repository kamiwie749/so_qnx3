#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int i, j, k, w, status, kod;
    
    //instrukcje procesu macierzystego 
    for(k=0;k<atoi(argv[1]);k++){
            printf("Proces macierzysty PID = %d, PPID = %d\n",getpid(), getppid());
            sleep(1);
        }
    
    for(i=2;i<argc;i++){
        if(!fork()){
            for(j=0;j<atoi(argv[i]);j++){
                printf("Proces potomny PID = %d, PPID = %d\n",getpid(), getppid());
                sleep(1);
            }
            exit(i);
        }
    }
    
    for(w=2;w<argc; w++){
        kod = wait(&status);
        printf("Zamknieto proces %d  kodem %d\n",kod, WEXITSTATUS(status));
    }
    
    return 0;
}
