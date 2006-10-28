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
#include "PhysicalJoint.h"

using namespace InGE;

PhysicalJoint::PhysicalJoint(){
}
PhysicalJoint::~PhysicalJoint(){
}

void PhysicalJoint::attach(PhysicalBody &b1, PhysicalBody &b2){
	dJointAttach(m_jointId, b1.getId(), b2.getId());
}

void PhysicalJoint::setData(void *data){
	dJointSetData(m_jointId,data);
}


void *PhysicalJoint::getData(){
	return dJointGetData(m_jointId);
}

int PhysicalJoint::getType(){
	return dJointGetType(m_jointId);
}

PhysicalBody *PhysicalJoint::getBody(int index){
	dBodyID o = dJointGetBody(m_jointId, index);
	return (PhysicalBody *) dBodyGetData(o);
}

PhysicalJointFeedback PhysicalJoint::getFeedback(){
	dJointFeedback *feedback = dJointGetFeedback(m_jointId);
	return PhysicalJointFeedback((float *)feedback->f1, (float *)feedback->f2, (float *)feedback->t1, (float *)feedback->t2);
}

void PhysicalJoint::setFeedback(PhysicalJointFeedback &feedback){
	dJointFeedback fb;
	fb.f1[0] = feedback.f1[0];
	fb.f1[1] = feedback.f1[1];
	fb.f1[2] = feedback.f1[2];

	fb.f2[0] = feedback.f2[0];
	fb.f2[1] = feedback.f2[1];
	fb.f2[2] = feedback.f2[2];
	
	fb.t1[0] = feedback.t1[0];
	fb.t1[1] = feedback.t1[1];
	fb.t1[2] = feedback.t1[2];
	
	fb.t2[0] = feedback.t2[0];
	fb.t2[1] = feedback.t2[1];
	fb.t2[2] = feedback.t2[2];
	
	dJointSetFeedback(m_jointId, &fb);	
}


bool PhysicalJoint::areConnected(PhysicalBody &o1, PhysicalBody &o2){
	return dAreConnected(o1.getId(), o2.getId()) ? true : false;
}


bool PhysicalJoint::areConnectedExcluding(PhysicalBody &o1, PhysicalBody &o2, int jointType){
	return dAreConnectedExcluding(o1.getId(), o2.getId(), jointType) ? true : false;
}
