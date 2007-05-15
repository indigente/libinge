INCLUDES = 
METASOURCES = AUTO
bin_PROGRAMS = COLLADA2InGE
noinst_HEADERS = Importer.h
COLLADA2InGE_SOURCES = Importer.cpp

COLLADA2InGE_LDADD = \
	$(top_builddir)/src/Tools/COLLADA_DOM/dae/libcollada_dae.la $(top_builddir)/src/Tools/COLLADA_DOM/dom/libcollada_dom.la \
	$(top_builddir)/src/Tools/COLLADA_DOM/modules/STLDatabase/libcollada_STLDatabase.la \
	$(top_builddir)/src/Tools/COLLADA_DOM/modules/XMLPlugin/libcollada_LIBXMLPlugin.la \
	$(top_builddir)/src/Tools/COLLADA_DOM/modules/stdErrPlugin/libcollada_stdErrPlugin.la $(top_builddir)/src/libInGE.la -lCEGUIOpenGLRenderer -lCEGUIBase -lGLU \
	-lGL -lxml2
SUBDIRS = COLLADA_DOM
