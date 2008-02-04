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

#ifndef MONNAND_LIBTAGAL_SQLITE_IMPLEMENTATION_H
#define MONNAND_LIBTAGAL_SQLITE_IMPLEMENTATION_H

#include "dbinterface.h"
#include "sqlite3.h"

typedef struct tagal_db_sqlite_t {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *filename;
} tagal_db_sqlite_t;

typedef struct tagal_db_sqlite_result_t {
	sqlite3_stmt *stmt;
	int nr_col;
} tagal_db_sqlite_result_t;

int tagal_db_sqlite_init(void **lite, const char *arg);
int tagal_db_sqlite_sql_exec(void *lite, const char *sql);
int tagal_db_sqlite_result_new(libtagal_db_result_t *result);
int tagal_db_sqlite_release(void *lite);

int tagal_db_sqlite_get_result(void *lite, void **result);

int tagal_db_sqlite_release_result(void *result);
int tagal_db_sqlite_next_row(void *result);
int tagal_db_sqlite_column_int(void *result, int col);
const unsigned char *tagal_db_sqlite_column_text(void *result, int col);

const char *tagal_db_sqlite_strerror(void *lite);

#endif /* MONNAND_LIBTAGAL_SQLITE_IMPLEMENTATION_H */

