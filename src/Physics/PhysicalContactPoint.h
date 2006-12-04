/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2005 Indigente

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
#ifndef PHYSICALCONTACTPOINT_H
#define PHYSICALCONTACTPOINT_H
#include "../Math/Vector3.h"
#include "PhysicalGeom.h"
#include <ode/ode.h>

namespace InGE{

	

	class PhysicalContactPoint{
		public:
		
			dContactGeom	m_contact;
			bool m_colided;
		
			PhysicalContactPoint();
			PhysicalContactPoint(PhysicalContactPoint* point);
			~PhysicalContactPoint();
			
			void setNormal(const Vector3& normal);
			void setPosition(const Vector3& position);
			void setDepth(float depth);
			void setColided(bool theValue);
			
			Vector3 getNormal();
			Vector3 getPosition();
			float getDepth();
			PhysicalGeom *getObject1();
			PhysicalGeom *getObject2();
			bool getColided() const;
	
	

	
			
	};
}
#endif // PHYSICALCONTACTPOINT_H
