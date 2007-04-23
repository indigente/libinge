/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

Copyright  2004-2006 Indigente


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
#ifndef INGESPACETREE_H
#define INGESPACETREE_H

#include <map>
#include "../Physics/PhysicalGeom.h"

namespace InGE {

/**
	@author Humberto Bandeira <nkbeto@gmail.com>
*/
template <typename Tp> class SpaceTree{
	private:
		
	public:
		SpaceTree();
	
		~SpaceTree();
		
		virtual bool reCalculate() = 0;
		
		virtual bool insertElement(Tp *element, Vector3 &position) = 0;
		
		virtual Tp *getElement(Vector3 &position, unsigned int index) = 0;
		virtual std::map<Vector3, Tp *>	getElements(Vector3 &position) = 0;
		
		virtual std::map<Vector3, Tp *>	getNeighbors(Vector3 &position) = 0;
		
		virtual bool removeElement(Vector3 &position, unsigned int index) = 0;
		virtual bool cleanLeaf(Vector3 &position) = 0;
		
		virtual unsigned int getNumberOfLeaves() = 0;
		virtual unsigned int getNumberOfLeaves(Vector3 &position) = 0;
		virtual unsigned int getNumberOfLevels() = 0;
		virtual unsigned int getNumberOfLevels(Vector3 &position) = 0;
		

};

}

#endif
