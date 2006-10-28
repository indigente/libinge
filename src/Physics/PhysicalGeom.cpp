/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2005 Indigente

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
#include "PhysicalGeom.h"

using namespace InGE;

PhysicalGeom::PhysicalGeom(){
	m_pPhysicalBody = NULL;
	m_pData = NULL;

}

PhysicalGeom::~PhysicalGeom(){
	if (m_pPhysicalBody) delete m_pPhysicalBody;
	if (m_pData) delete m_pData;
} 

void *PhysicalGeom::getData(){
	return m_pData;
}


void PhysicalGeom::setBody(PhysicalBody *pb){
	if(!pb) return;
	m_pPhysicalBody =  pb;
	dGeomSetBody(m_geomId,m_pPhysicalBody->getId());
}


PhysicalBody *PhysicalGeom::getBody(){
	return m_pPhysicalBody;
}


void PhysicalGeom::sumPosition(const Vector3 &position){
	Vector3 pos = Vector3((float *) dGeomGetPosition(m_geomId));
	pos += position;
	dGeomSetPosition(m_geomId, pos.getX(), pos.getY(), pos.getZ());
	
}

void PhysicalGeom::setPosition(const Vector3 &position){
	dGeomSetPosition(m_geomId, position.getX(), position.getY(), position.getZ());
	Vector3 v = position;
	if(m_pPhysicalBody) m_pPhysicalBody->setPosition(v);
}

void PhysicalGeom::setRotation(const float rotation[12]){
	dGeomSetRotation(m_geomId, (const dReal *)rotation);
	if(m_pPhysicalBody) m_pPhysicalBody->setRotation(rotation);	
}

void PhysicalGeom::setQuaternion(const float quaternion[4]){
	dGeomSetQuaternion(m_geomId, (const dReal *) quaternion);
	if(m_pPhysicalBody) m_pPhysicalBody->setQuaternion(quaternion);	
}


Vector3 PhysicalGeom::getPosition(){
	const dReal *vet = dGeomGetPosition(m_geomId);
	return Vector3((float)vet[0], (float)vet[1],(float)vet[2]);
}

const float *PhysicalGeom::getRotation(){
	return (const float *) dGeomGetRotation(m_geomId);
}


Quaternion PhysicalGeom::getQuaternion(){
	dQuaternion result;
	dGeomGetQuaternion(m_geomId, result);

	return Quaternion((float) result[0], (float)result[1], (float)result[2], (float)result[3]);
}

AABB PhysicalGeom::getAABB(){
	dReal result[6];
	Vector3 min, max;
	dGeomGetAABB(m_geomId, result);
	min.setXYZ(result[0], result[2], result[4]);
	max.setXYZ(result[1], result[3], result[5]);
	return AABB(max, min);
}

bool PhysicalGeom::isSpace(){
	return dGeomIsSpace(m_geomId) ? true : false;
}

dSpaceID PhysicalGeom::getSpaceId(){
	return dGeomGetSpace(m_geomId);
}

int PhysicalGeom::getClass(){
	return dGeomGetClass(m_geomId);
}

void PhysicalGeom::setCategoryBits(unsigned long int bits){
	dGeomSetCategoryBits(m_geomId, bits);
}

void PhysicalGeom::setCollideBits(unsigned long int bits){
	dGeomSetCollideBits(m_geomId, bits);
}


unsigned long int PhysicalGeom::getCategoryBits(){
	return dGeomGetCategoryBits(m_geomId);
}

unsigned long int PhysicalGeom::getCollideBits(){
	return dGeomGetCollideBits(m_geomId);
}


void PhysicalGeom::enable(){
	dGeomEnable(m_geomId); 
}

void PhysicalGeom::disable(){
	dGeomDisable(m_geomId);
}

bool PhysicalGeom::isEnabled(){
	return dGeomIsEnabled(m_geomId) ? true : false;
}

dGeomID PhysicalGeom::getId(){
	return m_geomId;
}


