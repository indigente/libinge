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
#ifndef PHYSICALJOINT_H
#define PHYSICALJOINT_H
#include "../Math/Vector3.h"
#include "PhysicalBody.h"
#include <ode/ode.h>



namespace InGE{

	

	struct PhysicalJointFeedback{
		Vector3	f1;
		Vector3 t1;
		Vector3 f2;
		Vector3 t2;
		PhysicalJointFeedback(float force1[3], float force2[3], float torque1[3], float torque2[3]){
			f1.setXYZ(force1[0], force1[1], force1[2]);
			f2.setXYZ(force2[0], force2[1], force2[2]);
			t1.setXYZ(torque1[0], torque1[1], torque1[2]);
			t2.setXYZ(torque2[0], torque2[1], torque2[2]);
		}
	};
	
	enum JointParam{
		InGE_JOINT_LO_STOP = dParamLoStop,
		InGE_JOINT_HI_STOP = dParamHiStop,
		InGE_JOINT_VEL = dParamVel,
		InGE_JOINT_FMAX = dParamFMax,
		InGE_JOINT_FUDGE_FACTOR = dParamFudgeFactor,
		InGE_JOINT_BOUNCE = dParamBounce,
		InGE_JOINT_CFM = dParamCFM,
		InGE_JOINT_STOP_ERP = dParamStopERP,
		InGE_JOINT_STOP_CFM = dParamStopCFM,
		InGE_JOINT_SUSPENSION_ERP = dParamSuspensionERP,
		InGE_JOINT_SUSPENSION_CFM = dParamSuspensionCFM
	};
	
	class PhysicalJoint{
		protected:
			dJointID 	m_jointId;
		
		public:
		
			PhysicalJoint();
			virtual ~PhysicalJoint()=0;
			
			void attach(PhysicalBody &b1, PhysicalBody &b2);
			void setData(void *data);
			void *getData();
			int getType();
			PhysicalBody *getBody(int index);
			PhysicalJointFeedback getFeedback();
			void setFeedback(PhysicalJointFeedback &feedback);
			bool areConnected(PhysicalBody &o1, PhysicalBody &o2);
			bool areConnectedExcluding(PhysicalBody &o1, PhysicalBody &o2, int jointType);	
	};
	
};
#endif // PHYSICALJOINT_H
