#include <ncurses.h>
#include <unistd.h> // For sleep()

int main() {
    int height = 5, width = 20;
    int start_row = 5, start_col = 5;

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);

    // Create a window
    WINDOW *win = newwin(height, width, start_row, start_col);
    box(win, 0, 0);
    mvwprintw(win, 2, 2, "Moving Window");
    wrefresh(win);

    // Move the window around
    for (int i = 0; i < 10; i++) {
        // Erase the window from its current position
        werase(win);
        wrefresh(win);

        // Move the window down and to the right
        start_row += 1;
        start_col += 2;

        mvwin(win, start_row, start_col);

        // Redraw the window at its new position
        box(win, 0, 0);
        mvwprintw(win, 2, 2, "Moving Window");
        wrefresh(win);

        // Pause for a moment
        sleep(1);
    }

    // Wait for user input
    getch();

    // End ncurses mode
    delwin(win);
    endwin();

    return 0;
}
