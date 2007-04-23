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
#include "QuadTree.h"

namespace InGE {

template <typename Tp> 
	QuadTree<Tp>::QuadTree(double minX, double maxX,
								 double minY, double maxY,
								 unsigned int maxElem, unsigned int maxDepth) : SpaceTree<Tp>() {
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
	m_maxElem = maxElem;
	m_maxDepth = maxDepth;
	
	m_root = new SpaceLeaf<Tp> (maxElem);
}


template <typename Tp> QuadTree<Tp>::~QuadTree(){
	delete m_root;

}

template <typename Tp> bool QuadTree<Tp>::reCalculate(){
	
}


template <typename Tp> bool QuadTree<Tp>:: insertElement(Tp *element, Vector3 &position) {
	if (m_root){
		if (m_root->insertElement(element, position) ){
			return true;
		} else {
			QuadNode<Tp> *newNode = new QuadNode<Tp>(m_minX, m_maxX, m_minY, m_maxY, m_maxElem, m_maxDepth);
			newNode->insertLeaf(m_root);
			m_root = newNode;
			
			return true;
		}
	}
	return false;
}

}
