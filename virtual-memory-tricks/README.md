
#### Based on the ideas from [here](https://ruby0x1.github.io/machinery_blog_archive/post/virtual-memory-tricks/index.html)
  - simple end-of-page allocator
    - two scenarios which can be immediately detected by this allocator
      1. Writing beyond the allocated memory for an object
      2. Writing to memory that has been freed
    - ```gcc end_of_page_allocator.c test.c -o test```
      
  - gapless ring buffer
    - eliminates the need for wraparound logic in buffer write and read.
    - ```gcc gapless_ring_buffer.c test_ring_buffer.c -o test_ring_buffer```
