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
#ifndef JOINTUNIVERSAL_H
#define JOINTUNIVERSAL_H

#include "../PhysicalJoint.h"
#include "../PhysicalJointGroup.h"
#include "../../Math/Vector3.h"

namespace InGE{

	

	class JointUniversal : public InGE::PhysicalJoint{
		public:
			JointUniversal(PhysicalWorld *pw, PhysicalJointGroup *pjg=NULL);
			~JointUniversal();

			void setAnchor(Vector3 &point);
			void setAxis1(Vector3 &axis);
			void setAxis2(Vector3 &axis);			
			Vector3 getAnchor();
			Vector3 getAnchor2();
			Vector3 getAxis1();			
			Vector3 getAxis2();		
			
			void setParam(JointParam parameter, float value);				
			float getParam(JointParam parameter);
			
			void addTorque(float torque1, float torque2);
	};

};
#endif // JOINTUNIVERSAL_H
