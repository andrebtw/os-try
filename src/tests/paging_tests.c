#include "../../include/tests/paging_tests.h"

void paging_tests(void)
{
    volatile uint32_t *p = (uint32_t *)0x00401000;
    uint32_t x = *p;
    (void)x;
}
