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
#include "QuadNode.h"
using namespace std;
namespace InGE {

template <typename Tp> QuadNode<Tp>::QuadNode(double minX, double maxX, double minY, double maxY, unsigned int maxElem, unsigned int maxDepth){
	m_minX = minX;
	m_minY = minY;
	m_maxX = maxX;
	m_maxY = maxY;	
	m_maxElem = maxElem;
	m_maxDepth = maxDepth;
	m_middleX = ( (m_maxX - m_minX)/2 + m_minX);
	m_middleY = ( (m_maxY - m_minY)/2 + m_minY);

}


template <typename Tp> QuadNode<Tp>::~QuadNode()
{
}


template <typename Tp> bool InGE::QuadNode<Tp>::reCalculate( ){
	return false;
}

template <typename Tp> int InGE::QuadNode<Tp>::checkQuad(Vector3 &position){
	int sonIndex;
	if (position[0] > m_middleX){
		if (position[1] > m_middleY){
			sonIndex = 0;
		} else {
			sonIndex = 1;
		}
	} else {
		if (position[1] > m_middleY){
			sonIndex = 2;
		} else {
			sonIndex = 3;
		}
	}
	return sonIndex;
}

template <typename Tp> bool QuadNode<Tp>::insertElement(Tp *element, Vector3 &position){
	int sonIndex = checkQuad(position);
	if (m_son[sonIndex]->insertElement(element, position)){
		return true;
	} else {
		if(m_son[sonIndex]->isLeaf()) {
			return createNewFather(sonIndex);
		}
	}
	return false; /*level*/
}

template <typename Tp> bool QuadNode<Tp>::createNewFather(unsigned int sonIndex){
	double minX, minY, maxX, maxY;
	
	switch(sonIndex) {
		case 0: 
			minX = m_minX;
			maxX = m_middleX;
			minY = m_middleY;
			maxY = m_maxY;
			break;
		case 1: 
			minX = m_middleX;
			maxX = m_maxX;
			minY = m_middleY;
			maxY = m_maxY;
			break;
		case 2: 
			minX = m_minX;
			maxX = m_middleX;
			minY = m_minY;
			maxY = m_middleY;
			break;
		case 3: 
			minX = m_middleX;
			maxX = m_maxX;
			minY = m_minY;
			maxY = m_middleY;
			break;
	}
//	if( PODE CRIAR MAIS NIVEIS ){
		QuadNode *newNode = new QuadNode(minX, maxX, minY, maxY, m_maxElem, m_maxDepth);
		newNode->insertLeaf(m_son[sonIndex]); 
		m_son[sonIndex] = newNode;
		return true;
//	}
//		return false;
}

template <typename Tp> void QuadNode<Tp>:: insertLeaf(SpaceLeaf<Tp> *leaf) {
	m_son = new SpaceLeaf<Tp>[4];
	unsigned int leaves = leaf->getNumberOfElements();
	
	map<Vector3, Tp *> mapElements = leaf->getElements();
	
// 	map<Vector3, Tp *>::iterator elemIt;
	
	
// 	for(elemIt = mapElements.begin(); elemIt != mapElements.end(); elemIt++){
// 		m_son[checkQuad(elemIt.first)]->insertElement;
// 	}
	
	delete leaf;
}
}
