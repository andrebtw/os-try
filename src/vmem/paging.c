#include "../../include/paging.h"
#include <stddef.h>

uint32 page_directory_entry[1024] __attribute__((aligned(4096)));
uint32 page_table_entry[1024] __attribute__((aligned(4096)));

void fill_pde(void)
{
    page_directory_entry[0] = P_FLAG | RW_FLAG;
    for (size_t i = 1; i < 1024; i++)
    {
        page_directory_entry[i] = 0x0;
    }
}

void fill_pte(void)
{
    
}