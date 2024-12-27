#include "../include/menu.h"
#include <ncurses.h>

int main(void) {
	startup(OPT_CBREAK | OPT_MOUSE | OPT_NECHO);


	WINDOW *win = newwin(1, 1, 20, 40);
	box(win, 0, 0);
	refresh();
	wrefresh(win);

	getch();
	endwin();
	return 0;
}
