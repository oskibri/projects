#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>

static void finish(int sig);

int main(void) {
	int num = 0;
	signal(SIGINT, finish);

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	echo();

	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_CYAN, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
	}

	for(;;) {
		int c = getch();
		attrset(COLOR_PAIR(num % 8));
		if (c == '\n') {
			addch('\n');
		}
		num++;
	}

	finish(0);
}
static void finish(int sig) {
	endwin();
	exit(0);
}
