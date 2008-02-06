#ifndef MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_CB_H
#define MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_CB_H

#include <gtk/gtk.h>


gboolean
on_add_tags_to_file_wnd_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_add_tags_to_file_confirm_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_add_tags_to_file_cancel_clicked     (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_cur_file_tags_tree_key_release_event
                                        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_all_tags_tree_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

gboolean
on_all_tags_tree_key_release_event     (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

#endif /* MONNAND_TAGALADDTAGS_ADD_TAGS_TO_FILE_WND_CB_H */
