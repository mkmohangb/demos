#ifndef GAPLESS_RING_BUFFER_H
#define GAPLESS_RING_BUFFER_H

#include <stdint.h>

struct ring_buffer_t {
    uint8_t *data;
    uint64_t read;
    uint64_t written;
};

int ring_buffer_init(struct ring_buffer_t *rb);
void ring_buffer_write(struct ring_buffer_t *rb, uint8_t *p, uint64_t n);
uint8_t *ring_buffer_read(struct ring_buffer_t *rb, uint64_t n);
void ring_buffer_free(struct ring_buffer_t *rb);

#endif
