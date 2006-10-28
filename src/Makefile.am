SUBDIRS = AI Entities Audio Common Control Graphics Math Physics Util Triggers \
	Network
lib_LTLIBRARIES = libInGE.la
libInGE_la_SOURCES = InGE.h

libInGE_la_LIBADD = $(top_builddir)/src/Util/libUtil.la \
	$(top_builddir)/src/Triggers/libTriggers.la $(top_builddir)/src/Physics/libPhysics.la \
	$(top_builddir)/src/Math/libMath.la $(top_builddir)/src/Graphics/libGraphics.la \
	$(top_builddir)/src/Control/libControl.la $(top_builddir)/src/Common/libCommon.la \
	$(top_builddir)/src/Audio/libAudio.la $(top_builddir)/src/AI/libAI.la \
	$(top_builddir)/src/Entities/libEntities.la $(top_builddir)/src/Network/libNetwork.la
	
libInGE_la_LDFLAGS = -release $(LT_RELEASE)	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)



