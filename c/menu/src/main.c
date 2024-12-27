#include "../include/menu.h"
#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct menu_item{
	char *text;
	int y, x;
	ssize_t h, w;
} menu_item;

menu_item* cmenu_item(uint16_t y, uint16_t x, ssize_t heigth, ssize_t width, char *text) {
	menu_item *new = malloc(sizeof(menu_item));
	if (!new) {
		perror("Failed to create memory for menu item");
		exit(EXIT_FAILURE);
	}
	new->y = y;
	new->x = x;
	new->h = heigth;
	new->w = width;
	new->text = text;
	return new;
}

int main(void) {
	startup(OPT_CBREAK | OPT_MOUSE | OPT_NECHO);

	uint8_t y, x;
	getyx(stdscr, y, x);

	menu_item *item1 = cmenu_item(5, 5, 5, 5, "hello");
	WINDOW *item1_win = newwin(item1->y, item1->x, item1->h, item1->w);
	box(item1_win, 0, 0);
	wprintw(item1_win, "Hello");
	refresh();
	wrefresh(item1_win);

	int menu_size = 4;
	int attr_on = 0;

	int ch;
	while ((ch = getch()) != 'q') {
		mvchgat(y, x, -1, A_NORMAL, 0, NULL);
		switch (ch) {
			case KEY_UP:
				y = (y - 1 + menu_size) % menu_size;
				mvchgat(y, x, -1, A_REVERSE, 0, NULL);
				break;
			case 9:
			case KEY_DOWN:
				y = (y + 1) % menu_size;
				mvchgat(y, x, -1, A_REVERSE, 0, NULL);
				break;
			case 'a':
				if (attr_on) {
					wattrset(item1_win, A_NORMAL);
					attr_on = 0;
				} else {
					wattrset(item1_win, A_REVERSE);
					attr_on = 1;
				}
				box(item1_win, 0, 0);
				mvwprintw(item1_win, 1, 1, "hello");
				break;
		}
		refresh();
		wrefresh(item1_win);
	}

	// getch();
	endwin();
	return 0;
}
