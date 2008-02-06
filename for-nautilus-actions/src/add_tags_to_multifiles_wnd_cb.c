#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "add_tags_to_multifiles_wnd_cb.h"
#include "add_tags_to_multifiles_wnd_if.h"
#include "support.h"

#include <stdlib.h>


gboolean
on_add_tags_to_multifiles_wnd_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	add_tags_to_multifiles_wnd_arg_t *arg = 
		(add_tags_to_multifiles_wnd_arg_t *)user_data;
	if(arg->exit_on_delete)
		exit(0);

  return FALSE;
}


void
on_add_tags_to_multfile_confirm_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	add_tags_to_multifiles_wnd_arg_t *arg = 
		(add_tags_to_multifiles_wnd_arg_t *)user_data;
	char **path_ptr = arg->path;
	char *file_path;
	const char *base_dir = arg->base_dir;
	int i;
	tagal_t *tagal = arg->tagal;
	GtkTreeSelection *tags_selection = 
		gtk_tree_view_get_selection(arg->all_tags_tree);
	GList *all_selected_tags = gtk_tree_selection_get_selected_rows(
			tags_selection, NULL);
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->all_tags_tree);

	GtkTreeIter tree_iter;
	GList *tags_iter = NULL;
	GtkTreePath *tag = NULL;
	gchar *tag_tag = NULL;

	GString *ftags = format_search_str(
			gtk_entry_get_text(arg->input_entry));

	for(i = 0; i < arg->nr_path; i++) {
		file_path = path_ptr[i];
		tagal_add_data(tagal, file_path, file_path + strlen(base_dir) + 1);
		for(tags_iter = g_list_first(all_selected_tags); 
			NULL != tags_iter;
			tags_iter = g_list_next(tags_iter)) {
			tag = (GtkTreePath *)(tags_iter->data);
			gtk_tree_model_get_iter(tag_model, &tree_iter, tag);
			gtk_tree_model_get(tag_model, &tree_iter, 0, &tag_tag, -1);

			tagal_data_add_tag_to_path(tagal, file_path, tag_tag);
			g_free(tag_tag);
		}
		tagal_data_add_tags_to_path(tagal, file_path, ftags->str);
	}
	g_list_foreach(all_selected_tags, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (all_selected_tags);
	g_string_free(ftags, TRUE);
	gtk_widget_destroy(arg->wnd);
	if(arg->exit_on_delete)
		exit(0);
}


void
on_add_tags_to_multfile_cancel_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	add_tags_to_multifiles_wnd_arg_t *arg = 
		(add_tags_to_multifiles_wnd_arg_t *)user_data;
	gtk_widget_destroy(arg->wnd);
	if(arg->exit_on_delete)
		exit(0);
}


void
on_add_tags_to_mulfiles_tags_tree_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


gboolean
on_add_tags_to_multifile_tags_tree_key_release_event     
					(GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{

  return FALSE;
}

