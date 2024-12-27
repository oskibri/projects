#include <stdio.h>
#include <poll.h>

int main() {
	struct pollfd pfds[1];

	pfds[0].fd = 0;
	pfds[0].events = POLLIN;

	printf("Hit RETURN or wait 2.5 seconds for timeout\n");

	int num_events = poll(pfds, 1, 2500);

	if (num_events == 0) {
		printf("Timed out!\n");
	} else {
		//int pollin_happened = pfds[0].revents & POLLIN;
		if (pfds[0].revents == POLLIN) {
			printf("File descriptor %d is ready to read\n", pfds[0].fd);
		}
	}

	return 0;
}
