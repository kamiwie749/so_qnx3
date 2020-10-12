#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int mojaZmiennaglobalna = 0;
pthread_mutex_t blokada;

void *mojWatek (void * arg){
    int i, j;
    for(i=0; i<20; i++){
        pthread_mutex_lock(&blokada);
        j=mojaZmiennaglobalna;
        j=j+1;
        printf(".\n");
        fflush(stdout);
        sleep(1);
        mojaZmiennaglobalna=j;
        pthread_mutex_unlock(&blokada);
    }
    return NULL;
}

int main(void){
    pthread_t nowyWatek;
    int i;
    pthread_mutex_init(&blokada, NULL);
    if(pthread_create(&nowyWatek,NULL,mojWatek,NULL)){
        printf("Błąd przy tworzeniu wątku \n");
        //absort();
	return -1;
    }
    
    for(i=0; i<20; i++){
        pthread_mutex_lock(&blokada);
        mojaZmiennaglobalna=mojaZmiennaglobalna+1;
        printf("o\n");
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&blokada);
    }
    if(pthread_join(nowyWatek, NULL)){
        printf("Błąd przy kończeniu wątku\n");
        //absort();
	return -2;
    }
    
    printf("\nMoja zmienna globalna wynosi %d\n",mojaZmiennaglobalna);
    exit(0);
    
}
