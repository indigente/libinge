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
#include "GeomRay.h"

using namespace InGE;

GeomRay::GeomRay(float length, PhysicalSpace *ps){
	if(!ps)	m_geomId = dCreateRay(0, length);
	else	m_geomId = dCreateRay(ps->getId(), length);
	
	dGeomSetData(m_geomId, (void *) this);
}

GeomRay::~GeomRay(){
	dGeomDestroy(m_geomId);
}

void GeomRay::setData(void *data){
	m_pData = data;
}


void  GeomRay::setLength(float length){
	dGeomRaySetLength(m_geomId, length);
}

float GeomRay::getLength(){
	return dGeomRayGetLength(m_geomId);
}

void  GeomRay::set(Vector3 &position, Vector3 &direction){
	dGeomRaySet(m_geomId, position[0], position[1], position[2], direction[0], direction[1], direction[2]);
}

void  GeomRay::get(Vector3 &position, Vector3 &direction){
	dGeomRayGet(m_geomId, (dReal *) &position[0], (dReal *)  &direction[0] );	
}

