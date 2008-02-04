/* libtagal
 * A library used to tag file 
 *
 * Copyright (C) 2007 Deng Nan <monnand@gmail.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*!\file mempool.h
 * \brief An implementation of memory pool
 */
#ifndef MONNAND_LIBTAGAL_MEMPOOL_H
#define MONNAND_LIBTAGAL_MEMPOOL_H

/* TODO Actually, it haven't implemented. Just an interface. */
#include <stdio.h>
#include <stdlib.h>

typedef struct mempool_t {
	char foo_bar;
} mempool_t;

void *mempool_allocate(mempool_t *pool, size_t n);
void *mempool_realloc(mempool_t *pool, void *ptr, size_t n);
void mempool_free(mempool_t *pool, void *ptr);
char *mempool_strdup(mempool_t *pool, const char *str);

#endif

