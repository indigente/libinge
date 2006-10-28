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
#include "GeomBox.h"

using namespace InGE;

GeomBox::GeomBox(Vector3 length, PhysicalSpace *ps){
	if(!ps)	m_geomId = dCreateBox(0, length[0], length[1], length[2]);
	else	m_geomId = dCreateBox(ps->getId(), length[0], length[1], length[2]);
	
	dGeomSetData(m_geomId, (void *) this);
}

GeomBox::~GeomBox(){
	dGeomDestroy(m_geomId);
}

void GeomBox::setData(void *data){
	m_pData = data;
}

void GeomBox::setLengths(Vector3 &length){
	dGeomBoxSetLengths(m_geomId, length[0], length[1], length[2]);
}

Vector3 GeomBox::getLengths(){
	dVector3 result;
	dGeomBoxGetLengths(m_geomId, result);
	return Vector3((float *) result);
}

float GeomBox::pointDepth(Vector3 &point){
	return dGeomBoxPointDepth(m_geomId, point[0], point[1], point[2]);
}
