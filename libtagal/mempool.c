#include "mempool.h"
#include <string.h>

void *mempool_allocate(mempool_t *pool, size_t n)
{
	return malloc(n);
}

void *mempool_realloc(mempool_t *pool, void *ptr, size_t n)
{
	return realloc(ptr, n);
}

void mempool_free(mempool_t *pool, void *ptr)
{
	free(ptr);
}

char *mempool_strdup(mempool_t *pool, const char *str)
{
	return strdup(str);
}
