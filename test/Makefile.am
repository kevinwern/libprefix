## Testing for graph libraries

TESTS = ut_array ut_hashtable ut_graph
check_PROGRAMS = ut_array ut_hashtable ut_graph
ut_graph_SOURCES = ut_graph.c $(top_builddir)/src/graph.h $(top_builddir)/src/array.h
ut_graph_CFLAGS = @CHECK_CFLAGS@
ut_graph_LDADD = $(top_builddir)/src/libgraph.la @CHECK_LIBS@ $(top_builddir)/src/libarray.la 
ut_array_SOURCES = ut_array.c $(top_builddir)/src/array.h $(top_builddir)/src/graph.h 
ut_array_CFLAGS = @CHECK_CFLAGS@
ut_array_LDADD = $(top_builddir)/src/libarray.la @CHECK_LIBS@ $(top_builddir)/src/libgraph.la 
ut_hashtable_SOURCES = ut_hashtable.c $(top_builddir)/src/hashtable.h
ut_hashtable_CFLAGS = @CHECK_CFLAGS@
ut_hashtable_LDADD = $(top_builddir)/src/libhashtable.la @CHECK_LIBS@ $(top_builddir)/src/libgraph.la 
