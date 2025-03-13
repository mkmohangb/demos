#include "gapless_ring_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define PAGE_SIZE 16384
#define BUFFER_SIZE PAGE_SIZE // Example buffer size, must be a multiple of PAGE_SIZE


int ring_buffer_init(struct ring_buffer_t *rb) {
#ifdef _WIN32
    rb->data = VirtualAlloc(NULL, 2 * BUFFER_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (rb->data == NULL) {
        return -1;
    }

    // Create a file mapping to share the same physical memory
    HANDLE hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFER_SIZE, NULL);
    if (hFileMapping == NULL) {
        VirtualFree(rb->data, 0, MEM_RELEASE);
        return -1;
    }

    // Map the first half of the buffer to the file mapping
    uint8_t *first_half = (uint8_t*)MapViewOfFileEx(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE, rb->data);
    if (first_half != rb->data) {
        VirtualFree(rb->data, 0, MEM_RELEASE);
        CloseHandle(hFileMapping);
        return -1;
    }

    // Map the second half of the buffer to the same file mapping, pointing to the same physical memory
    uint8_t *second_half = (uint8_t*)MapViewOfFileEx(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE, rb->data + BUFFER_SIZE);
    if (second_half != rb->data + BUFFER_SIZE) {
        UnmapViewOfFile(first_half);
        VirtualFree(rb->data, 0, MEM_RELEASE);
        CloseHandle(hFileMapping);
        return -1;
    }

    CloseHandle(hFileMapping);

#else
    // Allocate memory for two copies of the buffer
    rb->data = mmap(NULL, 2 * BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (rb->data == MAP_FAILED) {
        return -1;
    }

    // mmap the same physical memory to the second half of the buffer
    void *result = mmap(rb->data + BUFFER_SIZE, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (result == MAP_FAILED) {
        munmap(rb->data, 2 * BUFFER_SIZE);
        return -1;
    }
#endif

    rb->read = 0;
    rb->written = 0;
    return 0;
}

void ring_buffer_write(struct ring_buffer_t *rb, uint8_t *p, uint64_t n) {
    memcpy(rb->data + (rb->written % BUFFER_SIZE), p, n);
    rb->written += n;
}

uint8_t *ring_buffer_read(struct ring_buffer_t *rb, uint64_t n) {
    uint8_t *p = rb->data + (rb->read % BUFFER_SIZE);
    rb->read += n;
    return p;
}

void ring_buffer_free(struct ring_buffer_t *rb) {
#ifdef _WIN32
    UnmapViewOfFile(rb->data);
    VirtualFree(rb->data, 0, MEM_RELEASE);
#else
    munmap(rb->data, 2 * BUFFER_SIZE);
#endif
}
