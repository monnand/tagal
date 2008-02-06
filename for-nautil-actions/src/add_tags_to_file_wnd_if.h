#ifndef MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_IF_H
#define MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_IF_H

#include <gtk/gtk.h>
#include "tagal.h"

enum {
	ADD_TAGS_TO_FILE_WND_NEED_FREE = 0,
	ADD_TAGS_TO_FILE_PATH_NEED_FREE,
	ADD_TAGS_TO_FILE_PATH_NR
};

typedef struct add_tags_to_file_wnd_arg_t {
	tagal_t *tagal;
	const gchar *path;
	const gchar *base_dir;
	GtkWidget *wnd;
	GtkTreeView *all_tags_tree;
	GtkTreeView *cur_file_tags_tree;
	GtkEntry *input_entry;
	unsigned int free_flags;
	int exit_on_delete;
} add_tags_to_file_wnd_arg_t;

GtkWidget* create_add_tags_to_file_wnd (add_tags_to_file_wnd_arg_t *arg);

#endif /* MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_IF_H */
