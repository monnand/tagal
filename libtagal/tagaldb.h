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

#ifndef MONNAND_LIBTAGAL_TAGALDB_H
#define MONNAND_LIBTAGAL_TAGALDB_H

#include "dbinterface.h"

int tagaldb_select_by_tags(libtagal_db_t *db, 
		libtagal_db_result_t *result,
		const char *tags);
int tagaldb_select_by_path(libtagal_db_t *db,
		libtagal_db_result_t *result,
		const char *path);

int tagaldb_get_fid(libtagal_db_result_t *result);
const char *tagaldb_get_path(libtagal_db_result_t *result);
const char *tagaldb_get_name(libtagal_db_result_t *result);

int tagaldb_get_tags_by_fid(libtagal_db_t *db, 
		libtagal_db_result_t *result, const int id);
int tagaldb_get_tags_by_path(libtagal_db_t *db, 
		libtagal_db_result_t *result, const char *path);

int tagaldb_get_tid(libtagal_db_result_t *result);
const char *tagaldb_get_tag(libtagal_db_result_t *result);

int tagaldb_add_tag_to_fid(libtagal_db_t *db, const int id, const char *tag);
int tagaldb_add_tag_to_path(libtagal_db_t *db, 
		const char *path, 
		const char *tag);

int tagaldb_del_tag_to_fid(libtagal_db_t *db, const int fid, const char *tag);
int tagaldb_del_tag_to_path(libtagal_db_t *db, 
		const char *path, 
		const char *tag);

int tagaldb_del_tag(libtagal_db_t *db, const char *tag);

int tagaldb_add_file(libtagal_db_t *db, const char *path, const char *name);
int tagaldb_del_file_by_fid(libtagal_db_t *db, const int id);
int tagaldb_del_file_by_path(libtagal_db_t *db, const char *path);

int tagaldb_rename(libtagal_db_t *db, const int id, const char *name);
int tagaldb_repath(libtagal_db_t *db, const int id, const char *path);

int tagaldb_get_all_tags(libtagal_db_t *db, libtagal_db_result_t *result);
int tagaldb_get_all_files(libtagal_db_t *db, libtagal_db_result_t *result);

#endif /* MONNAND_LIBTAGAL_TAGALDB_H */

