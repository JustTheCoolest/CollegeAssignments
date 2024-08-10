#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_a;
    serv_a.sin_family = AF_INET;
    serv_a.sin_addr.s_addr = INADDR_ANY;
    serv_a.sin_port = htons(1024);
    char send_pay[] = "I'm Waiting";
    sendto(s, send_pay, sizeof(send_pay), 0, (struct sockaddr *)&serv_a, sizeof(serv_a));
    int msg_len = 255;
    char message[msg_len];
    recvfrom(s, message, sizeof(message), 0, NULL, NULL);
    printf("%s\n", message);
    close(s);
}