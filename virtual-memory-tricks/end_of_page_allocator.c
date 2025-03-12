#include "end_of_page_allocator.h"
#include <stdlib.h> // For NULL
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

#define PAGE_SIZE 16384 // run sysconf(_SC_PAGESIZE);

void *eop_malloc(uint64_t size) {
    uint64_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
    void *base;

#ifdef _WIN32
    base = VirtualAlloc(NULL, pages * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (base == NULL) {
        return NULL;
    }
#else
    base = mmap(NULL, pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (base == MAP_FAILED) {
        return NULL;
    }
#endif

    uint64_t offset = pages * PAGE_SIZE - size;
    return (void *)((char *)base + offset);
}

void eop_free(void *ptr, uint64_t size) {
    if (ptr == NULL) {
        return;
    }

    uint64_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
    void *base = (void *)((char *)ptr - (pages * PAGE_SIZE - size));

#ifdef _WIN32
    VirtualFree(base, 0, MEM_RELEASE);
#else
    munmap(base, pages * PAGE_SIZE);
#endif
}
