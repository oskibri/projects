#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
		return 2;
	}


	if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("bind error");
		return 3;
	}

	char hostname[1024];
	if (gethostname(hostname, sizeof(hostname)) < 0) {
		perror("gethostname error");
		exit(7);
	}
	printf("Now listening on server: %s\n\n", hostname);

	int listen_ret, count = 0;
	while((listen_ret = listen(sockfd, 1)) >= 0 && count < 3) {
		int client_size = sizeof client_addr;

		if ((newfd = accept(sockfd, (struct sockaddr *)&client_addr, &(client_size))) < 0) {
			perror("accept error");
			return 5;
		}

		char msg[] = "Connected!\n";
		int msglen = strlen(msg);
		send(newfd, msg, msglen, 0);

		struct sockaddr_in c;
		socklen_t c_size = sizeof(c);
		getpeername(newfd, (struct sockaddr *)&c, &c_size);

		char client_addr_buf[INET_ADDRSTRLEN];
		if (inet_ntop(c.sin_family, &(c.sin_addr), client_addr_buf, INET_ADDRSTRLEN) == NULL) {
			perror("inet_ntop error");
			exit(6);
		}
		printf("IP: %s Port: %d\n", client_addr_buf, ntohs(c.sin_port));

		char buf[1024];
		recv(newfd, buf, sizeof buf, 0);
		printf("Incoming message: %s", buf);

		close(newfd);

		printf("\n");
		count++;
	} 

	if (listen_ret < 0) {
		perror("listen error");
		return 4;
	}


	close(sockfd);
	freeaddrinfo(res);

	return 0;
}
