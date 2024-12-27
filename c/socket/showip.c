#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include <sys/types.h>
//#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
//#include <netinet/in.h>

int main(int argc, char *argv[]) {
	struct addrinfo hints, *res, *p;
	char ip[INET6_ADDRSTRLEN], ipver[50];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(argv[1], NULL, &hints, &res) != 0) {
		perror("getaddrinfo error");
		return 2;
	}

	for(p = res; p != NULL; p = p->ai_next) {
		void *addr;
		switch(p->ai_family) {
			case AF_INET: {
				struct sockaddr_in* ip4 = (struct sockaddr_in*)p->ai_addr;
				strncpy(ipver, "IPv4", sizeof ipver);
				addr = &(ip4->sin_addr);
				break;
			}
			case AF_INET6: {
				struct sockaddr_in6* ip6 = (struct sockaddr_in6*)p->ai_addr;
				strncpy(ipver, "IPv6", sizeof ipver);
				addr = &(ip6->sin6_addr);
				break;
			}
			default: {
				fprintf(stderr, "unknown address family: %d\n", p->ai_family);
				return 3;
			}
		}

		inet_ntop(p->ai_family, addr, ip, sizeof ip);
		printf("%s: %s\n", ipver, ip);
	}

	freeaddrinfo(res);
	return 0;
}

