#include "gapless_ring_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    struct ring_buffer_t rb;
    if (ring_buffer_init(&rb) != 0) {
        printf("Ring buffer initialization failed!\n");
        return 1;
    }

    // Test writing to the ring buffer
    // Initialize the ring buffer
    char *initial_message = "Initial message";
    uint64_t initial_message_len = strlen(initial_message);
    ring_buffer_write(&rb, (uint8_t*)initial_message, initial_message_len);

    // Create a 16300-byte message
    char message1[16300];
    for (int i = 0; i < 16300; i++) {
        message1[i] = 'X';
    }
    ring_buffer_write(&rb, (uint8_t*)message1, 16300);

    // Read the initial message and the 16300-byte message
    ring_buffer_read(&rb, initial_message_len);
    ring_buffer_read(&rb, 16300);

    // Create a 100-byte message
    char message2[100];
    for (int i = 0; i < 100; i++) {
        message2[i] = 'Y';
    }
    ring_buffer_write(&rb, (uint8_t*)message2, 100);

    // Read the 100-byte message and assert its content
    uint8_t *read_data = ring_buffer_read(&rb, 100);
    for (int i = 0; i < 100; i++) {
        if (read_data[i] != 'Y') {
            printf("Assertion failed at index %d: read_data[%d] = %c (0x%x), expected 'Y'\n", i, i, read_data[i]);
            assert(read_data[i] == 'Y');
        }
    }

    printf("written bytes: %lu\n", rb.written);
    printf("read bytes: %lu\n", rb.read);

    ring_buffer_free(&rb);
    printf("Ring buffer freed.\n");

    return 0;
}
