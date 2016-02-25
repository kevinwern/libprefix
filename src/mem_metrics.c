#include "mem_metrics.h"

size_t memory_used_bytes = 0;

void (*__MALLOC_HOOK_VOLATILE __malloc_initialize_hook) (void) = my_init_hook;

void my_init_hook()
{
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

void *my_malloc_hook (size_t size, const void *caller)
{
    void *ptr;
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    ptr = malloc(size);
    memory_used_bytes += size; 
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
    return ptr;
}

void my_free_hook (void *ptr, const void *caller)
{
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    memory_used_bytes -= sizeof(ptr); 
    free(ptr);
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

size_t get_memory_used_bytes()
{
    return memory_used_bytes;
}
