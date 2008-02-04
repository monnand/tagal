#ifndef MONNAND_GTKTAGAL_ADD_TAGS_TO_FILE_WND_CB_H
#define MONNAND_GTKTAGAL_ADD_TAGS_TO_FILE_WND_CB_H

#include <gtk/gtk.h>


gboolean
on_add_tags_to_file_wnd_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_add_tags_to_file_confirm_clicked    (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

void
on_add_tags_to_file_cancel_clicked     (GtkToolButton   *toolbutton,
                                        gpointer         user_data);

gboolean
on_add_tags_to_file_tags_tree_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

#endif /* MONNAND_GTKTAGAL_ADD_TAGS_TO_FILE_WND_CB_H */

