#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in a;
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = INADDR_ANY;
    a.sin_port = htons(1024);
    int b = bind(s, (struct sockaddr *)&a, sizeof(a));
    struct sockaddr client_a;
    socklen_t client_size = sizeof(client_a);
    char buffer[255];
    recvfrom(s, buffer, sizeof(buffer), 0, &client_a, &client_size);
    printf("%s\n", buffer);
    char message[] = "Hello World!";
    sendto(s, message, sizeof(message), 0, &client_a, client_size);
    close(s);
}