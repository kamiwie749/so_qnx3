#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


void * newThread(void * arg){
    int *n;
    int *result;
    n = (int*)arg;
    *n=(*n)*(*n);
    printf("Funkcja Watek TID = %ld PID =%d\n",pthread_self(),getpid());
    sleep(1);
    pthread_exit(n);
}

int main(int argc, char* argv[]){
    int liczba = atoi(argv[1]);
    int *wynik;
    pthread_t myThread;
    printf("Wątek główny ,TID = %ld PID =%d\n",pthread_self(),getpid());
    if(pthread_create(&myThread,NULL,newThread,&liczba)){
        printf("Nie udało się utworzyć wątku\n");
        exit(-1);
    }
    pthread_join(myThread,(void**)&wynik);
    printf("Wynik = %d\n",*wynik);
    return 0;
}
