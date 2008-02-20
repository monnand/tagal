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

#ifndef MONNAND_GTKTAGAL_CONFIG_INTERFACE_H
#define MONNAND_GTKTAGAL_CONFIG_INTERFACE_H

#include "gtktagal_global.h"

typedef struct gtktagal_config_t {
	GString *config_file;
	GString *db_str;
	GString *open_file_cmd;
} gtktagal_config_t;

int config_file_open(gtktagal_config_t **config, const char *dir);
int config_file_close(gtktagal_config_t *config);
const gchar *config_file_get_dbstr(gtktagal_config_t *config);
int config_file_get_open_file_argv(gtktagal_config_t *config, 
		const char *out[], int size, 
		const gchar *file_path, const gchar *file_name,
		gchar **need_free);
int config_file_get_open_file_dir_argv(gtktagal_config_t *config, 
		const char *out[], int size, 
		const gchar *file_path, const gchar *file_name,
		gchar **need_free);
/*
const char *config_file_get_open_file_cmd(gtktagal_config_t *config, 
		GString *out, const gchar *file_path, const gchar *file_name);
*/
int config_file_set_dbstr(gtktagal_config_t *config, const gchar *str);

#endif /* MONNAND_GTKTAGAL_CONFIG_INTERFACE_H */

