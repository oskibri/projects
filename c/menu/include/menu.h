#ifndef MENU_H
#define MENU_H

#define OPT_NECHO		(1 << 0)
#define OPT_RAW			(1 << 1)
#define OPT_CBREAK		(1 << 2)
#define OPT_MOUSE		(1 << 3)

/*
 * @brief initialize ncurses stdscr window
 *
 * @param int	Bitmask options on what atrributes to enable
 * 				- OPT_NECHO:	Turn off echoing AKA noecho()
 * 				- OPT_RAW:		Enable raw mode AKA raw();
 * 				- OPT_CBREAK:	Enable control break AKA cbreak();
 * 				- OPT_MOUSE:	Enable mouse support AKA mousemask(ALL_MOUSE_EVENTS, NULL); mouseinterval(0);
 */
void startup(int options);
void minimize(void);
void maximize(void);

#endif // MENU_H
