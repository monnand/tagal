#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <string.h>


void
on_add_files_wnd_cancel_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	add_files_wnd_arg_t *arg = (add_files_wnd_arg_t *)user_data;
	gtk_widget_destroy(arg->wnd);
	g_free(arg);
}


void
on_add_files_wnd_confirm_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	add_files_wnd_arg_t *arg = (add_files_wnd_arg_t *)user_data;
	GtkFileChooser *chooser = GTK_FILE_CHOOSER(arg->wnd);
	GSList *files = gtk_file_chooser_get_filenames(chooser);
	GSList *iter;
	tagal_t *tagal = arg->tagal;
	GString *add_tags;

	const gchar *cur_dir;
	int dir_len;
	
	cur_dir = gtk_entry_get_text(arg->entry);
	if(NULL == cur_dir || 0 == strlen(cur_dir))
		add_tags = NULL;
	else {
		for(;'\n' == *cur_dir && 0 != *cur_dir; cur_dir++);
		if(0 == *cur_dir)
			add_tags = NULL;
		else 
			add_tags = format_search_str(cur_dir);
	}

	cur_dir = gtk_file_chooser_get_current_folder(chooser);
	dir_len = strlen(cur_dir);
	if(NULL != last_accessed_dir) {
		if(strlen(last_accessed_dir) >= strlen(cur_dir))
			strcpy(last_accessed_dir, cur_dir);
		else {
			g_free(last_accessed_dir);
			last_accessed_dir = g_strdup(cur_dir);
		}
	} else
			last_accessed_dir = g_strdup(cur_dir);

	for(iter = (files); iter != NULL;
		iter = g_slist_next(iter)) {
		gchar *filename = iter->data;

		tagal_add_data(tagal, filename, filename + dir_len + 1);
		
		if(NULL != add_tags) {
			tagal_data_add_tags_to_path(tagal, filename, add_tags->str);
		}

		g_free(filename);
	}
	g_slist_free(files);
	if(NULL != add_tags)
		g_string_free(add_tags, TRUE);
	gtk_widget_destroy(arg->wnd);
	g_free(arg);
}

