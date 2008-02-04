/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_add_files_wnd (add_files_wnd_arg_t *arg)
{
  GtkWidget *add_files_wnd;
  GtkWidget *dialog_vbox1;
  GtkWidget *add_files_wnd_entry;
  GtkWidget *dialog_action_area1;
  GtkWidget *add_files_wnd_cancel;
  GtkWidget *add_files_wnd_confirm;

  add_files_wnd = gtk_file_chooser_dialog_new (_("Add Files"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (add_files_wnd), 5);
  gtk_widget_set_events (add_files_wnd, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
  g_object_set (add_files_wnd,
                "select-multiple", TRUE,
                NULL);
  gtk_window_set_position (GTK_WINDOW (add_files_wnd), GTK_WIN_POS_CENTER_ON_PARENT);
  gtk_window_set_skip_taskbar_hint (GTK_WINDOW (add_files_wnd), TRUE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (add_files_wnd), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (add_files_wnd), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox1 = GTK_DIALOG (add_files_wnd)->vbox;
  gtk_widget_show (dialog_vbox1);

  add_files_wnd_entry = gtk_entry_new ();
  gtk_widget_show (add_files_wnd_entry);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), add_files_wnd_entry, TRUE, TRUE, 0);
  gtk_widget_set_events (add_files_wnd_entry, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
  gtk_entry_set_invisible_char (GTK_ENTRY (add_files_wnd_entry), 9679);
  gtk_entry_set_activates_default (GTK_ENTRY (add_files_wnd_entry), TRUE);

  dialog_action_area1 = GTK_DIALOG (add_files_wnd)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  add_files_wnd_cancel = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_show (add_files_wnd_cancel);
  gtk_dialog_add_action_widget (GTK_DIALOG (add_files_wnd), add_files_wnd_cancel, 0);

  add_files_wnd_confirm = gtk_button_new_from_stock ("gtk-apply");
  gtk_widget_show (add_files_wnd_confirm);
  gtk_dialog_add_action_widget (GTK_DIALOG (add_files_wnd), add_files_wnd_confirm, 0);

  arg->wnd = add_files_wnd;
  arg->entry = GTK_ENTRY(add_files_wnd_entry);

  if(NULL != last_accessed_dir) {
	  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(add_files_wnd), 
			  last_accessed_dir);
  }

  g_signal_connect ((gpointer) add_files_wnd_cancel, "clicked",
                    G_CALLBACK (on_add_files_wnd_cancel_clicked),
		    arg);
  g_signal_connect ((gpointer) add_files_wnd_confirm, "clicked",
                    G_CALLBACK (on_add_files_wnd_confirm_clicked),
		    arg);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (add_files_wnd, add_files_wnd, "add_files_wnd");
  GLADE_HOOKUP_OBJECT_NO_REF (add_files_wnd, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (add_files_wnd, add_files_wnd_entry, "add_files_wnd_entry");
  GLADE_HOOKUP_OBJECT_NO_REF (add_files_wnd, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (add_files_wnd, add_files_wnd_cancel, "add_files_wnd_cancel");
  GLADE_HOOKUP_OBJECT (add_files_wnd, add_files_wnd_confirm, "add_files_wnd_confirm");

  return add_files_wnd;
}

