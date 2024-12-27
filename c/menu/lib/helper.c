#include <ncurses.h>
#include <stdbool.h>
#include "../include/menu.h"

void startup(int options) {
	initscr();
	keypad(stdscr, true);
	curs_set(0);
	if (options & OPT_NECHO) noecho();
	if (options & OPT_RAW) raw();
	if (options & OPT_CBREAK) cbreak();
	if (options & OPT_MOUSE) {
		mousemask(ALL_MOUSE_EVENTS, NULL);
		mouseinterval(0);
	}
}

void minimize(void) {
	def_prog_mode();
	endwin();
}

void maximize(void) {
	reset_prog_mode();
	refresh();
}
