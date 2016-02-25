// mem_metrics.h - sets hooks for malloc and free for memory tracking
#ifndef MEM_METRICS_H
#define MEM_METRICS_H

#include <stdio.h>
#include <malloc.h>

extern size_t memory_used_bytes;

void *(*old_malloc_hook)(size_t size, const void *caller);
void *(*old_free_hook)(void *ptr, const void *caller);

void my_init_hook();
void *my_malloc_hook (size_t size, const void *caller);
void my_free_hook(void *ptr, const void *caller);

size_t get_memory_used_bytes();
#endif
