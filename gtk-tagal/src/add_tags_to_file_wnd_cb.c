#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "format_search_str.h"

gboolean
on_add_tags_to_file_wnd_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	g_free(arg->file_path);
	g_free(arg);

	return FALSE;
}


void
on_add_tags_to_file_confirm_clicked    (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	GtkTreeSelection *tags_selection = 
		gtk_tree_view_get_selection(arg->tags_tree);
	GList *all_selected_tags = gtk_tree_selection_get_selected_rows(
			tags_selection, NULL);
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->tags_tree);
	gchar *file_path = arg->file_path;

	GtkTreeIter tree_iter;
	GList *tags_iter = NULL;
	GtkTreePath *tag = NULL;
	gchar *tag_tag = NULL;
	tagal_t *tagal = arg->tagal;

	for(tags_iter = g_list_first(all_selected_tags); NULL != tags_iter;
		tags_iter = g_list_next(tags_iter)) {
		tag = (GtkTreePath *)(tags_iter->data);
		gtk_tree_model_get_iter(tag_model, &tree_iter, tag);
		gtk_tree_model_get(tag_model, &tree_iter, 0, &tag_tag, -1);

		tagal_data_add_tag_to_path(tagal, file_path, tag_tag);
		g_free(tag_tag);
	}

	g_list_foreach (all_selected_tags, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (all_selected_tags);

	GString *ftags = format_search_str(
			gtk_entry_get_text(arg->input_entry));

	tag_tag = ftags->str;
	gchar *ptr = NULL;
	for(ptr = strchr(tag_tag, '\n'); NULL != ptr; 
		ptr = strchr(tag_tag, '\n')) {
		*ptr = 0;
		tagal_data_add_tag_to_path(tagal, file_path, tag_tag);
		do {
			ptr++;
		} while('\n' == *ptr);
		tag_tag = ptr;
	}
	g_string_free(ftags, TRUE);

	gtk_widget_destroy(arg->wnd);
	g_free(arg->file_path);
	g_free(arg);
}


void
on_add_tags_to_file_cancel_clicked     (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	add_tags_to_file_wnd_arg_t *arg = 
		(add_tags_to_file_wnd_arg_t *)user_data;
	gtk_widget_destroy(arg->wnd);
	g_free(arg->file_path);
	g_free(arg);
}


gboolean
on_add_tags_to_file_tags_tree_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}

