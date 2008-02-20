#include "config_interface.h"
#include <string.h>

int config_file_open(gtktagal_config_t **config, const char *dir)
{
	*config = (gtktagal_config_t *)g_malloc(sizeof(gtktagal_config_t));
	(*config)->db_str = g_string_new(dir);
	g_string_append((*config)->db_str, "/.tagal.db");
	return 0;
}

int config_file_close(gtktagal_config_t *config)
{
	return 0;
}

const gchar *config_file_get_dbstr(gtktagal_config_t *config)
{
	return config->db_str->str;
}

int config_file_get_open_file_argv(gtktagal_config_t *config, 
		const char *out[], int size, 
		const gchar *file_path, const gchar *file_name,
		gchar **need_free)
{
	*need_free = g_strdup(file_path);
	//*((*need_free)+strlen(file_path)-strlen(file_name)) = 0;
	out[0] = "xdg-open";
	out[1] = (*need_free);
	out[2] = NULL;
	return 0;
}

int config_file_get_open_file_dir_argv(gtktagal_config_t *config, 
		const char *out[], int size, 
		const gchar *file_path, const gchar *file_name,
		gchar **need_free)
{
	*need_free = g_strdup(file_path);
	*((*need_free)+strlen(file_path)-strlen(file_name)) = 0;
	out[0] = "xdg-open";
	out[1] = (*need_free);
	out[2] = NULL;
	return 0;
}

const char *config_file_get_open_file_cmd(gtktagal_config_t *config, 
		GString *out, const gchar *file_path, const gchar *file_name)
{
	g_string_append(out, "xdg-open \"");
	g_string_append_len(out, file_path, strlen(file_path));
	g_string_append_c(out, '"');
	return out->str;
}

int config_file_set_dbstr(gtktagal_config_t *config, const gchar *str)
{
	g_print("set config db str to: %s", str);
	return 0;
}

