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
#include "GeomCylinder.h"

using namespace InGE;

GeomCylinder::GeomCylinder(float radius, float length, PhysicalSpace *ps){
	if(!ps)	m_geomId = dCreateCCylinder(0,           radius, length);
	else	m_geomId = dCreateCCylinder(ps->getId(), radius, length);	
	
	m_radius = radius;
	m_length = length;
	dGeomSetData(m_geomId, (void *) this);
}

GeomCylinder::~GeomCylinder(){
	dGeomDestroy(m_geomId);
}

void GeomCylinder::setData(void *data){
	m_pData = data;
}

void GeomCylinder::setParams(float radius, float length){
	dGeomCCylinderSetParams(m_geomId, radius, length);
	m_radius = radius;
	m_length = length;	
}

float GeomCylinder::getRadius(){
	return m_radius;
}

float GeomCylinder::getLength(){
	return m_length;
}

void GeomCylinder::updateParam(){
	dGeomCCylinderGetParams(m_geomId, (dReal *) &m_radius, (dReal *) &m_length);
}

float GeomCylinder::pointDepth(Vector3 &point){
	return dGeomCCylinderPointDepth(m_geomId, point[0], point[1], point[2]);
}

