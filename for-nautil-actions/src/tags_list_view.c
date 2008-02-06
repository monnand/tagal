#include "tags_list_view.h"
#include <string.h>

enum {
	TAGS_LIST_TAG_COL = 0,
	TAGS_LIST_NR_COL
};

int tags_list_view_set(GtkTreeView *view, const gchar *col_name)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeModel *list_model;
	GtkTreeSelection *selection;

	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title (column, col_name);
	
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


