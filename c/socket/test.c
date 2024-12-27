#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd, newfd;
    struct addrinfo hints, *res;
    struct sockaddr_storage client_addr;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "1234", &hints, &res) != 0) {
        perror("getaddrinfo error");
        return 1;
    }

    if ((sockfd = socket(res->ai_family, res->ai_socktype, 0)) < 0) {
        perror("socket error");
        freeaddrinfo(res);
        return 2;
    }

    int opt = 1;
    // Correct the size parameter to sizeof(opt)
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SO_REUSEADDR error");
        close(sockfd);
        freeaddrinfo(res);
        return 3;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SO_REUSEPORT error");
        close(sockfd);
        freeaddrinfo(res);
        return 3;
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("bind error");
        close(sockfd);
        freeaddrinfo(res);
        return 4;
    }

    if (listen(sockfd, 10) < 0) {
        perror("listen error");
        close(sockfd);
        freeaddrinfo(res);
        return 5;
    }

    int client_size = sizeof client_addr;
    if ((newfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_size)) < 0) {
        perror("accept error");
        close(sockfd);
        freeaddrinfo(res);
        return 6;
    }

    // Send a message to the client
    char *msg = "Connected!\n";
    int msglen = strlen(msg);
    send(newfd, msg, msglen, 0);

    // Properly shutdown and close the sockets
    if (shutdown(newfd, SHUT_RDWR) < 0) {
        perror("shutdown newfd error");
    }
    close(newfd);

    if (shutdown(sockfd, SHUT_RDWR) < 0) {
        perror("shutdown sockfd error");
    }
    close(sockfd);

    freeaddrinfo(res);

    return 0;
}
