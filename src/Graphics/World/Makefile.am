INCLUDES = 
METASOURCES = AUTO
SUBDIRS = Heightmap Q3Bsp
noinst_LTLIBRARIES = libWorld.la
libWorld_la_SOURCES = BspScene.cpp
libWorld_la_LIBADD = $(top_builddir)/src/Graphics/World/Q3Bsp/libQ3Bsp.la\
	$(top_builddir)/src/Graphics/World/Heightmap/libHeightmap.la
noinst_HEADERS = BspScene.h
