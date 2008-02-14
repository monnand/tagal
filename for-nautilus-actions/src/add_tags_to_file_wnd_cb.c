#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "format_search_str.h"
#include <stdlib.h>
#include <string.h>

gboolean
on_add_tags_to_file_wnd_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	if(arg->exit_on_delete)
		exit(0);
	return FALSE;
}


void
on_add_tags_to_file_confirm_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	tagal_t *tagal = arg->tagal;
	GtkTreeSelection *tags_selection = 
		gtk_tree_view_get_selection(arg->all_tags_tree);
	GList *all_selected_tags = gtk_tree_selection_get_selected_rows(
			tags_selection, NULL);
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->all_tags_tree);
	const gchar *file_path = arg->path;
	const gchar *base_dir = arg->base_dir;

	GtkTreeIter tree_iter;
	GList *tags_iter = NULL;
	GtkTreePath *tag = NULL;
	gchar *tag_tag = NULL;
	GString *ftags;

	tagal_add_data(tagal, file_path, file_path + strlen(base_dir) + 1);

	for(tags_iter = g_list_first(all_selected_tags); NULL != tags_iter;
		tags_iter = g_list_next(tags_iter)) {
		tag = (GtkTreePath *)(tags_iter->data);
		gtk_tree_model_get_iter(tag_model, &tree_iter, tag);
		gtk_tree_model_get(tag_model, &tree_iter, 0, &tag_tag, -1);

		tagal_data_add_tag_to_path(tagal, file_path, tag_tag);
		//g_print("add %s to %s\n", tag_tag, file_path);
		g_free(tag_tag);
		gtk_tree_path_free(tag);
	}
	g_list_free (all_selected_tags);

	base_dir = gtk_entry_get_text(arg->input_entry);
	for(;strchr(" \t\n\r", *base_dir) && 0 != *base_dir; base_dir++);
	if(*base_dir) {
		ftags = format_search_str(base_dir);
		tagal_data_add_tags_to_path(tagal, file_path, ftags->str);
		g_string_free(ftags, TRUE);
	}
	gtk_widget_destroy(arg->wnd);
	if(arg->exit_on_delete)
		exit(0);
}


void
on_add_tags_to_file_cancel_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	gtk_widget_destroy(arg->wnd);
	if(arg->exit_on_delete)
		exit(0);
}


gboolean
on_cur_file_tags_tree_key_release_event
                                        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	GtkTreeSelection *tags_selection;
	GList *all_selected_tags;
	GList *tags_iter;
	GtkTreePath *tree_path= NULL;
	gchar *tag = NULL;
	tagal_t *tagal = arg->tagal;
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->cur_file_tags_tree);
	GtkTreeIter tree_iter;
	GdkAtom atom = gdk_atom_intern("CLIPBOARD", TRUE);
	GtkClipboard *b = gtk_clipboard_get(atom);
	GString *all_tags;

	switch(event->keyval) {
	case GDK_c:
		if(!(event->state | GDK_CONTROL_MASK))
	       		break;
		all_tags = g_string_sized_new(1024);

		tags_selection = 
			gtk_tree_view_get_selection(arg->cur_file_tags_tree);
		all_selected_tags = 
			gtk_tree_selection_get_selected_rows(
				tags_selection, NULL);
		for(tags_iter = g_list_first(all_selected_tags);
			NULL != tags_iter; 
			tags_iter = g_list_next(tags_iter)) {
			tree_path = (GtkTreePath *)(tags_iter->data);
			gtk_tree_model_get_iter(tag_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(tag_model, &tree_iter, 0,
				&tag, -1);

			g_string_append(all_tags, tag);
			g_string_append_c(all_tags, '\n');

			gtk_tree_path_free(tree_path);
			g_free(tag);
		}
		gtk_clipboard_set_text(b, all_tags->str, -1);
		g_string_free(all_tags, TRUE);
		g_list_free (all_selected_tags);
		break;

	case GDK_F5:
		tags_list_refresh_by_path(tag_model, tagal, arg->path);
		break;
	case GDK_Delete:
		tags_selection = 
			gtk_tree_view_get_selection(arg->cur_file_tags_tree);
		all_selected_tags = 
			gtk_tree_selection_get_selected_rows(
				tags_selection, NULL);
		for(tags_iter = g_list_first(all_selected_tags);
			NULL != tags_iter; 
			tags_iter = g_list_next(tags_iter)) {
			tree_path = (GtkTreePath *)(tags_iter->data);
			gtk_tree_model_get_iter(tag_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(tag_model, &tree_iter, 0,
				&tag, -1);
			tagal_data_del_tag_by_path(tagal, arg->path, tag);
			gtk_tree_model_row_deleted(tag_model, tree_path);
			gtk_tree_path_free(tree_path);
			g_free(tag);
		}
		g_list_free (all_selected_tags);
		tags_list_refresh_by_path(tag_model, tagal, arg->path);
		break;
	default:
		break;
	}

	return FALSE;
}


void
on_all_tags_tree_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


gboolean
on_all_tags_tree_key_release_event     (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	GtkTreeSelection *tags_selection;
	GList *all_selected_tags;
	GList *tags_iter;
	GtkTreePath *tree_path= NULL;
	gchar *tag = NULL;
	tagal_t *tagal = arg->tagal;
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->all_tags_tree);
	GtkTreeIter tree_iter;
	GdkAtom atom = gdk_atom_intern("CLIPBOARD", TRUE);
	GtkClipboard *b = gtk_clipboard_get(atom);
	GString *all_tags;

	switch(event->keyval) {
	case GDK_c:
		if(!(event->state | GDK_CONTROL_MASK))
	       		break;
		all_tags = g_string_sized_new(1024);

		tags_selection = 
			gtk_tree_view_get_selection(arg->all_tags_tree);
		all_selected_tags = 
			gtk_tree_selection_get_selected_rows(
				tags_selection, NULL);
		for(tags_iter = g_list_first(all_selected_tags);
			NULL != tags_iter; 
			tags_iter = g_list_next(tags_iter)) {
			tree_path = (GtkTreePath *)(tags_iter->data);
			gtk_tree_model_get_iter(tag_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(tag_model, &tree_iter, 0,
				&tag, -1);

			g_string_append(all_tags, tag);
			g_string_append_c(all_tags, '\n');

			gtk_tree_path_free(tree_path);
			g_free(tag);
		}
		gtk_clipboard_set_text(b, all_tags->str, -1);
		g_string_free(all_tags, TRUE);
		g_list_free (all_selected_tags);
		break;

	case GDK_F5:
		tags_list_refresh_by_path(tag_model, tagal, "");
		break;
	case GDK_Delete:
		tags_selection = 
			gtk_tree_view_get_selection(arg->all_tags_tree);
		all_selected_tags = 
			gtk_tree_selection_get_selected_rows(
				tags_selection, NULL);
		for(tags_iter = g_list_first(all_selected_tags);
			NULL != tags_iter; 
			tags_iter = g_list_next(tags_iter)) {
			tree_path = (GtkTreePath *)(tags_iter->data);
			gtk_tree_model_get_iter(tag_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(tag_model, &tree_iter, 0,
				&tag, -1);
			tagal_tag_del_tag(tagal, tag);
			gtk_tree_model_row_deleted(tag_model, tree_path);
			gtk_tree_path_free(tree_path);
			g_free(tag);
		}
		g_list_free (all_selected_tags);
		tags_list_refresh_by_path(tag_model, tagal, "");
		break;
	default:
		break;
	}

	return FALSE;
}

