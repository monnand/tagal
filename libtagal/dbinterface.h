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

#ifndef MONNAND_LIBTAGAL_DBINTERFACE_H
#define MONNAND_LIBTAGAL_DBINTERFACE_H

#include "mempool.h"
#include "global.h"

struct libtagal_db_t;
struct libtagal_db_result_t;
typedef struct libtagal_db_t libtagal_db_t;
typedef struct libtagal_db_result_t libtagal_db_result_t;

typedef int (*db_new_f)(libtagal_db_t *);
typedef int (*db_result_new_f)(libtagal_db_result_t *);

typedef int (*db_init_f)(void **, const char *, int);
typedef int (*db_sql_exec_f)(void *, const char *);
typedef int (*db_noresult_sql_exec_f)(void *, const char *);
typedef int (*db_release_f)(void *);

typedef int (*db_get_result_f)(void *, void **);
typedef int (*db_release_result_f)(void *);

typedef int (*db_next_row_f)(void *);
typedef int (*db_column_int_f)(void *, int );
typedef const unsigned char *(*db_column_text_f)(void *, int );

typedef const char *(*db_strerror_f)(void *);

struct libtagal_db_t {
	void *db_data; /*!< database specific data. */
	mempool_t *pool;
	db_init_f db_init;
	db_sql_exec_f db_sql_exec;
	db_noresult_sql_exec_f db_noresult_sql_exec;
	db_release_f db_release;
	db_get_result_f db_get_result;
	db_result_new_f db_result_new;
	db_strerror_f db_strerror;
};

struct libtagal_db_result_t {
	libtagal_db_t *libtagal;
	mempool_t *pool;
	void *db_result;

	db_release_result_f db_release_result;
	db_next_row_f db_next_row;
	db_column_int_f db_column_int;
	db_column_text_f db_column_text;
};

int libtagal_db_new(libtagal_db_t **tagal, db_new_f db_new, mempool_t *pool);
int libtagal_db_connect(libtagal_db_t *tagal, const char *arg, int if_create);
int libtagal_db_release(libtagal_db_t *tagal);

int libtagal_db_sql_exec(libtagal_db_t *tagal, const char *sql);
int libtagal_db_get_result(libtagal_db_t *tagal, libtagal_db_result_t **result);
int libtagal_db_exec_result(libtagal_db_t *tagal, 
		libtagal_db_result_t *result,
		const char *sql);
int libtagal_db_exec_noresult(libtagal_db_t *tagal, const char *sql);

int libtagal_db_result_new(libtagal_db_t *tagal, libtagal_db_result_t **result);
int libtagal_db_result_release(libtagal_db_result_t *result);
int libtagal_db_result_next(libtagal_db_result_t *result);
int libtagal_db_result_column_int(libtagal_db_result_t *result, int col);

const unsigned char *libtagal_db_result_column_text(
		libtagal_db_result_t *result, 
		int col);

#endif /* MONNAND_LIBTAGAL_DBINTERFACE_H */
