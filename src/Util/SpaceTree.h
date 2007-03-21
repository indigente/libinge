/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

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

#include <list>
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
		
		virtual bool insertElement(Tp *element) = 0;
		
		virtual Tp *getElement(PhysicalGeom *geom, unsigned int index) = 0;
		virtual std::list<Tp *>	getElements(PhysicalGeom *geom) = 0;
		
		virtual std::list<Tp *>	getNeighbors(PhysicalGeom *geom) = 0;
		
		virtual bool removeElement(PhysicalGeom *geom, unsigned int index) = 0;
		virtual bool cleanLeaf(PhysicalGeom *geom) = 0;
		
		virtual unsigned int getNumberOfLeaves() = 0;
		virtual unsigned int getNumberOfLeaves(PhysicalGeom *geom) = 0;
		virtual unsigned int getNumberOfLevels() = 0;
		virtual unsigned int getNumberOfLevels(PhysicalGeom *geom) = 0;
		

};

}

#endif
