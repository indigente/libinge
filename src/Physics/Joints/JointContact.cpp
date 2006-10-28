/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2005 Indigente


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
#include "JointContact.h"

using namespace InGE;


JointContact::JointContact(){
}

JointContact::~JointContact(){
}

dJointID JointContact::createContact(PhysicalWorld *pw, PhysicalContactPoint *pcp, PhysicalJointGroup *pjg){
	if(!pw || !pcp) return m_jointId;
	
	m_contact.geom = pcp->m_contact;
	if(!pjg) return m_jointId = dJointCreateContact(pw->getId(), pjg->getId(), &m_contact);

	return m_jointId = dJointCreateContact(pw->getId(), 0, &m_contact);
}


void JointContact::setFDir(Vector3 &dir){
	m_contact.fdir1[0] = dir[0];
	m_contact.fdir1[1] = dir[1];
	m_contact.fdir1[2] = dir[2];		
}

void JointContact::setMode(int mode){
	m_contact.surface.mode = mode;
}

void JointContact::setMU(float mu){
	m_contact.surface.mu = mu;
}

void JointContact::setMU2(float mu2){
	m_contact.surface.mu2 = mu2;
}

void JointContact::setBounce(float bounce){
	m_contact.surface.bounce = bounce;
}

void JointContact::setBounceVel(float bounceVel){
	m_contact.surface.bounce_vel = bounceVel;
}

void JointContact::setSoftERP(float softERP){
	m_contact.surface.soft_erp  = softERP;
}

void JointContact::setSoftCFM(float softCFM){
	m_contact.surface.soft_cfm = softCFM;
}

void JointContact::setMotion1(float motion1){
	m_contact.surface.motion1 = motion1;
}

void JointContact::setMotion2(float motion2){
	m_contact.surface.motion2 = motion2;
}


void JointContact::setSlip1(float slip1){
	m_contact.surface.slip1 = slip1;
}

void JointContact::setSlip2(float slip2){
	m_contact.surface.slip2 = slip2;
}

