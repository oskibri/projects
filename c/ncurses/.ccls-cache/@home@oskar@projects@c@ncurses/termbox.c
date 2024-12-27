#include <termbox.h>

int main() {
    if (tb_init() != 0) {
        return -1;
    }

    // Set a specific cell at (10, 5) with 'A' character
    tb_change_cell(10, 5, 'A', TB_WHITE, TB_DEFAULT);

    // Draw a box manually
    int box_x = 15, box_y = 10, box_width = 20, box_height = 5;
    for (int x = box_x; x < box_x + box_width; ++x) {
        tb_change_cell(x, box_y, '-', TB_WHITE, TB_DEFAULT); // Top
        tb_change_cell(x, box_y + box_height, '-', TB_WHITE, TB_DEFAULT); // Bottom
    }
    for (int y = box_y; y <= box_y + box_height; ++y) {
        tb_change_cell(box_x, y, '|', TB_WHITE, TB_DEFAULT); // Left
        tb_change_cell(box_x + box_width - 1, y, '|', TB_WHITE, TB_DEFAULT); // Right
    }

    tb_present(); // Refresh to display changes
    tb_poll_event(NULL); // Wait for any key press

    tb_shutdown();
    return 0;
}

