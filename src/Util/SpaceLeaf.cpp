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
#include "SpaceLeaf.h"

using namespace InGE;
using namespace std;

template <typename Tp> InGE::SpaceLeaf<Tp>::SpaceLeaf(unsigned int maxElem){
	m_maxElem = maxElem;
}


template <typename Tp> InGE::SpaceLeaf<Tp>::~SpaceLeaf(){
}


template <typename Tp> bool InGE::SpaceLeaf<Tp>::insertElement( Tp *element, Vector3 &position ){
	if (m_vetElement.size() < m_maxElem){
		m_vetElement.push_back(element);
		return true;
	}
	return false;
}

template <typename Tp> Tp *InGE::SpaceLeaf<Tp>::getElement( unsigned int index ){
	return m_vetElement[index];
}

template <typename Tp> std::map<Vector3, Tp * > InGE::SpaceLeaf<Tp>::getElements( ){
}

template <typename Tp> unsigned int InGE::SpaceLeaf<Tp>::getNumberOfElements( ){
}

template <typename Tp> bool InGE::SpaceLeaf<Tp>::removeElement( unsigned int index ){
}

template <typename Tp> bool InGE::SpaceLeaf<Tp>::clean( ){
}

template <typename Tp> bool InGE::SpaceLeaf<Tp>::isLeaf( ){
	return true;
}
