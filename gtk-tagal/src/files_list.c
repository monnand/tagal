#include "files_list.h"

enum {
	FILES_LIST_NAME_COL = 0,
	FILES_LIST_PATH_COL,
	FILES_LIST_NR_COL
};

GtkTreeModel *files_list_create()
{
	GtkListStore *model;
	model = gtk_list_store_new (FILES_LIST_NR_COL, G_TYPE_STRING, G_TYPE_STRING);
	return GTK_TREE_MODEL(model);
}

int files_list_clr_append_str(GtkTreeModel *list, const gchar *name, 
		const gchar *path)
{
	GtkTreeIter iter;
	gtk_list_store_clear(GTK_LIST_STORE(list));
	gtk_list_store_append(GTK_LIST_STORE(list), &iter);
	gtk_list_store_set(GTK_LIST_STORE(list), &iter, FILES_LIST_NAME_COL,
			name, FILES_LIST_PATH_COL, path, -1);
	return 0;
}


int files_list_append_str(GtkTreeModel *list, const gchar *name, 
		const gchar *path)
{
	GtkTreeIter iter;
	gtk_list_store_append(GTK_LIST_STORE(list), &iter);
	gtk_list_store_set(GTK_LIST_STORE(list), &iter, FILES_LIST_NAME_COL,
			name, FILES_LIST_PATH_COL, path, -1);
	return 0;
}

int files_list_clr_append(GtkTreeModel *list, tagal_data_iter_t *iter)
{
	gtk_list_store_clear(GTK_LIST_STORE(list));
	while(DB_MORE_DATA == tagal_data_next(iter)) {
		files_list_append_str(list, tagal_data_name(iter),
				tagal_data_path(iter));
	}
	return 0;
}

int files_list_append(GtkTreeModel *list, tagal_data_iter_t *iter)
{
	while(DB_MORE_DATA == tagal_data_next(iter)) {
		files_list_append_str(list, tagal_data_name(iter),
				tagal_data_path(iter));
	}
	return 0;
}
