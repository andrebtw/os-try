#include "../../include/paging.h"

uint32 page_directory_entry[1024] __attribute__((aligned(4096)));

uint32 page_table_entry0[1024] __attribute__((aligned(4096)));
uint32 page_table_entry1[1024] __attribute__((aligned(4096)));
uint32 page_table_entry2[1024] __attribute__((aligned(4096)));

static void fill_pte(void)
{
    // Page table entry 0, 1 and 2
    for (size_t i = 0; i < 1024; i++)
    {
        page_table_entry0[i] = i * 4096 | P_FLAG | RW_FLAG;
    }
}

/* Filling each page directory with only zeros &
setting page table entry address + flags to each pde */
static void fill_pde(void)
{
    for (size_t i = 0; i < 1024; i++)
    {
        page_directory_entry[i] = 0x0000;
    }
    page_directory_entry[0] = (uint32)page_table_entry0 | P_FLAG | RW_FLAG;
}

void paging_init()
{
    fill_pte();
    fill_pde();

    load_pde(page_directory_entry);
    enable_paging();
}
