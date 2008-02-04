/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"
#include "global_var.h"
#include "files_list.h"
#include "tags_list.h"

static int gtktagal_init(const char *dir)
{
	tagal_data_iter_t *data;
	tagal_tag_iter_t *tags;
	last_accessed_dir = NULL;
	config_file_open(&config_handler, dir);

	tagal_new(&tagal_handler, libtagal_sqlite, 
		config_file_get_dbstr(config_handler), NULL);

	tagal_data_iter_new(tagal_handler, &data);
	tagal_tag_iter_new(tagal_handler, &tags);

	tagal_get_all_data(tagal_handler, data);
	tagal_get_all_tags(tagal_handler, tags);

	files_list_clr_append(
		gtk_tree_view_get_model(search_main_wnd_arg.files_tree),
		data);
	tags_list_clr_append(
		gtk_tree_view_get_model(search_main_wnd_arg.tags_tree),
		tags);

	tagal_data_iter_release(data);
	tagal_tag_iter_release(tags);
	search_main_wnd_arg.tagal = tagal_handler;
	return 0;
}

int
main(int argc, char *argv[], char *env[])
{
  GtkWidget *search_wnd;
  GtkWidget *file_properties_wnd;

  char *dir;
  int i;
  for(i = 0; NULL != env[i]; i++) {
	  if(!strncmp(env[i], "HOME", 4)) {
		  dir = strchr(env[i], '/');
	  }
  }

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  search_wnd = create_search_wnd ();
  gtk_widget_show (search_wnd);
  /*
  file_properties_wnd = create_file_properties_wnd ();
  gtk_widget_show (file_properties_wnd);
  */
  gtktagal_init(dir);

  gtk_main ();
  return 0;
}
