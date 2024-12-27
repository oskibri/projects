#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int s;
	char ip4[INET_ADDRSTRLEN];
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_flags = AI_CANONNAME;

	int e = getaddrinfo("servebolt.com", "http", &hints, &res);
	if (e != 0) {
		fprintf(stderr, "(netdb.h) -> getadddrinfo() = %d ### Error: %s\n", e, gai_strerror(e));
		exit(1);
	}

	struct sockaddr_in *sin = (struct sockaddr_in *)res->ai_addr;

	if (inet_ntop(sin->sin_family, &(sin->sin_addr), ip4, INET_ADDRSTRLEN) == NULL) {
		perror("inet_ntop()");
		exit(2);
	}

	printf("%s\n", ip4);

	char ip[1024];
	struct sockaddr_in sa;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_family = AF_INET;
	inet_ntop(AF_INET, &(sa.sin_addr), ip, INET_ADDRSTRLEN);
	printf("%s\n", ip);

	int status;
	struct addrinfo h, *servinfo;

	memset(&h, 0, sizeof h);
	h.ai_family = AF_INET;
	h.ai_socktype = SOCK_STREAM;
	h.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, "3333", &h, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	char bla[INET6_ADDRSTRLEN];
	switch(servinfo->ai_addr->sa_family) {
		case AF_INET:
			struct sockaddr_in *sni = (struct sockaddr_in *)servinfo->ai_addr;

			if (inet_ntop(AF_INET, &(sni->sin_addr), bla, INET_ADDRSTRLEN) == NULL) {
				perror("inet_ntop error");
				exit(2);
			}

			printf("2 --- ip: %s and port: %d\n", bla, ntohs(sni->sin_port));
			break;
		case AF_INET6:
			struct sockaddr_in6 *sni6 = (struct sockaddr_in6 *)servinfo->ai_addr;

			if (inet_ntop(AF_INET6, &(sni6->sin6_addr), bla, INET6_ADDRSTRLEN) == NULL) {
				perror("inet_ntop error");
				exit(2);
			}

			printf("10 --- ip: %s and port: %d\n", bla, ntohs(sni6->sin6_port));
			break;
		default:
			fprintf(stderr, "Something went wrong");
			exit(3);
	}


	

	freeaddrinfo(servinfo);
	freeaddrinfo(res);
	return 0;
}
