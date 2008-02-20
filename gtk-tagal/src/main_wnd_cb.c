#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "global_var.h"
#include "files_list_view.h"
#include "tags_list_view.h"
#include "format_search_str.h"
#include "config_interface.h"
#include <string.h>

gboolean
on_search_wnd_delete_event (GtkWidget *widget,
					GdkEvent  *event,
				       	gpointer   user_data)
{
	exit(0);
}

void
on_add_file_button_clicked             (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	add_files_wnd_arg_t *new_arg;
	GtkWidget *new_wnd;
	new_arg = (add_files_wnd_arg_t *)g_malloc(sizeof(add_files_wnd_arg_t));
	memset(new_arg, 0, sizeof(add_files_wnd_arg_t));

	new_arg->tagal = tagal_handler;
	new_arg->main_arg = (search_main_wnd_arg_t *)user_data;
	new_wnd = create_add_files_wnd(new_arg);
	gtk_widget_show(new_wnd);
}


void
on_add_tag_button_clicked              (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{

}

static void del_tags_from_file(gpointer data, gpointer user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreePath *file = (GtkTreePath *)(data);
	GtkTreeSelection *tags_selection = 
		gtk_tree_view_get_selection(arg->tags_tree);
	GList *all_selected_tags = gtk_tree_selection_get_selected_rows(
			tags_selection, NULL);

	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->tags_tree);
	GtkTreeModel *file_model = gtk_tree_view_get_model(arg->files_tree);

	GtkTreeIter tree_iter;
	gchar *file_path;
	gtk_tree_model_get_iter(file_model, &tree_iter, file);
	gtk_tree_model_get(file_model, &tree_iter, 1, &file_path, -1);

	GList *tags_iter = NULL;
	GtkTreePath *tag = NULL;
	gchar *tag_tag = NULL;
	tagal_t *tagal = arg->tagal;

	for(tags_iter = g_list_first(all_selected_tags); NULL != tags_iter;
		tags_iter = g_list_next(tags_iter)) {
		tag = (GtkTreePath *)(tags_iter->data);
		gtk_tree_model_get_iter(tag_model, &tree_iter, tag);
		gtk_tree_model_get(tag_model, &tree_iter, 0, &tag_tag, -1);
		
		tagal_data_del_tag_by_path(tagal, file_path, tag_tag);

		if(!strcmp(gtk_label_get_text(arg->tags_tree_label), 
			file_path)) {
			gtk_tree_model_row_deleted(tag_model, tag);
		}
		g_free(tag_tag);
		tag_tag = NULL;
		gtk_tree_path_free(tag);
	}

	//g_list_foreach (all_selected_tags, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (all_selected_tags);
	g_free(file_path);
	gtk_tree_path_free(file);
}



static void add_tags_to_file(gpointer data, gpointer user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreePath *file = (GtkTreePath *)(data);
	GtkTreeSelection *tags_selection = 
		gtk_tree_view_get_selection(arg->tags_tree);
	GList *all_selected_tags = gtk_tree_selection_get_selected_rows(
			tags_selection, NULL);

	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->tags_tree);
	GtkTreeModel *file_model = gtk_tree_view_get_model(arg->files_tree);

	GtkTreeIter tree_iter;
	gchar *file_path;
	gtk_tree_model_get_iter(file_model, &tree_iter, file);
	gtk_tree_model_get(file_model, &tree_iter, 1, &file_path, -1);

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
		tag_tag = NULL;
		gtk_tree_path_free(tag);
	}

	//g_list_foreach (all_selected_tags, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (all_selected_tags);
	g_free(file_path);
	gtk_tree_path_free(file);
}

void
on_connect_button_clicked              (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeSelection *files_selection = 
		gtk_tree_view_get_selection(arg->files_tree);

	GList *all_selected_files = gtk_tree_selection_get_selected_rows(
			files_selection, NULL);
	g_list_foreach(all_selected_files, (GFunc)add_tags_to_file, user_data);

	//g_list_foreach (all_selected_files, (GFunc)(gtk_tree_path_free), NULL);
	g_list_free (all_selected_files);
}


void
on_disconnect_button_clicked           (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeSelection *files_selection = 
		gtk_tree_view_get_selection(arg->files_tree);

	GList *all_selected_files = gtk_tree_selection_get_selected_rows(
			files_selection, NULL);
	g_list_foreach(all_selected_files, (GFunc)del_tags_from_file, user_data);

	//g_list_foreach (all_selected_files, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (all_selected_files);
}


void
on_config_button_clicked               (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{

}


void
on_help_button_clicked                 (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{

}


void
on_about_button_clicked                (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	GtkWidget *tagal_about_dialog;
	tagal_about_dialog = create_tagal_about_dialog ();
	gtk_widget_show (tagal_about_dialog);
}

void
on_clear_button_clicked                (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	refresh_tags_view_with_path(arg, "", "");
	refresh_files_view_with_tags(arg, "", "");
	gtk_entry_set_text(arg->input_text_entry, "");
}

void
on_search_button_clicked               (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GString *str;
	const char *new_label;
	new_label = gtk_entry_get_text(arg->input_text_entry);
	str = format_search_str(new_label);
	if('\n' == *(str->str) && 1 == strlen(str->str)) {
		*(str->str) = 0;
		refresh_tags_view_with_path(arg, str->str, "");
	}

	refresh_files_view_with_tags(arg, str->str, new_label);
	g_string_free(str, TRUE);
}


gboolean
on_files_tree_select_cursor_row        (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data)
{
  return FALSE;
}


gboolean
on_files_tree_key_press_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_files_tree_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	gchar *file_name, *file_path;
	GtkTreeIter tree_iter;

	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	gtk_tree_model_get_iter(model, &tree_iter, path);
	gtk_tree_model_get(model, &tree_iter, 0, 
		&file_name, 1, &file_path, -1);

	refresh_tags_view_with_path(arg, file_path, file_path);
	g_free(file_name);
	g_free(file_path);
}


gboolean
on_files_tree_key_release_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeSelection *files_selection;
	GList *all_selected_files;
	GList *files_iter;
	GtkTreePath *tree_path= NULL;
	gchar *file_path= NULL;
	tagal_t *tagal = arg->tagal;
	GtkTreeModel *file_model = gtk_tree_view_get_model(arg->files_tree);
	GtkTreeIter tree_iter;
	GString *all_path;
	GdkAtom atom = gdk_atom_intern("CLIPBOARD", TRUE);
	GtkClipboard *b = gtk_clipboard_get(atom);

	switch(event->keyval) {
	case GDK_c:
		if(!(event->state | GDK_CONTROL_MASK))
	       		break;
		files_selection = 
			gtk_tree_view_get_selection(arg->files_tree);
		all_selected_files = 
			gtk_tree_selection_get_selected_rows(
				files_selection, NULL);
		all_path = g_string_sized_new(1024);
		for(files_iter = g_list_first(all_selected_files);
			NULL != files_iter; 
			files_iter = g_list_next(files_iter)) {

			tree_path = (GtkTreePath *)(files_iter->data);
			gtk_tree_model_get_iter(file_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(file_model, &tree_iter, 1,
				&file_path, -1);
			g_string_append(all_path, file_path);
			g_string_append_c(all_path, '\n');
			g_free(file_path);
			gtk_tree_path_free(tree_path);
		}
		gtk_clipboard_set_text(b, all_path->str, -1);
		g_string_free(all_path, TRUE);
		g_list_free (all_selected_files);
		break;
	case GDK_F5:
		refresh_files_view_with_tags(arg, "", "");
		break;
	case GDK_Delete:
		files_selection = 
			gtk_tree_view_get_selection(arg->files_tree);
		all_selected_files = 
			gtk_tree_selection_get_selected_rows(
				files_selection, NULL);
		for(files_iter = g_list_first(all_selected_files);
			NULL != files_iter; 
			files_iter = g_list_next(files_iter)) {
			tree_path = (GtkTreePath *)(files_iter->data);
			gtk_tree_model_get_iter(file_model, &tree_iter, 
				tree_path);
			gtk_tree_model_get(file_model, &tree_iter, 1,
				&file_path, -1);
			tagal_data_del_by_path(tagal, file_path);
			gtk_tree_model_row_deleted(file_model, tree_path);
			gtk_tree_path_free(tree_path);
			g_free(file_path);
		}
		g_list_free (all_selected_files);
		break;
	default:
		break;
	}
	return TRUE;
}


gboolean
on_files_tree_button_release_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	if(3 != event->button)
		return FALSE;
	GtkTreePath *path;
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkWidget *menu;
	main_wnd_menu_arg_t *new_arg;
	new_arg = (main_wnd_menu_arg_t *)g_malloc(sizeof(main_wnd_menu_arg_t));
	new_arg->main_arg = arg;
	new_arg->model = gtk_tree_view_get_model(arg->files_tree);
	new_arg->selected_row = NULL;

	if(gtk_tree_view_get_path_at_pos(arg->files_tree, (gint)event->x,
		(gint)event->y, &path, NULL, NULL, NULL)) {
		new_arg->selected_row = path;

		menu = create_file_item_menu(new_arg);
		gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
				event->button, event->time);

		return TRUE;
	}
	return TRUE;
}

gboolean
on_tags_tree_select_cursor_row         (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_tags_tree_key_press_event           (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_tags_tree_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	tagal_t *tagal;
	GtkTreeIter tree_iter;
	gchar *tag;
	
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeModel *tag_model = gtk_tree_view_get_model(treeview);

	gtk_tree_model_get_iter(tag_model, &tree_iter, path);
	gtk_tree_model_get(tag_model, &tree_iter, 0, &tag, -1);

	refresh_files_view_with_tags(arg, tag, tag);

	g_free(tag);
}


gboolean
on_tags_tree_key_release_event         (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkTreeSelection *tags_selection;
	GList *all_selected_tags;
	GList *tags_iter;
	GtkTreePath *tree_path= NULL;
	gchar *tag = NULL;
	tagal_t *tagal = arg->tagal;
	GtkTreeModel *tag_model = gtk_tree_view_get_model(arg->tags_tree);
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
			gtk_tree_view_get_selection(arg->tags_tree);
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
		refresh_tags_view_with_path(arg, "", "");
		break;
	case GDK_Delete:
		tags_selection = 
			gtk_tree_view_get_selection(arg->tags_tree);
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
		break;
	default:
		break;
	}
	return TRUE;

  return FALSE;
}


gboolean
on_tags_tree_button_release_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	if(3 != event->button)
		return FALSE;
	GtkTreePath *path;
	search_main_wnd_arg_t *arg = (search_main_wnd_arg_t *)user_data;
	GtkWidget *menu;

	main_wnd_menu_arg_t *new_arg;
	new_arg = (main_wnd_menu_arg_t *)g_malloc(sizeof(main_wnd_menu_arg_t));

	new_arg->main_arg = arg;
	new_arg->model = gtk_tree_view_get_model(arg->tags_tree);
	new_arg->selected_row = NULL;

	if(gtk_tree_view_get_path_at_pos(arg->tags_tree, (gint)event->x,
		(gint)event->y, &path, NULL, NULL, NULL)) {
		new_arg->selected_row = path;
		menu = create_tag_item_menu(new_arg);
		gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
				event->button, event->time);

		return TRUE;
	}

	return FALSE;
}

void
menu_reaper (GtkMenuShell    *menushell,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	if(NULL != arg->selected_row) {
		gtk_tree_path_free(arg->selected_row);
	}
	g_free(user_data);
}

void
on_open_file_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *file_path, *file_name;
	char *argv[3];
	gchar *need_free;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 0, &file_name, 1, &file_path, -1);

	config_file_get_open_file_argv(config_handler, argv, 3, 
		file_path, file_name, &need_free);
	g_spawn_async(
			NULL, /* working directory */ 
			argv, /* argv */
			NULL, /* envp */
			G_SPAWN_SEARCH_PATH, /* flag */
			NULL, /* child setup */
			NULL, /* user data for child setup */
			NULL, /* pid */
			NULL);

	if(NULL != need_free)
		g_free(need_free);
	g_free(file_path);
	g_free(file_name);
}

void
on_file_open_dir_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *file_path, *file_name;
	char *argv[3];
	gchar *need_free;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 0, &file_name, 1, &file_path, -1);

	config_file_get_open_file_dir_argv(config_handler, argv, 3, 
		file_path, file_name, &need_free);
	g_spawn_async(
			NULL, /* working directory */ 
			argv, /* argv */
			NULL, /* envp */
			G_SPAWN_SEARCH_PATH, /* flag */
			NULL, /* child setup */
			NULL, /* user data for child setup */
			NULL, /* pid */
			NULL);

	if(NULL != need_free)
		g_free(need_free);
	g_free(file_path);
	g_free(file_name);
}

void
on_add_tags_to_file_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	add_tags_to_file_wnd_arg_t *wnd_arg;
	GtkWidget *new_wnd;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *file_path;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 1, &file_path, -1);

	wnd_arg = (add_tags_to_file_wnd_arg_t *)g_malloc(
			sizeof(add_tags_to_file_wnd_arg_t));
	memset(wnd_arg, 0, sizeof(add_tags_to_file_wnd_arg_t));

	wnd_arg->tagal = tagal_handler;
	wnd_arg->file_path = file_path;
	new_wnd = create_add_tags_to_file_wnd(wnd_arg);
	gtk_widget_show (new_wnd);
}

void
on_copy_file_path_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	add_tags_to_file_wnd_arg_t *wnd_arg;
	GtkWidget *new_wnd;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *file_path;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 1, &file_path, -1);

	GdkAtom atom = gdk_atom_intern("CLIPBOARD", TRUE);
	GtkClipboard *b = gtk_clipboard_get(atom);
	gtk_clipboard_set_text(b, file_path, -1);

	g_free(file_path);
}

/*
void
on_file_show_tags_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_file_details_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}
*/


void
on_del_file_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *file_path;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 1, &file_path, -1);

	tagal_data_del_by_path(tagal_handler, file_path);

	gtk_tree_model_row_deleted(model, arg->selected_row);
	g_free(file_path);
}


void
on_tag_search_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *tag;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 0, &tag, -1);

	g_free(tag);
}


void
on_add_files_to_tag_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

void
on_copy_tag_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{	
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;

	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *tag;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 0, &tag, -1);

	GdkAtom atom = gdk_atom_intern("CLIPBOARD", TRUE);
	GtkClipboard *b = gtk_clipboard_get(atom);
	gtk_clipboard_set_text(b, tag, -1);

	g_free(tag);
}

void
on_tag_del_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	main_wnd_menu_arg_t *arg = (main_wnd_menu_arg_t *)user_data;
	GtkTreeModel *model = arg->model;
	GtkTreeIter tree_iter;
	gchar *tag;

	gtk_tree_model_get_iter(model, &tree_iter, arg->selected_row);
	gtk_tree_model_get(model, &tree_iter, 0, &tag, -1);

	tagal_tag_del_tag(tagal_handler, tag);

	gtk_tree_model_row_deleted(model, arg->selected_row);
	g_free(tag);
}


void
on_file_name_change_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


gboolean
on_file_tags_tree_select_cursor_row    (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_file_tags_tree_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}

