INCLUDES = 
METASOURCES = AUTO
SUBDIRS = Geoms Joints
noinst_LTLIBRARIES = libPhysics.la
libPhysics_la_SOURCES = PhysicalBody.cpp PhysicalContactPoint.cpp \
		PhysicalGeom.cpp PhysicalJoint.cpp PhysicalJointGroup.cpp PhysicalSpace.cpp \
		PhysicalWorld.cpp PhysicsManager.cpp
libPhysics_la_LIBADD = $(top_builddir)/src/Physics/Joints/libJoints.la \
	$(top_builddir)/src/Physics/Geoms/libGeoms.la
noinst_HEADERS = PhysicalBody.h PhysicalContactPoint.h PhysicalGeom.h\
	PhysicalJointGroup.h PhysicalJoint.h PhysicalMass.h PhysicalSpace.h\
	PhysicalWorld.h
