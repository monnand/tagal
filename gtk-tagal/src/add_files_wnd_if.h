#ifndef MONNAND_GTKTAGAL_ADD_FILES_WND_IF_H
#define MONNAND_GTKTAGAL_ADD_FILES_WND_IF_H

#include <gtk/gtk.h>
#include "global_var.h"

typedef struct add_files_wnd_arg_t {
	GtkWidget *wnd;
	GtkEntry *entry;
	tagal_t *tagal;
} add_files_wnd_arg_t;

gchar *last_accessed_dir;

GtkWidget* create_add_files_wnd (add_files_wnd_arg_t *arg);

#endif /* MONNAND_GTKTAGAL_ADD_FILES_WND_IF_H */

