/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

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
#include "PhysicalContactPoint.h"

using namespace InGE;

PhysicalContactPoint::PhysicalContactPoint(){
	m_colided = false;
	m_contact.depth = 1.0f;
}

PhysicalContactPoint::PhysicalContactPoint(PhysicalContactPoint* point){
	this->m_colided = point->m_colided;
	this->m_contact = point->m_contact;
}

PhysicalContactPoint::~PhysicalContactPoint(){
}
void PhysicalContactPoint::setNormal(const Vector3 &normal){
	float *pNormal = (float *) &m_contact.normal;
	const float *tmp  = normal.toArray();
	pNormal[0] = tmp[0];
	pNormal[1] = tmp[1];
	pNormal[2] = tmp[2];
}
void PhysicalContactPoint::setPosition(const Vector3 &position){
	float *pPosition = (float *) &m_contact.pos;
	const float *tmp  = position.toArray();
	pPosition[0] = tmp[0];
	pPosition[1] = tmp[1];
	pPosition[2] = tmp[2];
}
void PhysicalContactPoint::setDepth(float depth){
	m_contact.depth = depth;
}

Vector3 PhysicalContactPoint::getNormal(){
	return Vector3((float *)m_contact.normal);
}

Vector3 PhysicalContactPoint::getPosition(){
	float *pPosition = (float *) &m_contact.pos;
	Vector3 pos(pPosition[0], pPosition[1], pPosition[2]);
	return pos;
}

float PhysicalContactPoint::getDepth(){
	return m_contact.depth;
}

PhysicalGeom *PhysicalContactPoint::getObject1(){
	if(!m_contact.g1) return NULL;
	PhysicalGeom *g1 = (PhysicalGeom *)dGeomGetData(m_contact.g1);
	return g1;
}

PhysicalGeom *PhysicalContactPoint::getObject2(){
	if(!m_contact.g2) return NULL;
	PhysicalGeom *g2 = (PhysicalGeom *)dGeomGetData(m_contact.g2);
	return g2;
}

bool PhysicalContactPoint::getColided() const{
  return m_colided;
}

void PhysicalContactPoint::setColided(bool theValue){
  m_colided = theValue;
}
