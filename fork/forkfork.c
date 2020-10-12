#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void rekurencja(int ile){
    printf("ile = %d\n",ile);
    if(!fork()){
        printf("Proces potomny PID = %d PPID = %d\n",getpid(),getppid());
        sleep(1);
        //exit(ile); //nwm jak dobrze zakończyć te procesy
        if(ile>0){
            printf("tak\n");
            rekurencja(ile-1);
        }
    }
}


int main(int argc, char* argv[]){
    int i, status, kod;
    
    //instrukcje procesu macierzystego 
    printf("Proces macierzysty PID = %d, PPID = %d\n",getpid(), getppid());
    sleep(1);
    
    rekurencja(atoi(argv[1]));
    
    for(i=0; i<atoi(argv[1]);i++){
        kod = wait(&status);
        printf("Zamknieto proces %d  kodem %d\n",kod, WEXITSTATUS(status));
    }
   //while(1);
   return 0;
}




