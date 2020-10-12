#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
/*
 * Argv 1 = pierwszy mutex zablokuje wątek główny
 */
pthread_mutex_t blokada;

void* newThread(void * arg){
    int* scenariusz = (int *) arg;
    
    if(*scenariusz == 1){
        sleep(1);
    }
    pthread_mutex_lock(&blokada);
    printf("Mam przejęty mutex FUNKCJA TID = %ld\n",pthread_self());
    sleep(10);
    pthread_mutex_unlock(&blokada);
}

int main(int argc, char* argv[]){
    int arg = atoi(argv[1]);
    pthread_t myThread;
    
    pthread_mutex_init(&blokada, NULL);
    
    if(pthread_create(&myThread,NULL,newThread,&arg)){
        printf("Nie udało się utworzyć wątku\n");
        exit(-1);
    }
    if(arg != 1)
        sleep(1);
    pthread_mutex_lock(&blokada);
    printf("Mam przejęty mutex WĄTEK GŁÓWNY TID = %ld\n",pthread_self());
    sleep(10);
    pthread_mutex_unlock(&blokada);
    
    pthread_join(myThread, NULL);
    return 0;
}
