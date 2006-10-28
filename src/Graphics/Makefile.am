INCLUDES = 
METASOURCES = AUTO
SUBDIRS = Base Camera FX Model Render Toolkit World
noinst_LTLIBRARIES = libGraphics.la
libGraphics_la_LIBADD = $(top_builddir)/src/Graphics/World/libWorld.la\
	$(top_builddir)/src/Graphics/Toolkit/libToolkit.la\
	$(top_builddir)/src/Graphics/Render/libRender.la\
	$(top_builddir)/src/Graphics/Model/libModel.la\
	$(top_builddir)/src/Graphics/FX/libFX.la\
	$(top_builddir)/src/Graphics/Camera/libCamera.la\
	$(top_builddir)/src/Graphics/Base/libBase.la

noinst_HEADERS = Graphics.h
libGraphics_la_SOURCES = Graphics.h
