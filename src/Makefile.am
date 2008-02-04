include_HEADERS = $(top_srcdir)/include/error.h 	\
		  $(top_srcdir)/include/dlist.h	\
		  dbinterface.h	\
		  db_sqlite.h	\
		  db_sqlite_impl.h	\
		  global.h	\
		  mempool.h	\
		  tagaldb.h	\
		  tagal_errno.h	\
		  tagal.h	
lib_LIBRARIES = libtagal.a
libtagal_a_SOURCES = error.c mempool.c db_sqlite_impl.c \
		     dbinterface.c tagaldb.c libtagal.c

#bin_PROGRAMS = tagal_test

#tagal_test_SOURCES = tagal_test.c

#test_dataelem_SOURCES = test_dataelem.c
#test_tagedset_SOURCES = test_tagedset.c
#test_sqlite_SOURCES = test_sqlite.c
#test_dataelem_LDADD = libtagal.a
#test_tagedset_LDADD = libtagal.a
#test_sqlite_LDADD = $(top_srcdir)/sqlite/libsqlite3.la 
libtagal_a_LIBADD = $(top_srcdir)/sqlite/libsqlite3.la 
#tagal_test_LDADD = $(top_srcdir)/sqlite/libsqlite3.la libtagal.a
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/sqlite
