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

#ifndef MONNAND_GTKTAGAL_FILES_LIST_VIEW_H
#define MONNAND_GTKTAGAL_FILES_LIST_VIEW_H

#include "files_list.h"
#include "global_var.h"

int set_files_list_view(GtkTreeView *view);
int refresh_files_view_with_tags(search_main_wnd_arg_t *arg, 
		const gchar *tags, const gchar *new_label);

#endif /* MONNAND_GTKTAGAL_FILES_LIST_VIEW_H */

