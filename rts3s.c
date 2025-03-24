#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>

void server(void)
{
    int rcvid;
    int chid;
    char str1[20];
    char str2[20];
    char n;
    int i;

    printf("Server start working\n");

    chid = ChannelCreate(0);

    printf("Channel id: %d\n", chid);
    printf("Pid: %d\n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, str1, sizeof(str1), NULL);
        printf("Client >> %s\n", str1);

        memset(str2, 0, sizeof(str2));
        n = 0;

        for (i = 0; i < sizeof(str1); i++) {
            if (str1[i] == 0) break;

            if (i == 0 || str1[i] == str1[i - 1]) {
                n++;
            } else {
                sprintf(str2, "%s%d%c", str2, n, str1[i - 1]);
                n = 1;
            }
        }
        sprintf(str2, "%s%d%c", str2, n, str1[i - 1]);

        MsgReply(rcvid, EOK, str2, sizeof(str2));
        printf("Server >> %s\n", str2);
    }
}

int main(void)
{
    printf("Server made by Shvetsov i914b\n");
    server();
    sleep(5);
    return(1);
}