#include <gtk/gtk.h>

gboolean
on_search_wnd_delete_event	      (GtkWidget *widget,
					GdkEvent  *event,
				       	gpointer   user_data);

void
on_add_file_button_clicked             (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_add_tag_button_clicked              (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_connect_button_clicked              (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_disconnect_button_clicked           (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_config_button_clicked               (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_help_button_clicked                 (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_about_button_clicked                (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_search_button_clicked               (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_clear_button_clicked                (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

gboolean
on_files_tree_select_cursor_row        (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data);

gboolean
on_files_tree_key_press_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_files_tree_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
gboolean
on_files_tree_button_release_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_files_tree_key_release_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_tags_tree_select_cursor_row         (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data);

gboolean
on_tags_tree_key_press_event           (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_tags_tree_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

gboolean
on_tags_tree_button_release_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_tags_tree_key_release_event         (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
menu_reaper			      (GtkMenuShell    *menushell,
                                        gpointer         user_data);

void
on_file_item_menu_destroy              (GtkObject       *object,
                                        gpointer         user_data);

void
on_open_file_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_file_open_dir_activate		(GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy_file_path_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_add_tags_to_file_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

/*
void
on_file_show_tags_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_file_details_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
*/

void
on_del_file_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_tag_search_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_add_files_to_tag_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy_tag_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);


void
on_tag_del_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
