/* 0xB8000 is the start of the memory address for VGA text
80x25 resolution, each character is 16 bit
8 higher bit for the color and 8 lower bits for the character
background | foreground | character
*/

void VGA_clear_screen(void)
{
    unsigned char *video_buffer = (unsigned char *)0xB8000;

    for (unsigned short i = 0; i < 2000; i++)
    {
        video_buffer[0] = ' ';
        video_buffer[1] = 0x00;
        video_buffer = video_buffer + 2;
    }
}
