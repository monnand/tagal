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

#ifndef MONNAND_LIBTAGAL_TAGAL_H
#define MONNAND_LIBTAGAL_TAGAL_H

#include "global.h"
#include "mempool.h"
#include "db_sqlite.h"
#include "tagal_errno.h"

struct tagal_t;
typedef struct tagal_t tagal_t;

struct tagal_data_iter_t;
typedef struct tagal_data_iter_t tagal_data_iter_t;

struct tagal_tag_iter_t;
typedef struct tagal_tag_iter_t tagal_tag_iter_t;

int tagal_new(tagal_t **tagal, db_new_f db_new, 
	const char *arg, mempool_t *pool);
int tagal_release(tagal_t *tagal);

int tagal_data_iter_new(tagal_t *tagal, tagal_data_iter_t **iter); 
int tagal_data_iter_release(tagal_data_iter_t *iter);

int tagal_tag_iter_new(tagal_t *tagal, tagal_tag_iter_t **iter); 
int tagal_tag_iter_release(tagal_tag_iter_t *iter);

int tagal_select_by_tags(tagal_t *tagal, 
		tagal_data_iter_t *data, 
		const char *tags);
int tagal_select_by_path(tagal_t *tagal, 
		tagal_data_iter_t *data, 
		const char *path);

const char *tagal_data_path(tagal_data_iter_t *data);
const char *tagal_data_name(tagal_data_iter_t *data);
const char *tagal_tag_tag(tagal_tag_iter_t *tag);

int tagal_tag_del_tag(tagal_t *tagal, const char *tag);

int tagal_data_next(tagal_data_iter_t *data);
int tagal_tag_next(tagal_tag_iter_t *tag);

int tagal_data_get_tags(tagal_data_iter_t *data, tagal_tag_iter_t *tags);
int tagal_data_get_tags_by_path(const char *path, tagal_tag_iter_t *tags);

int tagal_data_add_tag(tagal_data_iter_t *data, const char *tag);
int tagal_data_add_tag_to_path(tagal_t *tagal, const char *path, 
	const char *tag);

int tagal_data_add_tags_to_path(tagal_t *tagal, const char *path, 
	const char *tag);

int tagal_data_del_tag(tagal_data_iter_t *data, const char *tag);
int tagal_data_del_tag_by_path(tagal_t *tagal, const char *path, 
	const char *tag);

int tagal_data_del_data(tagal_data_iter_t *data);
int tagal_data_del_by_path(tagal_t *tagal, const char *path);

int tagal_add_data(tagal_t *tagal, const char *path, const char *name);
int tagal_get_all_data(tagal_t *tagal, tagal_data_iter_t *iter);
int tagal_get_all_tags(tagal_t *tagal, tagal_tag_iter_t *iter);

int tagal_data_set_name(tagal_data_iter_t *data, const char *name);
int tagal_data_set_path(tagal_data_iter_t *data, const char *path);

#endif /* MONNAND_LIBTAGAL_TAGAL_H */
