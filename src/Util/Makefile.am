INCLUDES = 
METASOURCES = AUTO
noinst_LTLIBRARIES = libUtil.la
libUtil_la_SOURCES = BitSet.cpp LogManager.cpp SpaceTree.cpp SpaceLeaf.cpp \
	QuadTree.cpp SpaceNode.cpp




SUBDIRS = TinyXML

libUtil_la_LIBADD = $(top_builddir)/src/Util/TinyXML/libTinyXML.la

noinst_HEADERS = SpaceTree.h SpaceLeaf.h QuadTree.h SpaceNode.h
