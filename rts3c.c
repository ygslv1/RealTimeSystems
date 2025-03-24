#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char smsg[20];
    char rmsg[20];
    int coid;
    long serv_pid;

    printf("Client made by Shvetsov i914b\n");
    printf("Enter server's PID: ");
    scanf("%ld", &serv_pid);

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);

    while (1) {
        printf("Client >> ");
        fflush(stdout);
        scanf("%s", &smsg);

        if (strcmp(smsg, "exit") == 0) {
            break;
        }

        if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
            perror("MsgSend failed");
            continue;
        }

        printf("Server >> %s\n", rmsg);
    }

    return(1);
}