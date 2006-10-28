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
#include "JointSlider.h"

using namespace InGE;

JointSlider::JointSlider(PhysicalWorld *pw, PhysicalJointGroup *pjg){
	if(!pw) return;
	
	if(!pjg) m_jointId = dJointCreateSlider(pw->getId(), 0);
	else     m_jointId = dJointCreateSlider(pw->getId(), pjg->getId());
}

JointSlider::~JointSlider(){
	dJointDestroy(m_jointId);
}

void JointSlider::setAxis(Vector3 &axis){
	dJointSetSliderAxis(m_jointId, axis[0], axis[1], axis[2]);
}

Vector3 JointSlider::getAxis(){
	dVector3 result;
	dJointGetSliderAxis(m_jointId, result);
	return Vector3((float *)result);	
}

float JointSlider::getPosition(){
	return dJointGetSliderPosition(m_jointId);
}

float JointSlider::getPositionRate(){
	return dJointGetSliderPositionRate(m_jointId);
}

void JointSlider::setParam(JointParam parameter, float value){
	dJointSetSliderParam(m_jointId, parameter, value);
}

float JointSlider::getParam(JointParam parameter){
	return dJointGetSliderParam(m_jointId, parameter);
}

void JointSlider::addForce(float force){
	dJointAddSliderForce(m_jointId, force);
}

