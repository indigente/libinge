INCLUDES = 
METASOURCES = AUTO
SUBDIRS = Md2 Md3
noinst_LTLIBRARIES = libKFModel.la
libKFModel_la_SOURCES = Face.cpp KeyFrame.cpp KFModelFactory.cpp \
		BoundVolume.cpp CurrentAnimInfo.cpp
libKFModel_la_LIBADD = $(top_builddir)/src/Graphics/Model/KFModel/Md3/libMd3.la\
	$(top_builddir)/src/Graphics/Model/KFModel/Md2/libMd2.la
noinst_HEADERS = Face.h IKFModel.h KeyFrame.h KFModelFactory.h \
	CurrentAnimInfo.h
