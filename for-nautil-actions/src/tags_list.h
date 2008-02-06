/* gtk-tagal
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

#ifndef MONNAND_GTKTAGAL_TAGS_LIST_H
#define MONNAND_GTKTAGAL_TAGS_LIST_H

#include "gtktagal_global.h"

GtkTreeModel *tags_list_create();
int tags_list_clr_append(GtkTreeModel *list, tagal_tag_iter_t *iter);
int tags_list_append(GtkTreeModel *list, tagal_tag_iter_t *iter);

int tags_list_clr_append_str(GtkTreeModel *list, const gchar *tag); 
int tags_list_append_str(GtkTreeModel *list, const gchar *tag); 
int tags_list_refresh_by_path(GtkTreeModel *model, tagal_t *tagal, 
		const gchar *path);

#endif /* MONNAND_GTKTAGAL_TAGS_LIST_H */
