## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gtk-tagal

gtk_tagal_SOURCES = \
	main.c \
	support.c support.h \
	interface.h \
	main_wnd_if.c main_wnd_if.h	\
	add_tags_to_file_wnd_if.c add_tags_to_file_wnd_if.h	\
	add_files_wnd_if.c add_files_wnd_if.h	\
	callbacks.h	\
	main_wnd_cb.c main_wnd_cb.h	\
	add_tags_to_file_wnd_cb.c add_tags_to_file_wnd_cb.h	\
	add_files_wnd_cb.c add_files_wnd_cb.h	\
	files_list.c files_list.h	\
	tags_list.c tags_list.h	\
	files_list_view.c files_list_view.h	\
	format_search_str.c format_search_str.h	\
	tags_list_view.c tags_list_view.h	\
	config_interface.c config_interface.h	\
	global_var.h gtktagal_global.h

gtk_tagal_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)	\
		  $(top_srcdir)/../libtagal/libtagal.a	\
		  $(top_srcdir)/../sqlite/libsqlite3.la

AM_CPPFLAGS = -I$(top_srcdir)/../libtagal/	\
		-Wl,-R/usr/local/lib 

