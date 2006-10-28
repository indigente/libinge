/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2005 Indigente


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "GeomPlane.h"

using namespace InGE;

GeomPlane::GeomPlane(){
	m_geomId = dCreatePlane(0,0, 1, 0, 0);
	dGeomSetData(m_geomId, (void *) this);
}

GeomPlane::GeomPlane(Vector3 normal, float d, PhysicalSpace *ps){
	if(!ps)	m_geomId = dCreatePlane(0,           normal[0], normal[1], normal[2], d);
	else	m_geomId = dCreatePlane(ps->getId(), normal[0], normal[1], normal[2], d);
	
	dGeomSetData(m_geomId, (void *) this);
}

GeomPlane::GeomPlane(Vector4 plane, PhysicalSpace *ps){
	if(!ps)	m_geomId = dCreatePlane(0,           plane[0], plane[1], plane[2], plane[3]);
	else	m_geomId = dCreatePlane(ps->getId(), plane[0], plane[1], plane[2], plane[3]);
	
	setData((void *) this);
}

GeomPlane::~GeomPlane(){
	dGeomDestroy(m_geomId);
}

void GeomPlane::setData(void *data){
	m_pData = data;
}

void GeomPlane::setParams(const Vector4 &plane){
	dGeomPlaneSetParams(m_geomId, plane.getX(), plane.getY(), plane.getZ(), plane.getW());
}

void GeomPlane::setParams(const Vector3 &normal, float d){
	dGeomPlaneSetParams(m_geomId, normal.getX(), normal.getY(), normal.getZ(), d);
}

Vector4 GeomPlane::getParams(){
	dVector4 result;
	dGeomPlaneGetParams(m_geomId, result);
	return Vector4((float *) result);
}

float GeomPlane::pointDepth(const Vector3 &point){
	return dGeomPlanePointDepth(m_geomId, point.getX(), point.getY(), point.getZ());
}

