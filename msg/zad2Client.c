#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#define SIZE 20

int main(void)
{
    int rsendStatus;
    int connection;
    char wiadomosc[SIZE], odpowiedz[SIZE];

    connection = name_open("server", 0);

    printf("Klient\n");
    while (1)
    {
        printf("Podaj treść wiadomości\t");
        scanf("%s", &wiadomosc);
        sendStatus = MsgSend(connection, &wiadomosc, sizeof(wiadomosc), &odpowiedz, sizeof(odpowiedz));
        printf("Status otrzymanej odpowiedzi = %d\nTreść : %s\n", sendStatus, odpowiedz);
    }
    return 0;
}