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
#include "JointHinge2.h"

using namespace InGE;

JointHinge2::JointHinge2(PhysicalWorld *pw, PhysicalJointGroup *pjg){
	if(!pw) return;
	
	if(!pjg) m_jointId = dJointCreateHinge2(pw->getId(), 0);
	else     m_jointId = dJointCreateHinge2(pw->getId(), pjg->getId());	
}

JointHinge2::~JointHinge2(){
	dJointDestroy(m_jointId);		
}

void JointHinge2::setAnchor(Vector3 &point){
	dJointSetHinge2Anchor(m_jointId, point[0], point[1], point[2]);
}

void JointHinge2::setAxis1(Vector3 &axis){
	dJointSetHinge2Axis1(m_jointId, axis[0], axis[1], axis[2]);
}

void JointHinge2::setAxis2(Vector3 &axis){
	dJointSetHinge2Axis2(m_jointId, axis[0], axis[1], axis[2]);
}

Vector3 JointHinge2::getAnchor(){
	dVector3 result;
	dJointGetHinge2Anchor(m_jointId, result);
	return Vector3((float *)result);	
}

Vector3 JointHinge2::getAnchor2(){
	dVector3 result;
	dJointGetHinge2Anchor2(m_jointId, result);
	return Vector3((float *)result);	
}

Vector3 JointHinge2::getAxis1(){
	dVector3 result;
	dJointGetHinge2Axis1(m_jointId, result);
	return Vector3((float *)result);	
}

Vector3 JointHinge2::getAxis2(){
	dVector3 result;
	dJointGetHinge2Axis2(m_jointId, result);
	return Vector3((float *)result);	
}


float JointHinge2::getAngle1(){
	return dJointGetHinge2Angle1(m_jointId);
}

float JointHinge2::getAngle1Rate(){
	return dJointGetHinge2Angle1Rate(m_jointId);	
}

float JointHinge2::getAngle2Rate(){
	return dJointGetHinge2Angle2Rate(m_jointId);	
}

void JointHinge2::setParam(JointParam parameter, float value){
	dJointSetHinge2Param(m_jointId, parameter, value);
}

float JointHinge2::getParam(JointParam parameter){
	return dJointGetHinge2Param(m_jointId, parameter);
}

void JointHinge2::addTorque(float torque1, float torque2){
	dJointAddHinge2Torques(m_jointId, torque1, torque2);
}
