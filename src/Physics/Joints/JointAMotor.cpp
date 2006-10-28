/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2005 Indigente


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
#include "JointAMotor.h"

using namespace InGE;

JointAMotor::JointAMotor(PhysicalWorld *pw, PhysicalJointGroup *pjg){
	if(!pw) return;
	
	if(!pjg) m_jointId = dJointCreateUniversal(pw->getId(), 0);
	else     m_jointId = dJointCreateUniversal(pw->getId(), pjg->getId());		
}

JointAMotor::~JointAMotor(){
	dJointDestroy(m_jointId);
}

void JointAMotor::setMode(int mode){
	dJointSetAMotorMode(m_jointId, mode);
}

int  JointAMotor::getMode(){
	return dJointGetAMotorMode(m_jointId);
}

void JointAMotor::setNumAxes(int num){
	dJointSetAMotorNumAxes(m_jointId, num);
}

int  JointAMotor::getNumAxes(){
	return dJointGetAMotorNumAxes(m_jointId);
}


void JointAMotor::setAxis(int anum, int rel, Vector3 &axis){
	dJointSetAMotorAxis(m_jointId, anum, rel, axis[0], axis[1], axis[2]);
}

Vector3 JointAMotor::getAxis(int anum){
	dVector3 result;
	dJointGetAMotorAxis(m_jointId, anum, result);
	return Vector3((float *)result);	
}

int JointAMotor::getAxisRel(int anum){
	return dJointGetAMotorAxisRel(m_jointId, anum);
}


void JointAMotor::setAngle(int anum, float angle){
	dJointSetAMotorAngle(m_jointId, anum, angle);
}

float JointAMotor::getAngle(int anum){
	return dJointGetAMotorAngle(m_jointId, anum);
}

float JointAMotor::getAngleRate(int anum){
	return dJointGetAMotorAngleRate(m_jointId, anum);
}

void JointAMotor::setParam(JointParam parameter, float value){
	dJointSetAMotorParam(m_jointId, parameter, value);
}

float JointAMotor::getParam(JointParam parameter){
	return dJointGetAMotorParam(m_jointId, parameter);
}

void JointAMotor::addTorque(float torque0, float torque1, float torque2){
	dJointAddAMotorTorques(m_jointId, torque0, torque1, torque2);
}

