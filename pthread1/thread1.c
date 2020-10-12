#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/* 
 * program tworzy drugi wątek ptóry wypisuje argv[1] razy TIP oraz wątek(główny)
 * który wypisuje argv[2] razy TIP 
 */ 

void * myThread(void* arg){
    int i, n;
    n = *(int *)arg;
    //n=arg;
    for(i=0; i<n; i++){
    //while(1){
        printf("Funkcja Watek TID = %ld PID = %d\n",pthread_self(),getpid());
        sleep(1);
    }
}

int main(int argc, char* argv[]){
    int i, n;
    n = atoi(argv[1]);
    pthread_t newThread;
    //pthread_create(&newThread, NULL, myThread, &n);
    if(pthread_create(&newThread, NULL, myThread, &n)){
        printf("Nie udało się utworzyć wątku\n");
    }
    
    //watek(główny)
    for(i=0; i<atoi(argv[2]); i++){
    //while(1){
        printf("Watek TID = %ld PID = %d\n",pthread_self(),getpid());
        sleep(1);
    }
    
    //czekanie na zakończenie się drugiego wątku
    //pthread_join(newThread, NULL);
    
    printf("Watki sie zakonczyły\n");
    
    return 0;
}
