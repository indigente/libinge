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
#include "PhysicalBody.h"
#include <iostream>
using namespace std;
using namespace InGE;
PhysicalBody::PhysicalBody(PhysicalWorld *pw){
	m_bodyId  = dBodyCreate( pw->getId() );
	m_worldId = pw->getId();
	
	setData((void *) this);
}

PhysicalBody::PhysicalBody(PhysicalWorld &pw){
	m_bodyId  = dBodyCreate(pw.getId());
	m_worldId = pw.getId();
	
	setData((void *) this);
}

PhysicalBody::~PhysicalBody(){
	dBodyDestroy(m_bodyId);
}

void PhysicalBody::setMass(PhysicalMass &mass){
	dBodySetMass(m_bodyId, &mass.getMass());
}

float PhysicalBody::getMass(){
	dMass mass;
	dBodyGetMass(m_bodyId, &mass);
	return mass.mass;
}

Vector4 PhysicalBody::getCenter(){
	dMass mass;
	dBodyGetMass(m_bodyId, &mass);
	return Vector4((float *)(mass.c));
}

float *PhysicalBody::getInertia(){
	dMass mass;
	dBodyGetMass(m_bodyId, &mass);
	return (float *)(mass.I);
}


void PhysicalBody::setPosition(Vector3 &position){
	dBodySetPosition(m_bodyId, position[0], position[1], position[2]);
}

void PhysicalBody::setLinearVel(Vector3 &v){
	dBodySetLinearVel(m_bodyId, v[0], v[1], v[2]);
}

void PhysicalBody::setAngularVel(Vector3 &v){
	dBodySetAngularVel(m_bodyId, v[0], v[1], v[2]);
}

void PhysicalBody::setRotation(const float rotation[12]){
	dBodySetRotation(m_bodyId, (const dReal*)rotation);
}

void PhysicalBody::setQuaternion(const float quaternion[4]){
	dBodySetQuaternion(m_bodyId, (const dReal *)quaternion);
}
			
Vector3 PhysicalBody::getPosition(){
	const dReal *v  = dBodyGetPosition(m_bodyId);
	return Vector3(v[0], v[1], v[2]);

}

Vector3 PhysicalBody::getLinearVel(){
	const dReal *v  = dBodyGetLinearVel(m_bodyId);
	return Vector3(v[0], v[1], v[2]);
}

Vector3 PhysicalBody::getAngularVel(){
	const dReal *v  = dBodyGetAngularVel(m_bodyId);
	return Vector3(v[0], v[1], v[2]);
}

const float *PhysicalBody::getRotation(){
	return (const float *)dBodyGetRotation(m_bodyId);
}

const float *PhysicalBody::getQuaternion(){
	return (const float *)dBodyGetQuaternion(m_bodyId);
}	

dBodyID PhysicalBody::getId(){
	return m_bodyId;
}



void PhysicalBody::addForce(Vector3 &force){
	dBodyAddForce(m_bodyId, force[0], force[1], force[2]);
}

void PhysicalBody::addTorque(Vector3 &torque){
	dBodyAddTorque(m_bodyId, torque[0], torque[1], torque[2]);
}

void PhysicalBody::addRelForce(Vector3 &force){
	dBodyAddRelForce(m_bodyId, force[0], force[1], force[2]);
}

void PhysicalBody::addRelTorque(Vector3 &torque){
	dBodyAddRelTorque(m_bodyId, torque[0], torque[1], torque[2]);
}

void PhysicalBody::addForceAtPos(Vector3 &force, Vector3 &position){
	dBodyAddForceAtPos(m_bodyId, force[0], force[1], force[2], position[0], position[1], position[2]);
}

void PhysicalBody::addForceAtRelPos(Vector3 &force, Vector3 &position){
	dBodyAddForceAtRelPos(m_bodyId, force[0], force[1], force[2], position[0], position[1], position[2]);
}

void PhysicalBody::addRelForceAtPos(Vector3 &force, Vector3 &position){
	dBodyAddRelForceAtPos(m_bodyId, force[0], force[1], force[2], position[0], position[1], position[2]);
}

void PhysicalBody::addRelForceAtRelPos(Vector3 &force, Vector3 &position){
	dBodyAddRelForceAtRelPos(m_bodyId, force[0], force[1], force[2], position[0], position[1], position[2]);
}


Vector3 PhysicalBody::getForce(){
	const float *force = (const float *)dBodyGetForce(m_bodyId);
	return Vector3(force[0], force[1], force[2]);
}

Vector3 PhysicalBody::getTorque(){
	const float *torque = (const float *)dBodyGetTorque(m_bodyId);
	return Vector3(torque[0], torque[1], torque[1]);
}

void PhysicalBody::setForce(Vector3 &force){
	dBodySetForce(m_bodyId, force[0], force[1], force[2]);
}

void PhysicalBody::setTorque(Vector3 &torque){
	dBodySetTorque(m_bodyId, torque[0], torque[1], torque[2]);
}



Vector3 PhysicalBody::getRelPointPos(Vector3 position){
	dVector3 result; 
	dBodyGetRelPointPos(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);
}

Vector3 PhysicalBody::getRelPointVel(Vector3 position){
	dVector3 result; 
	dBodyGetRelPointVel(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);	
}

Vector3 PhysicalBody::getPointVel(Vector3 position){
	dVector3 result; 
	dBodyGetPointVel(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);	
}

Vector3 PhysicalBody::getPosRelPoint(Vector3 position){
	dVector3 result; 
	dBodyGetPosRelPoint(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);	
}

Vector3 PhysicalBody::vectorToWorld(Vector3 position){
	dVector3 result; 
	dBodyVectorToWorld(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);
}

Vector3 PhysicalBody::vectorFromWorld(Vector3 position){
	dVector3 result; 
	dBodyVectorFromWorld(m_bodyId, position[0], position[1], position[2], result);
	return Vector3(result[0], result[1], result[2]);
}




void  PhysicalBody::enable(){
	dBodyEnable(m_bodyId);
}

void  PhysicalBody::disable(){
	dBodyDisable(m_bodyId);
}

bool  PhysicalBody::isEnabled(){
	return dBodyIsEnabled(m_bodyId) ? true : false;
}

void  PhysicalBody::setAutoDisableFlag(int autoDisable){
	dBodySetAutoDisableFlag(m_bodyId, autoDisable);	
}

int   PhysicalBody::getAutoDisableFlag(){
	return dBodyGetAutoDisableFlag(m_bodyId);	
}

void  PhysicalBody::setAutoDisableLinearThreshold(float linearThreshold){
	dBodySetAutoDisableLinearThreshold(m_bodyId, linearThreshold);	
}

float PhysicalBody::getAutoDisableLinearThreshold(){
	return dBodyGetAutoDisableLinearThreshold(m_bodyId);		
}

void  PhysicalBody::setAutoDisableAngularThreshold(float angularThreshold){
	dBodySetAutoDisableAngularThreshold(m_bodyId, angularThreshold);	
}

float PhysicalBody::getAutoDisableAngularThreshold(){
	return dBodyGetAutoDisableAngularThreshold(m_bodyId);		
}

void  PhysicalBody::setAutoDisableSteps(int steps){
	dBodySetAutoDisableSteps(m_bodyId, steps);
}

int   PhysicalBody::getAutoDisableSteps(){
	return dBodyGetAutoDisableSteps(m_bodyId);		
}

void  PhysicalBody::setAutoDisableTime(float time){
	dBodySetAutoDisableTime(m_bodyId, time);
}

float PhysicalBody::getAutoDisableTime(){
	return dBodyGetAutoDisableTime(m_bodyId);
}

void  PhysicalBody::setAutoDisableDefaults(){
	dBodySetAutoDisableDefaults(m_bodyId);
}

/*
void  PhysicalBody::setAutoDisableThresholdSF1(float autoDisableThreshold){
	dBodySetAutoDisableThresholdSF1(m_bodyId, autoDisableThreshold);
}

float PhysicalBody::getAutoDisableThresholdSF1(){
	return dBodyGetAutoDisableThesholdSF1(m_bodyId);
}

void  PhysicalBody::setAutoDisableStepSF1(int autoDisableStep){
	dBodySetAutoDisableStepsSF1(m_bodyId, autoDisableStep);
}

int   PhysicalBody::getAutoDisableStepSF1(){
	return dBodyGetAutoDisableSF1(m_bodyId);
}
*/


void PhysicalBody::setData(void *data){
	dBodySetData(m_bodyId, data);
}

void *PhysicalBody::getData(){
	return dBodyGetData(m_bodyId);
}

void PhysicalBody::setFiniteRotationMode(int mode){
	dBodySetFiniteRotationMode(m_bodyId, mode);
}

int  PhysicalBody::getFiniteRotationMode(){
	return dBodyGetFiniteRotationMode(m_bodyId);
}

void PhysicalBody::setFiniteRotationAxis(Vector3 axis){
	dBodySetFiniteRotationAxis(m_bodyId, axis[0], axis[1], axis[2]);
}

Vector3 PhysicalBody::getFiniteRotationAxis(){
	dVector3 result;
	dBodyGetFiniteRotationAxis(m_bodyId, result);
	return Vector3(result[0], result[1], result[2]);
}

int PhysicalBody::getNumJoints(){
	return dBodyGetNumJoints(m_bodyId);
}

dJointID PhysicalBody::getJoint(int index){
	return dBodyGetJoint(m_bodyId, index);
}

void PhysicalBody::setGravityMode(int mode){
	dBodySetGravityMode(m_bodyId, mode);
}

int PhysicalBody::getGravityMode(){
	return dBodyGetGravityMode(m_bodyId);
}



