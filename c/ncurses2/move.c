#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

int main(void) {
	setlocale(LC_ALL, "");
	MEVENT event;

	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	mouseinterval(0);
	box(stdscr, 0, 0);
	refresh();

	int x = 0, y = 0;
	x = COLS / 2;
	y = LINES / 2;
	printw("Y: %d, X: %d", y, x);
	mvaddstr(y, x, "█");
	refresh();

	int ch, lastx, lasty;
	while ((ch = getch()) != 'q') {
		mvaddch(y, x, ' ');
		mvaddch(lasty, lastx, ' ');
		lasty = y;
		lastx = x;
		switch (ch) {
			case KEY_UP:
				if (y > 1) y--;
				break;
			case KEY_DOWN:
				if (y < LINES - 2) y++;
				break;
			case KEY_LEFT:
				if (x-1 > 1) x -= 2;
				break;
			case KEY_RIGHT:
				if (x+1 < COLS - 2) x += 2;
				break;
			case KEY_MOUSE:
				if (getmouse(&event) == OK && event.bstate & BUTTON1_PRESSED) {
					y = event.y;
					x = event.x;
				}
				break;

		}
		box(stdscr, 0, 0);
		mvprintw(0, 0, "Y: %d, X: %d", y, x);

		mvaddstr(y, x, "█");
		mvaddstr(lasty, lastx, "█");
		refresh();
	}


	endwin();
	return 0;
}
