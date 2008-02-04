#include "tags_list_view.h"
#include <string.h>

enum {
	TAGS_LIST_TAG_COL = 0,
	TAGS_LIST_NR_COL
};

int set_tags_list_view(GtkTreeView *view)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeModel *list_model;
	GtkTreeSelection *selection;

	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title (column, "Tag");
	
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_column_pack_start (column, renderer, TRUE);
	gtk_tree_view_column_set_attributes (column, renderer,
					     "text", 0, NULL);
	gtk_tree_view_append_column (view, column);	

	list_model = tags_list_create();
	gtk_tree_view_set_model (view, list_model);

	selection = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);

	return 0;
}

int refresh_tags_tree_by_path(GtkTreeModel *tag_model, tagal_t *tagal, 
		const gchar *path) {
	tagal_tag_iter_t *tags;
	tagal_tag_iter_new(tagal, &tags);

	if(strlen(path)) {
		tagal_data_get_tags_by_path(path, tags);
	} else {
		tagal_get_all_tags(tagal, tags);
	}
	tags_list_clr_append(tag_model, tags);
	tagal_tag_iter_release(tags);
	return 0;
}

int refresh_tags_view_with_path(search_main_wnd_arg_t *arg, 
		const gchar *path, const gchar *new_label)
{
	tagal_tag_iter_t *tags;
	tagal_t *tagal = arg->tagal;
	tagal_tag_iter_new(tagal, &tags);
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->tags_tree);

	if(strlen(path) && strcmp(path, "All Tags")) {
		tagal_data_get_tags_by_path(path, tags);
		gtk_label_set_text(arg->tags_tree_label, new_label);
	} else {
		tagal_get_all_tags(tagal, tags);
		gtk_label_set_text(arg->tags_tree_label, "All Tags");
	}
	tags_list_clr_append(tag_model, tags);
	tagal_tag_iter_release(tags);
	return 0;
}

