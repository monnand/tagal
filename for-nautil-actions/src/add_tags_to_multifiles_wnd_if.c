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
create_add_tags_to_multifiles_wnd (add_tags_to_multifiles_wnd_arg_t *arg)
{
  GtkWidget *add_tags_to_multifiles_wnd;
  GtkWidget *vpaned1;
  GtkWidget *hpaned2;
  GtkWidget *add_tags_to_multifile_wnd_entry;
  GtkWidget *hbox1;
  GtkWidget *add_tags_to_multfile_confirm;
  GtkWidget *hbox2;
  GtkWidget *image1;
  GtkWidget *label1;
  GtkWidget *add_tags_to_multfile_cancel;
  GtkWidget *hbox3;
  GtkWidget *image2;
  GtkWidget *label2;
  GtkWidget *scrolledwindow1;
  GtkWidget *add_tags_to_mulfiles_tags_tree;

  add_tags_to_multifiles_wnd = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_events (add_tags_to_multifiles_wnd, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
  gtk_window_set_default_size (GTK_WINDOW (add_tags_to_multifiles_wnd), 450, 400);

  vpaned1 = gtk_vpaned_new ();
  gtk_widget_show (vpaned1);
  gtk_container_add (GTK_CONTAINER (add_tags_to_multifiles_wnd), vpaned1);
  gtk_paned_set_position (GTK_PANED (vpaned1), 60);

  hpaned2 = gtk_hpaned_new ();
  gtk_widget_show (hpaned2);
  gtk_paned_pack1 (GTK_PANED (vpaned1), hpaned2, FALSE, TRUE);
  gtk_paned_set_position (GTK_PANED (hpaned2), 289);

  add_tags_to_multifile_wnd_entry = gtk_entry_new ();
  gtk_widget_show (add_tags_to_multifile_wnd_entry);
  gtk_paned_pack1 (GTK_PANED (hpaned2), add_tags_to_multifile_wnd_entry, FALSE, TRUE);
  gtk_widget_set_events (add_tags_to_multifile_wnd_entry, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
  gtk_entry_set_invisible_char (GTK_ENTRY (add_tags_to_multifile_wnd_entry), 9679);
  gtk_entry_set_activates_default (GTK_ENTRY (add_tags_to_multifile_wnd_entry), TRUE);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_paned_pack2 (GTK_PANED (hpaned2), hbox1, TRUE, TRUE);

  add_tags_to_multfile_confirm = gtk_button_new ();
  gtk_widget_show (add_tags_to_multfile_confirm);
  gtk_box_pack_start (GTK_BOX (hbox1), add_tags_to_multfile_confirm, TRUE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_container_add (GTK_CONTAINER (add_tags_to_multfile_confirm), hbox2);

  image1 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox2), image1, TRUE, TRUE, 0);

  label1 = gtk_label_new (_("Apply"));
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (hbox2), label1, TRUE, TRUE, 0);

  add_tags_to_multfile_cancel = gtk_button_new ();
  gtk_widget_show (add_tags_to_multfile_cancel);
  gtk_box_pack_start (GTK_BOX (hbox1), add_tags_to_multfile_cancel, TRUE, TRUE, 0);

  hbox3 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox3);
  gtk_container_add (GTK_CONTAINER (add_tags_to_multfile_cancel), hbox3);

  image2 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox3), image2, TRUE, TRUE, 0);

  label2 = gtk_label_new (_("Cancel"));
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox3), label2, TRUE, TRUE, 0);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_paned_pack2 (GTK_PANED (vpaned1), scrolledwindow1, TRUE, TRUE);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  add_tags_to_mulfiles_tags_tree = gtk_tree_view_new ();
  gtk_widget_show (add_tags_to_mulfiles_tags_tree);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), add_tags_to_mulfiles_tags_tree);
  gtk_widget_set_events (add_tags_to_mulfiles_tags_tree, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
  gtk_tree_view_set_reorderable (GTK_TREE_VIEW (add_tags_to_mulfiles_tags_tree), TRUE);

  tags_list_view_set(GTK_TREE_VIEW(add_tags_to_mulfiles_tags_tree), "All Tags");
  tags_list_refresh_by_path(gtk_tree_view_get_model(
		GTK_TREE_VIEW(add_tags_to_mulfiles_tags_tree)), arg->tagal, "");

  arg->all_tags_tree = GTK_TREE_VIEW(add_tags_to_mulfiles_tags_tree);
  arg->input_entry = GTK_ENTRY(add_tags_to_multifile_wnd_entry);
  arg->wnd = add_tags_to_multifiles_wnd;

  g_signal_connect ((gpointer) add_tags_to_multifiles_wnd, "delete_event",
                    G_CALLBACK (on_add_tags_to_multifiles_wnd_delete_event),
		    arg);
  g_signal_connect ((gpointer) add_tags_to_multfile_confirm, "clicked",
                    G_CALLBACK (on_add_tags_to_multfile_confirm_clicked),
		    arg);
  g_signal_connect ((gpointer) add_tags_to_multfile_cancel, "clicked",
                    G_CALLBACK (on_add_tags_to_multfile_cancel_clicked),
		    arg);
  g_signal_connect ((gpointer) add_tags_to_mulfiles_tags_tree, "row_activated",
                    G_CALLBACK (on_add_tags_to_mulfiles_tags_tree_row_activated),
		    arg);
  g_signal_connect ((gpointer) add_tags_to_mulfiles_tags_tree, "key_release_event",
                    G_CALLBACK (on_all_tags_tree_key_release_event),
		    arg);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (add_tags_to_multifiles_wnd, add_tags_to_multifiles_wnd, "add_tags_to_multifiles_wnd");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, vpaned1, "vpaned1");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, hpaned2, "hpaned2");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, add_tags_to_multifile_wnd_entry, "add_tags_to_multifile_wnd_entry");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, add_tags_to_multfile_confirm, "add_tags_to_multfile_confirm");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, image1, "image1");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, label1, "label1");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, add_tags_to_multfile_cancel, "add_tags_to_multfile_cancel");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, image2, "image2");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, label2, "label2");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (add_tags_to_multifiles_wnd, add_tags_to_mulfiles_tags_tree, "add_tags_to_mulfiles_tags_tree");

  return add_tags_to_multifiles_wnd;
}

