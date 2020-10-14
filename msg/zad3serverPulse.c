#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

int main(void)
{
    int receiveStatus;
    struct _pulse pulse;

    name_attach *name;
    name = name_attach(NULL, "serverPulse", 0);

    printf("Server\n");
    while (1)
    {
        receiveStatus = MsgReceivePulse(name->chid, &pulse, sizeof(pulse), NULL);
        printf("Klient wysłał impuls o kodzie %d i zawartości %d\n", pulse.code, pulse.value.sival_int);
    }
    return 0;
}