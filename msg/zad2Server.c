#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#define SIZE 20

int main(void)
{
    int receiveStatus;
    char wiadomosc[SIZE], odpowiedz[SIZE];
    struct _msg_info info;

    name_attach_t *name;
    name = name_attach(NULL, "server", 0);

    printf("Server\n");
    while (1)
    {
        while (receiveStatus = MsgReceive(name->chid, &wiadomosc, sizeof(wiadomosc), &info))
        {
            printf("Klient wysłał wiadomość : %s\n", wiadomosc);
            printf("Podaj odpowiedź \t");
            scanf("%s", &odpowiedz);
            MsgReply(receiveStatus, 10, &odpowiedz, sizeof(odpowiedz));
        }
    }
    return 0;
}