void _start()
{
    char* video_memory = (char*) 0xB8000; // Video memory address
    *video_memory = 'T';
    while (1);
    int i = 0;
}
