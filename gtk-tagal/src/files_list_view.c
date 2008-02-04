#include "files_list_view.h"
#include <string.h>

enum {
	FILES_LIST_NAME_COL = 0,
	FILES_LIST_PATH_COL,
	FILES_LIST_NR_COL
};

int set_files_list_view(GtkTreeView *view)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeModel *list_model;
	GtkTreeSelection *selection;

	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title (column, "Name");
	
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_column_pack_start (column, renderer, TRUE);
	gtk_tree_view_column_set_attributes (column, renderer,
					     "text", 0, NULL);
	
	gtk_tree_view_append_column (view, column);	

	/********************************************************/
	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title (column, "Path");
	
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_column_pack_start (column, renderer, TRUE);
	gtk_tree_view_column_set_attributes (column, renderer,
					     "text", 1, NULL);
	
	gtk_tree_view_append_column (view, column);

	list_model = files_list_create();
	gtk_tree_view_set_model (view, list_model);

	selection = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);

	return 0;
}

int refresh_files_view_with_tags(search_main_wnd_arg_t *arg, 
		const gchar *tags, const gchar *new_label)
{
	tagal_data_iter_t *data;
	tagal_t *tagal = arg->tagal;

	GtkTreeModel *file_model = gtk_tree_view_get_model(arg->files_tree);

	tagal_data_iter_new(tagal, &data);
	if(strlen(tags)) {
		tagal_select_by_tags(tagal, data, tags);
		gtk_label_set_text(arg->files_tree_label, new_label);
	} else {
		tagal_get_all_data(tagal, data);
		gtk_label_set_text(arg->files_tree_label, "All Files");
	}
	files_list_clr_append(file_model, data);

	tagal_data_iter_release(data);
	return 0;
}

