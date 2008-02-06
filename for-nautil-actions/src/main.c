/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "interface.h"
#include "support.h"
#include "global_var.h"

static int gtktagal_init(const char *dir)
{
	config_file_open(&config_handler, dir);

	tagal_new(&tagal_handler, libtagal_sqlite, 
		config_file_get_dbstr(config_handler), NULL);
	return 0;
}

int
main(int argc, char *argv[], char *env[])
{
  GtkWidget *wnd;
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

  gtktagal_init(dir);

  add_tags_to_file_wnd_arg_t one_file_arg;
  add_tags_to_multifiles_wnd_arg_t multifiles_arg;
  memset(&one_file_arg, 0, sizeof(add_tags_to_file_wnd_arg_t));
  if(argc < 3) {
	  fprintf(stderr, "useage: %s [base dir] [file path]\n", argv[0]);
	  return -1;
  }
  if(3 == argc) {
	one_file_arg.path = (argv[2]);
	one_file_arg.base_dir = (argv[1]);
  	one_file_arg.tagal = tagal_handler;
	one_file_arg.exit_on_delete = 1;
  	wnd = create_add_tags_to_file_wnd (&one_file_arg);
  } else {
	multifiles_arg.base_dir = argv[1] ;
	multifiles_arg.path = argv + 2;
  	multifiles_arg.tagal = tagal_handler;
	multifiles_arg.exit_on_delete = 1;
	multifiles_arg.nr_path = argc - 1;
	wnd = create_add_tags_to_multifiles_wnd(&multifiles_arg);
  }

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  gtk_widget_show (wnd);

  gtk_main ();
  return 0;
}

