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
#ifndef PHYSICALSPACE_H
#define PHYSICALSPACE_H
#include "../Math/Vector3.h"
#include "PhysicalGeom.h"
#include "PhysicalContactPoint.h"

#include <ode/ode.h>

namespace InGE{

	
	
	enum SpaceType { InGE_SIMPLE_SPACE, InGE_HASH_SPACE, InGE_QUADTREE_SPACE};

	//Callback utilizada para processar objetos que possuem alto potencial de intersecao
	typedef void SpaceCallback(PhysicalGeom &, PhysicalGeom &, void *);
	
	class PhysicalSpace : public InGE::PhysicalGeom{
		private:
			dSpaceID	m_spaceId;
			int 		m_numGeom;
			
		public:
			//Membro estatico - Guarda o callback atualmente utilizado 
			static SpaceCallback *m_spaceCallback;
	
			//Membro estatico - Callback ponte para ponte SpaceCallback
			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
			
			static int collide(PhysicalGeom &o1, PhysicalGeom &o2, PhysicalContactPoint *contact, short int maxContacts);

			static void spaceCollide(PhysicalGeom &o1, PhysicalGeom &o2, SpaceCallback *callback, void *data);
			void spaceCollide(SpaceCallback *callback, void *data);

			PhysicalSpace(SpaceType st= InGE_SIMPLE_SPACE, PhysicalSpace *ps=NULL); // SIMPLE & HASH
			PhysicalSpace(Vector3 center, Vector3 extends, int depth, PhysicalSpace *ps=NULL); // QUADTREE
			~PhysicalSpace();
			
			dSpaceID getId();
			
			void hashSpaceSetLevels(int minLevel, int maxLevel);
			void hashSpaceGetLevels(int &minLevel, int &maxLevel);
			void setCleanup(int mode);
			int  getCleanup();
			
			void add(PhysicalGeom &pg);
			void remove(PhysicalGeom &pg);
			bool query(PhysicalGeom &pg);
			PhysicalGeom *getGeom(int i);
			const PhysicalGeom &operator[](int i);
			void setData(void *data);
			
			int getNumGeom();
			

	};
};

#endif // PHYSICALSPACE_H
