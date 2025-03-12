
####  simple end-of-page allocator based on the idea from [here](https://ruby0x1.github.io/machinery_blog_archive/post/virtual-memory-tricks/index.html)
  - two scenarios which can be immediately detected by this allocator
    1. Writing beyond the allocated memory for an object
    2. Writing to memory that has been freed
