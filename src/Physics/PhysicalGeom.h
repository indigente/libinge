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
#ifndef PHYSICALGEOM_H
#define PHYSICALGEOM_H
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "PhysicalBody.h" 
#include <ode/ode.h>

namespace InGE{

	struct AABB{
		Vector3 max;
		Vector3 min;
		AABB(Vector3 &ma, Vector3 &mi){ max = ma; min = mi;}
	};

	class PhysicalGeom{
		protected:
			dGeomID		m_geomId;
			void		*m_pData;
			PhysicalBody 	*m_pPhysicalBody;
			
		public:
			PhysicalGeom();
			virtual ~PhysicalGeom();
			
			virtual void setData(void *data)=0;
			void *getData();
			
			void setBody(PhysicalBody *pb);
			PhysicalBody *getBody();
			
			void sumPosition(const Vector3 &position);
			void setPosition(const Vector3 &position);
			void setRotation(const float rotation[12]);
			void setQuaternion(const float quaternion[4]);
			
			Vector3 getPosition();
			const float *getRotation();

			Quaternion getQuaternion();
			
			AABB getAABB();
			
			bool isSpace();
			dSpaceID getSpaceId();
			int getClass();

			// Categoria e campo de bits para colisao
			void setCategoryBits(unsigned long int bits);
			void setCollideBits(unsigned long int bits);
			unsigned long int getCategoryBits();
			unsigned long int getCollideBits();
			
			// Enable e Disable
			void enable();
			void disable();
			bool isEnabled();
			
			dGeomID getId();
	};

};

#endif // PHYSICALGEOM_H
