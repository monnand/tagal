## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(top_srcdir)/../src/	\
	@PACKAGE_CFLAGS@

bin_PROGRAMS = tagal-add-tags

tagal_add_tags_SOURCES = \
	main.c \
	gtktagal_global.h	\
	support.c support.h \
	config_interface.c  config_interface.h	\
	interface.h \
	add_tags_to_multifiles_wnd_if.c add_tags_to_multifiles_wnd_if.h	\
	add_tags_to_file_wnd_if.c add_tags_to_file_wnd_if.h	\
	tags_list.c tags_list.h	\
	tags_list_view.c tags_list_view.h	\
	format_search_str.c format_search_str.h	\
	callbacks.h	\
	add_tags_to_multifiles_wnd_cb.c add_tags_to_multifiles_wnd_cb.h	\
	add_tags_to_file_wnd_cb.h add_tags_to_file_wnd_cb.c

tagal_add_tags_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)	\
		  $(top_srcdir)/../src/libtagal.a	\
		  $(top_srcdir)/../sqlite/libsqlite3.la

