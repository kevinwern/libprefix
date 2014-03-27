## Testing for graph libraries

TESTS = ut_graph ut_array
check_PROGRAMS = ut_graph ut_array
ut_graph_SOURCES = ut_graph.c $(top_builddir)/src/graph.h
ut_graph_CFLAGS = @CHECK_CFLAGS@
ut_graph_LDADD = $(top_builddir)/src/libgraph.la @CHECK_LIBS@
ut_array_SOURCES = ut_array.c $(top_builddir)/src/array.h
ut_array_CFLAGS = @CHECK_CFLAGS@
ut_array_LDADD = $(top_builddir)/src/libarray.la @CHECK_LIBS@
