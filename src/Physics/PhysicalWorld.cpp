/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente

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
#include "PhysicalWorld.h"

using namespace InGE;

PhysicalWorld::PhysicalWorld(){
	m_worldId = dWorldCreate();
}

PhysicalWorld::~PhysicalWorld(){
	dWorldDestroy(m_worldId);
}

// Ajusta gravidade no mundo fisico
void PhysicalWorld::setGravity(const Vector3 &v){
	dWorldSetGravity(m_worldId, v.getX(), v.getY(), v.getZ());
}

// Retorna a gravidade do mundo fisico
Vector3 PhysicalWorld::getGravity(){
	dReal v[4];
	dWorldGetGravity(m_worldId, v);
	return Vector3((float *)v);
}


void PhysicalWorld::setERP(float erp){
	dWorldSetERP(m_worldId, erp);
}

float PhysicalWorld::getERP(){
	return dWorldGetERP(m_worldId);
}

void PhysicalWorld::setCFM(float cfm){
	dWorldSetCFM(m_worldId, cfm);
}

float PhysicalWorld::getCFM(){
	return dWorldGetCFM(m_worldId);
}

// Set e Get para o padrao dos parametros a criacao de novos corpos
void  PhysicalWorld::setAutoDisableFlag(int autoDisable){
	dWorldSetAutoDisableFlag(m_worldId, autoDisable);	
}

int   PhysicalWorld::getAutoDisableFlag(){
	return dWorldGetAutoDisableFlag(m_worldId);	
}

void  PhysicalWorld::setAutoDisableLinearThreshold(float linearThreshold){
	dWorldSetAutoDisableLinearThreshold(m_worldId, linearThreshold);	
}

float PhysicalWorld::getAutoDisableLinearThreshold(){
	return dWorldGetAutoDisableLinearThreshold(m_worldId);		
}

void  PhysicalWorld::setAutoDisableAngularThreshold(float angularThreshold){
	dWorldSetAutoDisableAngularThreshold(m_worldId, angularThreshold);	
}

float PhysicalWorld::getAutoDisableAngularThreshold(){
	return dWorldGetAutoDisableAngularThreshold(m_worldId);		
}

void  PhysicalWorld::setAutoDisableSteps(int steps){
	dWorldSetAutoDisableSteps(m_worldId, steps);
}

int   PhysicalWorld::getAutoDisableSteps(){
	return dWorldGetAutoDisableSteps(m_worldId);		
}

void  PhysicalWorld::setAutoDisableTime(float time){
	dWorldSetAutoDisableTime(m_worldId, time);
}

float PhysicalWorld::getAutoDisableTime(){
	return dWorldGetAutoDisableTime(m_worldId);
}

void PhysicalWorld::setAutoEnableDepthSF1(int autoEnableDepth){
	dWorldSetAutoEnableDepthSF1(m_worldId, autoEnableDepth);
}

int  PhysicalWorld::getAutoEnableDepthSF1(){
	return dWorldGetAutoEnableDepthSF1(m_worldId);
}

// converter impulso em forca 
Vector3 PhysicalWorld::impulseToForce(int stepSize, Vector3 impulse){
	dVector3 force;
	dWorldImpulseToForce(m_worldId, stepSize, impulse[0], impulse[1], impulse[2], force);
	return Vector3((float *) force);
}

void PhysicalWorld::step(float stepSize){
	dWorldStep(m_worldId, stepSize);
}


void PhysicalWorld::quickStep(float stepSize){
	dWorldQuickStep(m_worldId, stepSize);
}

void PhysicalWorld::stepFast1(float stepSize, int maxIterations){
	dWorldStepFast1(m_worldId, stepSize, maxIterations);
}


void  PhysicalWorld::setQuickStepNumIterations(int num){
	dWorldSetQuickStepNumIterations(m_worldId, num);
}

int   PhysicalWorld::getQuickStepNumIterations(){
	return dWorldGetQuickStepNumIterations(m_worldId);
}

void  PhysicalWorld::setContactMaxCorrectingVel(float vel){
	dWorldSetContactMaxCorrectingVel(m_worldId, vel);
}

float PhysicalWorld::getContactMaxCorrectingVel(){
	return dWorldGetContactMaxCorrectingVel(m_worldId);
}

void  PhysicalWorld::setContactSurfaceLayer(float depth){
	dWorldSetContactSurfaceLayer(m_worldId, depth);
}

float PhysicalWorld::getContactSurfaceLayer(){
	return dWorldGetContactSurfaceLayer(m_worldId);	
}

dWorldID PhysicalWorld::getId(){
	return m_worldId;
}
