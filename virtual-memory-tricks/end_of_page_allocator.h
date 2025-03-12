#ifndef END_OF_PAGE_ALLOCATOR_H
#define END_OF_PAGE_ALLOCATOR_H

#include <stdint.h>

void *eop_malloc(uint64_t size);
void eop_free(void *ptr, uint64_t size);

#endif
