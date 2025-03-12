#include "end_of_page_allocator.h"
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void print_stack_trace() {
    void *buffer[128];
    int size;

    // Capture the backtrace
    size = backtrace(buffer, 128);

    // Print raw backtrace addresses
    fprintf(stderr, "Stack trace (addresses):\n");
    backtrace_symbols_fd(buffer, size, STDERR_FILENO);

    // Use 'atos' to resolve symbols into human-readable format
    fprintf(stderr, "\nResolved stack trace:\n");
    for (int i = 0; i < size; i++) {
        char command[512];
        snprintf(command, sizeof(command), "atos -arch arm64 -o %s %p", getprogname(), buffer[i]);
        system(command);
    }
}


void handler(int sig) {
    void *array[10];
    size_t size;

    print_stack_trace();
    exit(1);
}


int main() {
    uint64_t size = 100;
    //sleep(20);
    volatile void *ptr = eop_malloc(size);

    //signal(SIGSEGV, handler);

    long pagesize = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld\n", pagesize);

    if (ptr == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }

    printf("Allocated memory at: %p\n", (void*)ptr);

    // Write some data to the allocated memory
    volatile char *data = (volatile char *)ptr;
    for (int i = 0; i < size; i++) {
        data[i] = 'A';
    }

    printf("Data written to memory.\n");


    // scenario 1
    // printf("Attempting to write beyond memory...\n");
    // data[100] = 'B'; // This should cause a crash
    printf("Memory freed.\n"); // This line should not be reached

    eop_free((void*)ptr, size);

    // scenario 2
    //printf("Attempting to write after freeing memory...\n");
    //data[0] = 'B'; // This should cause a crash

    return 0;
}
;
