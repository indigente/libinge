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
#include "JointUniversal.h"

using namespace InGE;

JointUniversal::JointUniversal(PhysicalWorld *pw, PhysicalJointGroup *pjg){
	if(!pw) return;
	
	if(!pjg) m_jointId = dJointCreateUniversal(pw->getId(), 0);
	else     m_jointId = dJointCreateUniversal(pw->getId(), pjg->getId());	
}

JointUniversal::~JointUniversal(){
	dJointDestroy(m_jointId);	
}

void JointUniversal::setAnchor(Vector3 &point){
	dJointSetUniversalAnchor(m_jointId, point[0], point[1], point[2]);	
}

void JointUniversal::setAxis1(Vector3 &axis){
	dJointSetUniversalAxis1(m_jointId, axis[0], axis[1], axis[2]);
}

void JointUniversal::setAxis2(Vector3 &axis){
	dJointSetUniversalAxis2(m_jointId, axis[0], axis[1], axis[2]);	
}

Vector3 JointUniversal::getAnchor(){
	dVector3 result;
	dJointGetUniversalAnchor(m_jointId, result);
	return Vector3((float *)result);	
}

Vector3 JointUniversal::getAnchor2(){
	dVector3 result;
	dJointGetUniversalAnchor2(m_jointId, result);
	return Vector3((float *)result);		
}

Vector3 JointUniversal::getAxis1(){
	dVector3 result;
	dJointGetUniversalAxis1(m_jointId, result);
	return Vector3((float *)result);		
}

Vector3 JointUniversal::getAxis2(){
	dVector3 result;
	dJointGetUniversalAnchor(m_jointId, result);
	return Vector3((float *)result);		
}
void JointUniversal::setParam(JointParam parameter, float value){
	dJointSetUniversalParam(m_jointId, parameter, value);
}

float JointUniversal::getParam(JointParam parameter){
	return dJointGetUniversalParam(m_jointId, parameter);
}

void JointUniversal::addTorque(float torque1, float torque2){
	dJointAddUniversalTorques(m_jointId, torque1, torque2);
}


