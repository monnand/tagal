/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */
#ifndef MONNAND_GTKTAGAL_MAIN_WND_INTERFACE_H
#define MONNAND_GTKTAGAL_MAIN_WND_INTERFACE_H

#include "global_var.h"

typedef struct main_wnd_menu_arg_t {
	search_main_wnd_arg_t *main_arg;
	GtkTreeModel *model;
	GtkTreePath *selected_row;
}main_wnd_menu_arg_t;

GtkWidget* create_search_wnd (void);
GtkWidget* create_file_item_menu (main_wnd_menu_arg_t *arg);
GtkWidget* create_tag_item_menu (main_wnd_menu_arg_t *arg);
GtkWidget* create_tagal_about_dialog (void);

#endif /* MONNAND_GTKTAGAL_MAIN_WND_INTERFACE_H */

