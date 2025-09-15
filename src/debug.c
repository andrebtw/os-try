#include "debug.h"
#include "vga_text.h"
#include "stdlib.h"


void debug_print(char *string, int8 newline)
{
    static int i = 6;
    static int x_pos = 0;

    if (!string)
        return ;
    VGA_print_str(string, x_pos, VGA_WIDTH - i, VGA_BLACK_COLOR, VGA_YELLOW_COLOR);
    if (!i)
        i = 6;
    if (x_pos >= VGA_WIDTH)
        x_pos = 0;
    if (newline)
    {
        x_pos = 0;
        i--;
    }
    x_pos = x_pos + strlen(string);
}
