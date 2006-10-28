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
#ifndef JOINTCONTACT_H
#define JOINTCONTACT_H

#include "../PhysicalJoint.h"
#include "../PhysicalJointGroup.h"
#include "../PhysicalContactPoint.h"
#include "../../Math/Vector3.h"

namespace InGE{
	
	
	
	enum JointContactSurfaceMode{
		InGE_JOINT_CONTACT_MU2 = dContactMu2,
		InGE_JOINT_CONTACT_FDIR = dContactFDir1,
		InGE_JOINT_CONTACT_BOUNCE = dContactBounce,
		InGE_JOINT_CONTACT_SOTF_ERP = dContactSoftERP,
		InGE_JOINT_CONTACT_MOTION1 = dContactMotion1,
		InGE_JOINT_CONTACT_MOTION2 = dContactMotion2,
		InGE_JOINT_CONTACT_SLIP1 = dContactSlip1,
		InGE_JOINT_CONTACT_SLIP2 = dContactSlip2,
		InGE_JOINT_CONTACT_APPROX1_1 = dContactApprox1_1,
		InGE_JOINT_CONTACT_APPROX1_2 = dContactApprox1_2,
		InGE_JOINT_CONTACT_APPROX1 = dContactApprox1				
	};
	
	class JointContact : public InGE::PhysicalJoint{
		private:
			dContact	m_contact;
		public:
			JointContact();
			~JointContact();
			
			dJointID createContact(PhysicalWorld *pw, PhysicalContactPoint *pcp, PhysicalJointGroup *pjg=NULL);
			
			void setFDir(Vector3 &dir);
			void setMode(int mode);
			void setMU(float mu);
			void setMU2(float mu2);
			void setBounce(float bounce);
			void setBounceVel(float bounceVel);
			void setSoftERP(float softERP);
			void setSoftCFM(float softCFM);
			void setMotion1(float motion1);
			void setMotion2(float motion2);
			void setSlip1(float slip1);
			void setSlip2(float slip2);
	};

};

#endif // JOINTCONTACT_H
