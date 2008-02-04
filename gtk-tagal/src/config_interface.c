#include "config_interface.h"

int config_file_open(gtktagal_config_t **config, const char *dir)
{
	*config = (gtktagal_config_t *)g_malloc(sizeof(gtktagal_config_t));
	(*config)->db_str = g_string_new(dir);
	g_string_append((*config)->db_str, "/.test.db");
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

int config_file_set_dbstr(gtktagal_config_t *config, const gchar *str)
{
	g_print("set config db str to: %s", str);
	return 0;
}

