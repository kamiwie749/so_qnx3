#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void rekurencja(int ile, int ileTab[], int kursor){
    int j, status, numer;
    if(!fork()){
        for(j = 0; j < ileTab[kursor]; j++){
            printf("Proces potomny PID = %d PPID = %d\n",getpid(),getppid());
            sleep(1);
        }
        //exit(ile); //nwm jak dobrze zakończyć te procesy
        if(ile>1){
            rekurencja(ile-1, ileTab, kursor + 1);
        }
        if(ile>1){ //ostatni proces nie musi już czekać na zamnięcie bo nie ma potomka
            numer = wait(&status);
            printf("Zamknieto proces %d  kodem %d\n",numer, WEXITSTATUS(status));
        }
        exit(ile);
    }
}


int main(int argc, char* argv[]){
    int i, kursor, status, numer, pid, *ileTab;
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
    numer = wait(&status);
    printf("Zamknieto proces %d  kodem %d\n",numer, WEXITSTATUS(status));
    
   return 0;
}











