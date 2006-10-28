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
#include "PhysicalSpace.h"
#include <cstdio>
using namespace InGE;

SpaceCallback *PhysicalSpace::m_spaceCallback = NULL;


PhysicalSpace::PhysicalSpace(SpaceType st, PhysicalSpace *ps){
	if(!ps){
		if(st == InGE_HASH_SPACE)m_spaceId = dHashSpaceCreate(0);
		else m_spaceId = dSimpleSpaceCreate(0);
	}
	else{
		if(st == InGE_HASH_SPACE) m_spaceId = dHashSpaceCreate(ps->getId());
		else m_spaceId = dSimpleSpaceCreate(ps->getId());
	}
	
	m_geomId = (dGeomID) m_spaceId;
	setData((void *) this);
	
	m_numGeom = 0;

}

PhysicalSpace::PhysicalSpace(Vector3 center, Vector3 extends, int depth, PhysicalSpace *ps){
	if(!ps)	m_spaceId = dQuadTreeSpaceCreate(0,           (dReal *)&center[0], (dReal *)&extends[0], depth);
	else	m_spaceId = dQuadTreeSpaceCreate(ps->getId(), (dReal *)&center[0], (dReal *)&extends[0], depth);
	
	m_geomId = (dGeomID) m_spaceId;
	setData((void *) this);
	
	m_numGeom = 0;
}


PhysicalSpace::~PhysicalSpace(){
	dSpaceDestroy(m_spaceId);
}

void PhysicalSpace::nearCallback(void *data, dGeomID o1, dGeomID o2){
	//printf("void PhysicalSpace::dNearCallback\n");
	PhysicalGeom *g1 = (PhysicalGeom *)dGeomGetData(o1);
	PhysicalGeom *g2 = (PhysicalGeom *)dGeomGetData(o2);
	PhysicalSpace::m_spaceCallback(*g1, *g2, data);
	
}

int PhysicalSpace::collide(PhysicalGeom &o1, PhysicalGeom &o2, PhysicalContactPoint *contact, short int maxContacts){
	//printf("int PhysicalSpace::collide\n");
	return dCollide(o1.getId(), o2.getId(),maxContacts, (dContactGeom *) contact, sizeof(PhysicalContactPoint));
}

void PhysicalSpace::spaceCollide(PhysicalGeom &o1, PhysicalGeom &o2, SpaceCallback *callback, void *data){
	//printf("void PhysicalSpace::spaceCollide2 - BEGIN\n");
	PhysicalSpace::m_spaceCallback = callback;


	dSpaceCollide2(o1.getId(), o2.getId() , data, &PhysicalSpace::nearCallback);
	//printf("void PhysicalSpace::spaceCollide2 - END\n");

}

void PhysicalSpace::spaceCollide(SpaceCallback *callback, void *data){
	//printf("void PhysicalSpace::spaceCollide1\n");
	PhysicalSpace::m_spaceCallback = callback;
	dSpaceCollide(m_spaceId, data,PhysicalSpace::nearCallback);
}



void PhysicalSpace::setData(void *data){
	dGeomSetData(m_geomId, data);
}


dSpaceID PhysicalSpace::getId(){
	return m_spaceId;
}

void PhysicalSpace::hashSpaceSetLevels(int minLevel, int maxLevel){
	dHashSpaceSetLevels(m_spaceId,minLevel, maxLevel);
}

void PhysicalSpace::hashSpaceGetLevels(int &minLevel, int &maxLevel){
	dHashSpaceGetLevels(m_spaceId, &minLevel, &maxLevel);
}

void PhysicalSpace::setCleanup(int mode){
	dSpaceSetCleanup(m_spaceId, mode);
}

int  PhysicalSpace::getCleanup(){
	return dSpaceGetCleanup(m_spaceId);
}

void PhysicalSpace::add(PhysicalGeom &pg){
	m_numGeom++;
	dSpaceAdd(m_spaceId, pg.getId());
}

void PhysicalSpace::remove(PhysicalGeom &pg){
	m_numGeom--;
	dSpaceRemove(m_spaceId, pg.getId());
}

bool PhysicalSpace::query(PhysicalGeom &pg){
	return dSpaceQuery(m_spaceId, pg.getId())? true:false;
}

PhysicalGeom *PhysicalSpace::getGeom(int i){
	dGeomID geom = dSpaceGetGeom(m_spaceId, i);
	return (PhysicalGeom *) dGeomGetData(geom);
}

const PhysicalGeom &PhysicalSpace::operator[](int i){
	dGeomID geom = dSpaceGetGeom(m_spaceId, i);
	return *((PhysicalGeom *) dGeomGetData(geom));
}

int PhysicalSpace::getNumGeom(){
	return m_numGeom;
}
