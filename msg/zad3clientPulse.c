#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

int main(void)
{
    int sendStatus;
    int connection;
    struct _pulse pulse;
    pulse.code = 1;
    pulse.value.sival_int = 2;
    connection = name_open("serverPulse", 0);
    printf("Klient\n");
    while (1)
    {
        printf("Wysyłam puls\n");
        sendStatus = MsgSendPulse(connection, 10, pulse.code, pulse.value.sival_int);
        printf("Code =%d, value = %d\n", pulse.code, pulse.value.sival_int);
        sleep(10);
        pulse.code++;
        pulse.value.sival_int++;
    }
    return 0;
}