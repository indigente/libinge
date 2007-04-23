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
#ifndef INGESPACELEAF_H
#define INGESPACELEAF_H

#include <list>
#include "SpaceNode.h"

namespace InGE {

/**
	@author Humberto Bandeira <nkbeto@gmail.com>
*/
template <typename Tp> class SpaceLeaf : public SpaceNode<Tp> {
	private:
		std::list<Tp *> m_vetElement;
	
	public:
		SpaceLeaf();
	
		~SpaceLeaf();
		
		bool insertElement(Tp *element);
		
		Tp *getElement(unsigned int index);
		std::list<Tp *>	getElements();
		unsigned int getNumberOfElements();
		bool removeElement(unsigned int index);
		bool clean();
		
		bool isLeaf();
		
};

}

#endif
