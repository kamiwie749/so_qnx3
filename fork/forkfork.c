#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void rekurencja(int ile, int ileTab[], int kursor){
    int j;
    if(!fork()){
        for(j = 0; j < ileTab[kursor]; j++){
            printf("Proces potomny PID = %d PPID = %d\n",getpid(),getppid());
            sleep(1);
        }
        //exit(ile); //nwm jak dobrze zakończyć te procesy
        if(ile>1){
            printf("tak\n");
            rekurencja(ile-1, ileTab, kursor + 1);
        }
    }
}


int main(int argc, char* argv[]){
    int i, kursor, status, kod, pid, *ileTab;
    int ile = argc - 2; //- nazwa - maciezysty
    pid = getpid();
    ileTab = malloc(ile*sizeof(int));
    for(i = 0; i < ile; i++){
        ileTab[i] = atoi(argv[i+2]);
    }
    kursor = 0;
    
    rekurencja(ile, ileTab, kursor);
    
    if(getpid() == pid){
        for(i=0; i < atoi(argv[1]); i++){
            printf("Proces macierzysty PID = %d, PPID = %d\n",getpid(), getppid());
            sleep(1);
        }
    }
    
    for(i=2; i<argc ;i++){
        kod = wait(&status);
        //printf("Zamknieto proces %d  kodem %d\n",kod, WEXITSTATUS(status));
    }
    
   return 0;
}











