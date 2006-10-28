INCLUDES = 
METASOURCES = AUTO
SUBDIRS = MeshDecorator
noinst_LTLIBRARIES = libBase.la
libBase_la_SOURCES = MaterialInfo.cpp TextureArray.cpp Vertex.cpp \
	VolumeInfo.cpp
libBase_la_LIBADD =\
	$(top_builddir)/src/Graphics/Base/MeshDecorator/libMeshDecorator.la
noinst_HEADERS = MaterialInfo.h Mesh.h TextureArray.h Vertex.h VolumeInfo.h
