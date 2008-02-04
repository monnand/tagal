#include "tags_list.h"

enum {
	TAGS_LIST_TAG_COL = 0,
	TAGS_LIST_NR_COL
};

GtkTreeModel *tags_list_create()
{
	GtkListStore *model;
	model = gtk_list_store_new (TAGS_LIST_NR_COL, G_TYPE_STRING);
	return GTK_TREE_MODEL(model);
}

int tags_list_clr_append_str(GtkTreeModel *list, const gchar *tag)
{
	GtkTreeIter iter;
	gtk_list_store_clear(GTK_LIST_STORE(list));
	gtk_list_store_append(GTK_LIST_STORE(list), &iter);
	gtk_list_store_set(GTK_LIST_STORE(list), &iter, 
			TAGS_LIST_TAG_COL, tag, -1);
	return 0;
}

int tags_list_append_str(GtkTreeModel *list, const gchar *tag)
{
	GtkTreeIter iter;
	gtk_list_store_append(GTK_LIST_STORE(list), &iter);
	gtk_list_store_set(GTK_LIST_STORE(list), &iter, 
			TAGS_LIST_TAG_COL, tag, -1);
	return 0;
}

int tags_list_clr_append(GtkTreeModel *list, tagal_tag_iter_t *iter)
{
	gtk_list_store_clear(GTK_LIST_STORE(list));
	while(DB_MORE_DATA == tagal_tag_next(iter)) {
		tags_list_append_str(list, tagal_tag_tag(iter));
	}
	return 0;
}

int tags_list_append(GtkTreeModel *list, tagal_tag_iter_t *iter)
{
	while(DB_MORE_DATA == tagal_tag_next(iter)) {
		tags_list_append_str(list, tagal_tag_tag(iter));
	}
	return 0;
}

