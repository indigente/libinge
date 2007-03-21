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
#ifndef INGEQUADTREE_H
#define INGEQUADTREE_H

#include "SpaceTree.h"
		
namespace InGE {

/**
	@author Humberto Bandeira <nkbeto@gmail.com>
*/
template <typename Tp> class QuadTree : public SpaceTree<Tp> {
	private: 
		double m_minX, m_maxX, m_minY, m_maxY;
		unsigned int m_maxElem, m_maxDepth;
// 		QuadNode *m_root;
				
	public:
   	QuadTree(Tp type, double minX, double maxX,
					double minY, double maxY,
					unsigned int maxElem, unsigned int maxDepth = 0);

		~QuadTree();

		 bool reCalculate();
		
		 bool insertElement(Tp *element);
		
		 Tp *getElement(PhysicalGeom *geom, unsigned int index);
		 std::list<Tp *>	getElements(PhysicalGeom *geom);
		
		 std::list<Tp *>	getNeighbors(PhysicalGeom *geom);
		
		 bool removeElement(PhysicalGeom *geom, unsigned int index);
		 bool cleanLeaf(PhysicalGeom *geom);
		
		 unsigned int getNumberOfLeaves();
		 unsigned int getNumberOfLeaves(PhysicalGeom *geom);
		 unsigned int getNumberOfLevels();
		 unsigned int getNumberOfLevels(PhysicalGeom *geom);

};

}

#endif
