#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>

int main() {
	int sockfd, clientfd;
	struct addrinfo hints, *res;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	int opt=1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(NULL, "1234", &hints, &res);

	if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
		perror("bind error");
		close(sockfd);
		return EXIT_FAILURE;
	}
	struct pollfd pfds[2];
	listen(sockfd, 1);

	pfds[0].fd = STDIN_FILENO;
	pfds[0].events = POLLIN;
	pfds[1].fd = sockfd;
	pfds[1].events = POLLIN;

	poll(pfds, 2, 2500);


	while(1) {
		if (pfds[0].revents & POLLIN) {
			pfds[0].revents = 0;
			printf("Got it!\n");
			break;
		}

		if (pfds[1].revents & POLLIN) {
			pfds[1].revents = 0;
			//clientfd = accept(sockfd, NULL, NULL);
			//if (clientfd == -1) {
			//	perror("accept error");
			//}
			printf("snibri\n");
		}
	}

	//close(clientfd);
	close(sockfd);
	return EXIT_SUCCESS;
}
