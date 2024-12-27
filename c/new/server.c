#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <ifaddrs.h>
#include <errno.h>

#define PORT "42069"
#define MAX_CLIENTS 10

typedef struct {
	int fd;
	int client_id;
} client_t;

client_t clients[MAX_CLIENTS];
int client_id_counter = 0;
int num_clients = 0;

void get_server_ip(char *ip_buf, size_t buf_size) {
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		perror("getiffaddr error");
		exit(EXIT_FAILURE);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		family = ifa->ifa_addr->sa_family;

		if (family == AF_INET) {
			s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

			if (s != 0) {
				perror("getnameinfo error");
				continue;
			}

			if (strncmp(host, "127.0.0.1", 10) != 0) {
				strncpy(ip_buf, host, buf_size);
				break;
			}
		}
	}
}

int main() {
	int sockfd, clientfd, opt = 1;
	struct addrinfo hints, *res, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
		perror("getaddrinfo error");
		return EXIT_FAILURE;
	}

	for(p = res; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("socket creation failed");
			continue;
		}

		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("bind error");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to bind to any address\n");
		freeaddrinfo(res);
		return EXIT_FAILURE;
	}

	char ip_buf[256] = {0};
	get_server_ip(ip_buf, sizeof(ip_buf));
	
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) < 0) {
		perror("gethostname error");
		close(sockfd);
		return EXIT_FAILURE;
	} else {
		char buf[INET6_ADDRSTRLEN] = {0};
		switch(res->ai_family) {
			case AF_INET:
				inet_ntop(res->ai_family, &(((struct sockaddr_in *)res->ai_addr)->sin_addr), buf, sizeof(buf));
				break;
			case AF_INET6:
				inet_ntop(res->ai_family, &(((struct sockaddr_in6 *)res->ai_addr)->sin6_addr), buf, sizeof(buf));
				break;
			default:
				fprintf(stderr, "Unknown local address family\n");
				close(sockfd);
				return EXIT_FAILURE;
		}

		printf("Now listening on server \033[1;32m%s (%s)\033[0m on port \033[1;32m%s\033[0m\n", hostname, ip_buf, PORT);
	}

	struct sockaddr_storage client_addr;
	socklen_t client_size = sizeof(client_addr);
	char buf[INET6_ADDRSTRLEN];

	if (listen(sockfd, 10) < 0) {
		perror("listen error");
		close(sockfd);
		return EXIT_FAILURE;
	}

	struct pollfd fds[MAX_CLIENTS + 2];
	//int num_clients = 0, clientid = 0;

	fds[0].fd = sockfd;
	fds[0].events = POLLIN;

	fds[1].fd = STDIN_FILENO;
	fds[1].events = POLLIN;

	printf("Type 'quit' to gracefully shut down the server.\n");

	while(1) {
		int poll_count = poll(fds, num_clients + 2, -1);
		if (poll_count == -1) {
			perror("poll error");
			close(sockfd);
			return EXIT_FAILURE;
		}

		if (poll_count == 0) {
			continue;
		}

		if (fds[1].revents & POLLIN) {
			char command[10];
			if (fgets(command, sizeof(command), stdin) != NULL) {
				command[strcspn(command, "\n")] = '\0';

				if (strcmp(command, "quit") == 0) {
					printf("Shutting down server...\n");
					break;
				}
			}
		}

		if (fds[0].revents & POLLIN) {
			if ((clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_size)) < 0) {
				perror("accept error");
				close(sockfd);
				return EXIT_FAILURE;
			}

			if (num_clients < MAX_CLIENTS) {
	  			//client_id_counter++;
				//clients[num_clients].fd = clientfd;
				//clients[num_clients].client_id = client_id_counter;
				fds[num_clients + 2].fd = clientfd;
				fds[num_clients + 2].events = POLLIN;
				num_clients++;

				in_port_t p = {0};
				if (client_addr.ss_family == AF_INET) {
					struct sockaddr_in *addr_in = (struct sockaddr_in *)&client_addr;
					inet_ntop(AF_INET, &(addr_in->sin_addr), buf, sizeof(buf));
					p = ntohs(addr_in->sin_port);

				} else if (client_addr.ss_family == AF_INET6) {
					struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6 *)&client_addr;
					inet_ntop(AF_INET6, &(addr_in6->sin6_addr), buf, sizeof(buf));
					p = ntohs(addr_in6->sin6_port);

				} else {
					printf("Unknown address family\n");
				}

				printf("Client #%d connected with IP: %s and port: %hu\n", clientfd, buf, p);
				char *msg = "Hello there from server!\n";
				send(clientfd, msg, strlen(msg), 0);
			} else {
				close(clientfd);
				printf("Maximum client limit reached. Closing new conncetion\n");
			}
		}

		for (int i = 2; i < num_clients + 2; i++) {
			if (fds[i].revents & POLLIN) {
				char rmsg[1024] = {0};
				size_t bytes_received = recv(fds[i].fd, rmsg, sizeof(rmsg), 0);
				rmsg[strcspn(rmsg, "\n")] = '\0';

				if (bytes_received > 0) {
					printf("Client #%d says: %s\n", fds[i].fd, rmsg);
				} else if (bytes_received == 0) {
					printf("Client #%d disconnected...\n", fds[i].fd);
					fds[i].revents = 0;
					close(fds[i].fd);

					fds[i + 2] = fds[num_clients + 1];
					num_clients--;
					i--;
				}
			}
		}
	}

	for (int i = 2; i < num_clients + 2; i++) {
		close(fds[i].fd);
	}

	close(sockfd);
	freeaddrinfo(res);

	return EXIT_SUCCESS;
}
