#ifndef MONNAND_TAGALADDTAGS_ADD_TAGS_TO_MULTIFILES_WND_IF_H
#define MONNAND_TAGALADDTAGS_ADD_TAGS_TO_MULTIFILES_WND_IF_H

#include <gtk/gtk.h>
#include "tagal.h"

typedef struct add_tags_to_multifiles_wnd_arg_t {
	tagal_t *tagal;
	GtkWidget *wnd;
	const gchar *base_dir;
	GtkTreeView *all_tags_tree;
	GtkEntry *input_entry;
	int exit_on_delete;
	char **path;
	int nr_path;
} add_tags_to_multifiles_wnd_arg_t;

GtkWidget* create_add_tags_to_multifiles_wnd (
		add_tags_to_multifiles_wnd_arg_t *arg);

#endif /* MONNAND_TAGALADDTAGS_ADD_TAGS_TO_MULTIFILES_WND_IF_H */
