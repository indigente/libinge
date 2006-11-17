SUBDIRS = AI Entities Audio Common Control Graphics Math Physics Util Triggers \
	Network
lib_LTLIBRARIES = libInGE.la
libInGE_la_SOURCES = InGE.h

LT_CURRENT = 0
LT_REVISION = 0
LT_AGE = 0

libInGE_la_LIBADD = $(top_builddir)/src/Util/libUtil.la \
	$(top_builddir)/src/Triggers/libTriggers.la $(top_builddir)/src/Physics/libPhysics.la \
	$(top_builddir)/src/Math/libMath.la $(top_builddir)/src/Graphics/libGraphics.la \
	$(top_builddir)/src/Control/libControl.la $(top_builddir)/src/Common/libCommon.la \
	$(top_builddir)/src/Audio/libAudio.la $(top_builddir)/src/AI/libAI.la \
	$(top_builddir)/src/Entities/libEntities.la $(top_builddir)/src/Network/libNetwork.la
	
libInGE_la_LDFLAGS = -release @PACKAGE_VERSION@	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

install-data-local:
	find . -name '*.h' -exec ./install-header '{}' $(DESTDIR)$(pkgincludedir) ';'
	mkdir -p $(DESTDIR)$(libdir)/pkgconfig
	$(INSTALL_DATA) inge.pc $(DESTDIR)$(libdir)/pkgconfig

uninstall-local:
	rm -rf $(DESTDIR)$(pkgincludedir)
	rm -rf $(DESTDIR)$(libdir)/pkgconfig/inge.pc
	rmdir --ignore-fail-on-non-empty $(DESTDIR)$(libdir)/pkgconfig
