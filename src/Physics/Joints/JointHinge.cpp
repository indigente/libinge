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
#include "JointHinge.h"

using namespace InGE;

JointHinge::JointHinge(PhysicalWorld *pw, PhysicalJointGroup *pjg){
	if(!pw) return;
	
	if(!pjg) m_jointId = dJointCreateHinge(pw->getId(), 0);
	else     m_jointId = dJointCreateHinge(pw->getId(), pjg->getId());
}

JointHinge::~JointHinge(){
	dJointDestroy(m_jointId);
}

void JointHinge::setAnchor(Vector3 &point){
	dJointSetHingeAnchor(m_jointId, point[0], point[1], point[2]);
}

void JointHinge::setAxis(Vector3 &axis){
	dJointSetHingeAxis(m_jointId, axis[0], axis[1], axis[2]);
}

Vector3 JointHinge::getAnchor(){
	dVector3 result;
	dJointGetHingeAnchor(m_jointId, result);
	return Vector3((float *)result);	
}

Vector3 JointHinge::getAnchor2(){
	dVector3 result;
	dJointGetHingeAnchor2(m_jointId, result);
	return Vector3((float *)result);		
}

Vector3 JointHinge::getAxis(){
	dVector3 result;
	dJointGetHingeAxis(m_jointId, result);
	return Vector3((float *)result);		
}

float JointHinge::getAngle(){
	return dJointGetHingeAngle(m_jointId);
}

float JointHinge::getAngleRate(){
	return dJointGetHingeAngleRate(m_jointId);
}

void JointHinge::setParam(JointParam parameter, float value){
	dJointSetHingeParam(m_jointId, parameter, value);
}

float JointHinge::getParam(JointParam parameter){
	return dJointGetHingeParam(m_jointId, parameter);
}

void JointHinge::addTorque(float torque){
	dJointAddHingeTorque(m_jointId, torque);
}

