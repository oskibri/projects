#include <ncurses.h>

int inside_box(WINDOW *box, MEVENT mevent) {
	int my = mevent.y, mx = mevent.x;
	int by, bx;
	int bh, bw;
	getbegyx(box, by, bx);
	getmaxyx(box, bh, bw);
	int sby = by + bh;
	int sbx = bx + bw;
	return ((my >= by && my < sby) && (mx >= bx && mx < sbx));
}

