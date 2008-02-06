#include "tags_list.h"
#include <string.h>

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

int tags_list_refresh_by_path(GtkTreeModel *model, tagal_t *tagal, 
		const gchar *path)
{
	tagal_tag_iter_t *tags;
	tagal_tag_iter_new(tagal, &tags);
	if(strlen(path)) {
		tagal_data_get_tags_by_path(path, tags);
	} else {
		tagal_get_all_tags(tagal, tags);
	}
	tags_list_clr_append(model, tags);
	tagal_tag_iter_release(tags);
	return 0;
}

