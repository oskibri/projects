#ifndef HELPER_H
#define HELPER_H

/**
 * @file helper.h
 * @brief Provides helper functions for ncurses
 */

/**
 * @brief Checks if a mouse event occured inside a window
 *
 * @param box The window to check
 * @param mevent The mouse event
 * @return 1 if the event occured inside the window, 0 otherwise
 */
int inside_box(WINDOW *box, MEVENT mevent);

#endif // HELPER_H
