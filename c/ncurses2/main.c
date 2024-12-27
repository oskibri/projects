#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "helper.h"

typedef struct {
	int h, w;
	int y, x;
	char *text;
} button;

int main(void) {
	initscr();
	noecho();
	curs_set(0);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	mouseinterval(0);
	keypad(stdscr, true);
	refresh();

	MEVENT event;

	WINDOW *win = newwin(LINES - 10, COLS - 10, 5, 5);
	box(win, 0, 0);
	wrefresh(win);

	button button1 = {5, 10, 6, 6, "OK"};
	WINDOW *button1win = subwin(win, button1.h, button1.w, button1.y, button1.x);
	mvwprintw(button1win, button1.h / 2, button1.w / 2 - 1, "%s", button1.text);
	box(button1win, 0, 0);
	wrefresh(button1win);

	int ch;
	while ((ch = getch()) != 'q') {
		if (ch == KEY_MOUSE && getmouse(&event) == OK) {
			if (inside_box(button1win, event)) {
				button1.text = "Touched!";
			} else {
				button1.text = "OK";
			}
		}

		wclear(button1win);
		box(button1win, 0, 0);
		mvwprintw(button1win, button1.h / 2, button1.w / 2 - 1, "%s", button1.text);
		wrefresh(button1win);
	}
	

	delwin(win);
	endwin();
	return 0;
}
