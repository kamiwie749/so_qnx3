/*
PARAMETRY WYWOLANIA PROGRAMU:
1 - Scenariusz 1 = tak aby utworzony proces czekał na odebranie wiadomości
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>

#define SIZE 20

int main(int arg, char *argv[])
{
    int receiveStatus, replyStatus;
    char odpowiedz[SIZE]; // definicja zmiennej typu msg_t do odebrania nfo oraz odpowiedzi
    int status;
    pid_t pid = getpid();
    int kanal = ChannelCreate(0); //tworzenie kanału wiadomości

    if (fork() == 0)
    {
        int connection, sendStatus;
        char wiadomosc[SIZE], odpowiedz[SIZE]; // definicja zmiennej typu msg_t do wysłania wiadomości oraz na odebranie odpowiedzi
        printf("Jestem procesem potomnym, PID = %d PPID = %d\n", getpid(), getppid());
        connection = ConnectAttach(0, pid, kanal, 0, 0); //nawiązanie połączenia z kanałem
        while (True)
        {
            printf("Podaj treść wiadomości\n");
            scanf("%s", &wiadomosc);
            sendStatus = MsgSend(connection, &wiadomosc, sizeof(wiadomosc), &odpowiedz, sizeof(odpowiedz));
            printf("Status odpowiedzi = %d\nTresc: %s", sendStatus, odpowiedz);
        }
        exit(0);
    }
    while (1)
    {
        if (atoi(argv[1]) == 1)
            sleep(30); // SCENARIUSZ 1 - tak aby utworzony proces czekał na odebranie wiadomości
        printf("Jestem procesem macierzystym, PID = %d PPID = %d\n", getpid(), getppid());
        receiveStatus = MsgReceive(kanal, &odpowiedz, sizeof(odpowiedz), NULL);
        printf("Potomek powiedzial mi %s\n", odpowiedz);
        scanf("%s", &odpowiedz);
        replyStatus = MsgReply(receiveStatus, 10, &odpowiedz, sizeof(odpowiedz));
    }
    wait(&status); //synchronizacja zakończenia procesów
    return 0;
}