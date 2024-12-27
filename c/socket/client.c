#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	int sock;
	struct addrinfo hints, *res;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, "1234", &hints, &res);
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
		perror("connect");
		return 3;
	}
	char msg[] = "Hello, world!\n";
	send(sock, msg, strlen(msg), 0);

	return 0;
}
