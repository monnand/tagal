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

#ifndef MONNAND_GTK_TAGAL_GLOBALVAR_H
#define MONNAND_GTK_TAGAL_GLOBALVAR_H

#include "gtktagal_global.h"
#include "config_interface.h"

typedef struct search_main_wnd_arg_t {
	GtkTreeView *files_tree;
	GtkTreeView *tags_tree;
	GtkEntry *input_text_entry;
	GtkLabel *files_tree_label;
	GtkLabel *tags_tree_label;
	tagal_t *tagal;
} search_main_wnd_arg_t;

tagal_t *tagal_handler;
gtktagal_config_t *config_handler;
search_main_wnd_arg_t search_main_wnd_arg;

#endif /* MONNAND_GTK_TAGAL_GLOBALVAR_H */
