## Testing for graph libraries

TESTS = ut_graph
check_PROGRAMS = ut_graph
ut_graph_SOURCES = ut_graph.c $(top_builddir)/src/graph.h
ut_graph_CFLAGS = @CHECK_CFLAGS@
ut_graph_LDADD = $(top_builddir)/src/libgraph.la @CHECK_LIBS@
