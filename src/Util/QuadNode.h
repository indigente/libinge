/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

Copyright © 2004-2006 Indigente


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
#ifndef INGEQUADNODE_H
#define INGEQUADNODE_H

#include "SpaceNode.h"
#include "SpaceLeaf.h"

namespace InGE {

/**
	@author Aline Bessa	<alibezz@gmail.com>
*/
template <typename Tp> class QuadNode : public SpaceNode<Tp> {
	private:
		/* Each ordinary node has pointers to its 'family'*/
		double m_minX, m_maxX, m_minY, m_maxY;
		unsigned int m_maxElem, m_maxDepth;
		double m_middleX, m_middleY;
		
		SpaceNode<Tp> *m_son;
		QuadNode *m_father;
		
		bool createNewFather(unsigned int sonIndex);
		int checkQuad(Vector3 &position);
	
	public:
		QuadNode(double minX, double maxX,
				 double minY, double maxY,
				 unsigned int maxElem, unsigned int maxDepth = 0);
		
		~QuadNode();
		
		bool isLeaf();
		bool reCalculate();
		bool insertElement(Tp *element, Vector3 &position);
		void insertLeaf(SpaceLeaf<Tp> *leaf);
			
};

}


#endif
